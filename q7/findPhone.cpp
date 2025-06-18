#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;

bool is_valid_name(const char* name) {
    for (int i = 0; name[i] != '\0'; ++i) {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '\'') {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./findPhone <first name>\n";
        return 1;
    }
    cout << "Notice:the program use the first name only (argv[1]) " << endl;

    char* name = argv[1];
    if (!is_valid_name(name)) {
        cerr << "invalid name: Name must contain letters or spaces only\n";
        return 1;
    }

    pid_t pidArr[4]; // 4 תהליכים

    int pipe1[2], pipe2[2], pipe3[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("pipe failed");
        return 1;
    }

    // ילד 1: grep
    pidArr[0] = fork();
    if (pidArr[0] == -1) {
        perror("fork failed before grep");
        return 1;
    } else if (pidArr[0] == 0) {
        // בילד - רק כותב ל-pipe1
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);

        // סוגרים את כל הפייפים שלא צריך
        close(pipe2[0]); close(pipe2[1]);
        close(pipe3[0]); close(pipe3[1]);

        execlp("grep", "grep", name, "phonebook.txt", NULL);
        perror("execlp grep failed");
        exit(1);
    }

    // ילד 2: sed s/ /#/g
    pidArr[1] = fork();
    if (pidArr[1] == -1) {
        perror("fork failed before sed1");
        return 1;
    } else if (pidArr[1] == 0) {
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        close(pipe3[0]); close(pipe3[1]);

        execlp("sed", "sed", "s/ /#/g", NULL);
        perror("execlp sed1 failed");
        exit(1);
    }

    // ילד 3: sed s/,/ /
    pidArr[2] = fork();
    if (pidArr[2] == -1) {
        perror("fork failed before sed2");
        return 1;
    } else if (pidArr[2] == 0) {
        dup2(pipe2[0], STDIN_FILENO);
        dup2(pipe3[1], STDOUT_FILENO);
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        close(pipe3[0]); close(pipe3[1]);

        execlp("sed", "sed", "s/,/ /", NULL);
        perror("execlp sed2 failed");
        exit(1);
    }

    // ילד 4: awk {print $2}
    pidArr[3] = fork();
    if (pidArr[3] == -1) {
        perror("fork failed before awk");
        return 1;
    } else if (pidArr[3] == 0) {
        dup2(pipe3[0], STDIN_FILENO);
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        close(pipe3[0]); close(pipe3[1]);

        execlp("awk", "awk", "{print $2}", NULL);
        perror("execlp awk failed");
        exit(1);
    }

    // אבא - סוגר את כל הקצוות
    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    close(pipe3[0]); close(pipe3[1]);

    // ממתין לכל הילדים
    cout << "The phone number/s: " << endl;
    for (int i = 0; i < 4; ++i) {
        waitpid(pidArr[i], NULL, 0);
    }

    cout << "The program has finished " << endl;

    return 0;
}

