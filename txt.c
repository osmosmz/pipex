#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    // The command and arguments to execute
    char *command = "/usr/bin/bat"; // Full path to the 'bat' executable
    char *args[] = { "bat", NULL }; // Arguments for 'bat'

    // The input file to redirect from
    char *input_file = "infile.txt";

    // Open the input file for reading
    int fd = open(input_file, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Duplicate the file descriptor to stdin (fd 0)
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the original file descriptor
    close(fd);

    // Execute the command
    execve(command, args, NULL);

    // If execve returns, it must have failed
    if (errno == ENOENT) {
        // ENOENT indicates the file was not found
        fprintf(stderr, "%s: command not found\n", args[0]);
    } else {
        // For other errors, print the error message
        perror("execve");
    }

    // Exit with the appropriate error code
    exit(errno);
}
