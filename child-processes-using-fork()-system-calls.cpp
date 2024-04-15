#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "Error: Fork failed" << std::endl;
        return 1;
    }
    else if (pid == 0)
    {
        std::cout << "Child process: My PID is " << getpid() << std::endl;
        std::cout << "Child process: My parent's PID is " << getppid() << std::endl;

        // Perform child-specific operations here

        return 0;
    }
    else
    {
        std::cout << "Parent process: I have a child with PID " << pid << std::endl;
        std::cout << "Parent process: My PID is " << getpid() << std::endl;

        // Perform parent-specific operations here

        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
