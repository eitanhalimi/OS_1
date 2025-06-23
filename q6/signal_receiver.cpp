#include <iostream>
#include <csignal>
#include <unistd.h>

volatile sig_atomic_t bit_count = 0;
volatile sig_atomic_t result = 0;

void handle_sigusr(int sig)
{
    result <<= 1;

    if (sig == SIGUSR2)
    {
        result |= 1;
    }

    bit_count++;

    if (bit_count == 8)
    {
        std::cout << "Received " << result << std::endl;
        exit(0);
    }
}

int main()
{
    std::cout << "My PID is " << getpid() << std::endl;

    struct sigaction sa;
    sa.sa_handler = handle_sigusr; // Set the signal handler

    sigemptyset(&sa.sa_mask);        // Clear the signal mask
    sigaddset(&sa.sa_mask, SIGUSR1); // Block SIGUSR1
    sigaddset(&sa.sa_mask, SIGUSR2); // Block SIGUSR2;

    // Set the signal handler for SIGUSR1 and SIGUSR2
    sigaction(SIGUSR1, &sa, nullptr);
    sigaction(SIGUSR2, &sa, nullptr);

    while (true)
    {
        pause(); // Wait for signals
    }

    return 0;
}
