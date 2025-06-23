#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <limits>

void send_bit(pid_t pid, int bit)
{
    int sig = (bit == 0) ? SIGUSR1 : SIGUSR2;
    if (kill(pid, sig) == -1)
    {
        perror("Failed to send signal");
        exit(1);
    }

    usleep(100000); // 100 milliseconds
}

int main()
{

    pid_t receiver_pid;
    int number;

    while (1)
    {
        std::cout << "Enter receiver PID: ";
        std::cin >> receiver_pid;

        // Check if the input is a valid and available PID
        if (std::cin.fail() || receiver_pid <= 0 || kill(receiver_pid, 0) == -1)
        {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            std::cout << "Invalid or unavailable PID." << std::endl;
            continue;
        }
        break; // Valid input
    }

    while (1)
    {
        std::cout << "Enter message: ";
        std::cin >> number;

        // Check if the input is a valid integer
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            std::cout << "Invalid input. Please enter a valid number between 0 and 255." << std::endl;
            continue;
        }

        // Check if there are any unexpected characters after the number
        if (std::cin.peek() != '\n')
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 0 and 255." << std::endl;
            continue;
        }

        // Check if the number is within the valid range
        if (number < 0 || number > 255)
        {
            std::cout << "Invalid number. Please enter a number between 0 and 255." << std::endl;
            continue;
        }

        break; // Valid input
    }

    for (int i = 7; i >= 0; --i)
    {
        int bit = (number >> i) & 1;
        send_bit(receiver_pid, bit);
    }

    return 0;
}
