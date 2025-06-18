/*תרגיל 7 - שימוש ב-pipes, יצירת תהליכים - 20 נקודות.
מטרת תרגיל זה - עבודה עם 2)fork ,)2(execve ,)2(pipe )ולא עבודה עם strings.
תרגיל שיממש את הבעיה בעזרת api strings יפסל.
אני מממש ספר טלפונים בעזרת קובץ טקסט.
בקובץ טקסט נמצאים אצלי כל השמות יחד עם מספר הטלפון במבנה הבא: )שורה לכל שם ומספר, הפרדה
בפסיק בין השם למספר, השורה מסתיימת בסימון שורה חדשה(
Nezer Zaidenberg,054-5531415\n
קובץ הטקסט יכול להכיל עשרות ומאות רשומות בפורמט הזה.
לצורך זה אני מממש את 2 התוכניות הבאות -
PB2add - המוסיפה רשומה חדשה לספר הטלפונים )פשוט שורה חדשה(.
התוכנית תקבל שם - בדרך כלל שם ושם משפחה - שיכול להכיל רווחים )לדוגמא במקרה של Sheva Bat או שם
שני(. יכול להכיל רק שם פרטי )אם שם המשפחה לא ידוע לנו או לשמות כמו Dad ,Mom )לאחר מכן יהיה פסיק
)מובטח לנו ששם לא מכיל פסיק לעולם( ואז מספר הטלפון. סוף רשומה תמיד יהיה feed line.
findPhone - המוצאת את הטלפון של האדם שהתקבל ב1)argv )על ידי קריאה לפקודות
cat(1), grep(1), awk(1), sed(1),cut(1)
יש לייצר תהליכים )בעזרת 2)fork )ו2-)execXX )ולהעתיק descriptor file-ים בעזרת 2)dup )או 2)2dup)
להגיש make וקוד לשתי התוכניות וכן דוגמת הרצה )לדוגמא צילום מסך(
הערה - ניתן לקרוא על sed ,awk ,grep בכתובת הבאה.
https://www-users.york.ac.uk/~mijp1/teaching/2nd_year_Comp_Lab/guides/grep_awk_sed.pdf
למען הסר ספק - תרגיל זה צריך להיות כתוב ב-C או C++ ולא בbash או PERL.
הקלה חשובה - ניתן להניח שלכל אדם יש רק מספר טלפון אחד.
בנוסף ניתן להניח כי אני מכיר רק אדם אחד בכל שם. אם במקרה ביקשתי שם המופיע בספר הטלפון פעמיים
התשובה יכולה להיות כל תשובה שהיא. לדוגמא אם אני מכיר שני אנשים ששמם Avner והקובץ מכיל
Avner Harishon,03-1234567
Avner Hasheni,050-9876543
כל תשובה אפשרית )כולל אף תשובה(. בנוסף ניתן להניח שהתו # איננו מופיע כחלק מהשם או המספר באף
טלפון.
פתרון אפשרי לבעיית מציאת מספר טלפון בעזרת bash:
grep “Micky Mouse” phonebook.txt | sed ‘s/ /#/g’ | sed ‘s/,/ /’ | awk {print$2}
הפקודה הראשונה תחזיר רק את השורה שמכילה מיקי מאוס.
הפקודה השניה תהפוך את כל הרווחים לסולמיות.
הפקודה השלישית תייצר רווח במקום פסיק )וכך תיצור עמודה שניה(
הפקודה הרביעית תדפיס את העמודה השניה )כלומר הטלפון(*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

bool is_valid_name(const char* name) {
    for (int i = 0; name[i] != '\0'; ++i) {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '\'') {
            return false;
        }
    }
    return true;
}

bool is_valid_phone(const char* phone) {
    for (int i = 0; phone[i] != '\0'; ++i) {
        if (!isdigit(phone[i]) && phone[i] != '-') {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./add2PB <full name> <phone number>\n";
        cerr << "run example: ./add2PB John Doe 123-4567890\n";
        return 1;
    }

    // חבר את השם מכל argv (למעט האחרון)
    char name[256] = {0};
    int nameIndex = 0;
    for (int i = 1; i < argc - 1; ++i) {
        int j = 0;
        while (argv[i][j] != '\0' && nameIndex < 255) {
            name[nameIndex++] = argv[i][j++];
        }
        if (i < argc - 2 && nameIndex < 255) {
            name[nameIndex++] = ' ';
        }
    }
    name[nameIndex] = '\0';

    // בדוק תקינות שם
    if (!is_valid_name(name)) {
        cerr << "invalid name: Name must contain letters or spaces only\n";
        return 1;
    }

    // קבל את מספר הטלפון
    const char* phone = argv[argc - 1];

    if (!is_valid_phone(phone)) {
        cerr << "invalid phone: Phone number must contain digits or hyphens only\n";
        return 1;
    }
    // כתוב לקובץ
    int fd = open("phonebook.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    
    // Check if the file was opened successfully
     // O_WRONLY: Open for writing only
     // O_APPEND: Append to the end of the file
     // O_CREAT: Create the file if it does not exist
     // 0644: File permissions (read/write for owner, read for group and others)

    if (fd < 0) {
        cerr << "Error: failed to open the file\n";
        return 1;
    }

    char buffer[512];
    int index = 0;

    // Write the name
    for (int i = 0; name[i] != '\0'; ++i) {
        buffer[index++] = name[i];
    }

    buffer[index++] = ',';
    
    // Write the phone number
    for (int i = 0; phone[i] != '\0'; ++i) {
        buffer[index++] = phone[i];
    }
    
    buffer[index++] = '\n'; // Newline
    buffer[index] = '\0';

    // Write to the file
    write(fd, buffer, index);
    close(fd);
    cout << "Added successfully to phonebook!" <<endl;
    return 0;
}