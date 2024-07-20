#include <stdio.h>
#include <errno.h>
#include <string.h>

//PERROR
// perror prints a descriptive error message to the standard error (stderr) 
// based on the global variable errno, which is set by system calls and library
//  functions when they fail. This function is useful for debugging and diagnosing 
//  issues in your programs.


int main() {
    // Attempt to open a file that doesn't exist
    FILE *file = fopen("nonexistentfile.txt", "r");
    
    if (file == NULL) {
        // Print the error using perror
        perror("Error opening file");
    } else {
        // Close the file if it was successfully opened
        fclose(file);
    }

    return 0;
}

// STRERROR
// How It Works
// When a system call or library function fails, it sets the global variable errno to indicate the type of error.
// You can call strerror and pass it the errno value (or any other error number) to obtain a string that describes the error.
// strerror returns a pointer to a static buffer 
//containing the error message. The content of this buffer is overwritten on subsequent calls to strerror.

#include <stdio.h>
#include <errno.h>
#include <string.h>

void check_file_open(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Print detailed error message
        fprintf(stderr, "Failed to open file '%s': %s\n", filename, strerror(errno));
    } else {
        // File opened successfully
        fclose(file);
    }
}

int main() {
    check_file_open("nonexistentfile.txt");
    return 0;
}


// ACCESS

// Check for Existence: access(filename, F_OK) checks if the file exists.
// Check for Readability: access(filename, R_OK) checks if the file is readable.
// Check for Writability: access(filename, W_OK) checks if the file is writable.
// Check for Executability: access(filename, X_OK) checks if the file is executable.


// DUP
// int dup(int oldfd);
// The dup() system call creates a copy of the file descriptor oldfd, using 
// the lowest-numbered unused file descriptor for the new descriptor.
// After a successful return, the old and new file descriptors may be used interchangeably.  
//They refer to the same open file description (see open(2)) and thus share file offset and file status flags;
// for example, if the file offset is modified by using lseek(2) on one of the file descriptors, 
// the offset is also changed for the other.

// The two file descriptors do not share file descriptor flags (the close-on-exec flag).  
//The close-on-exec flag (FD_CLOEXEC; see fcntl(2)) for the duplicate descriptor is off.


//   DUP2
//int dup2(int oldfd, int newfd);

//        The dup2() system call performs the same task as dup(), but instead of using  the  lowest-num‐
//        bered  unused  file descriptor, it uses the file descriptor number specified in newfd.  If the
//        file descriptor newfd was previously open, it is silently closed before being reused.

//        The steps of closing and reusing the file descriptor newfd are performed atomically.  This  is
//        important, because trying to implement equivalent functionality using close(2) and dup() would
//        be subject to race conditions, whereby newfd might be reused between the two steps.  Such  re‐
//        use  could happen because the main program is interrupted by a signal handler that allocates a
//        file descriptor, or because a parallel thread allocates a file descriptor.

//        Note the following points:

//        *  If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.

//        *  If oldfd is a valid file descriptor, and newfd has the same value  as  oldfd,  then  dup2()
//           does nothing, and returns newfd.



//EXECVE
// The primary purpose of execve is to run a new executable program within the current process.
// This call replaces the current process image with a new process image, 
//which means the original process (including its code, data, and stack) is discarded
// and replaced by the new program. It is often used in conjunction with fork to create a new 
//process and then replace it with a different program.

#include <unistd.h>

int execve(const char *pathname, char *const argv[], char *const envp[]);

// pathname: A string representing the path to the executable file you want to run.

// argv: An array of strings representing the command-line arguments for the new program. 
// The first element (argv[0]) typically contains the name of the program itself, 
// and the array must be terminated by a NULL pointer.

// envp: An array of strings representing the environment variables for the new program. 
// Each string has the form "NAME=VALUE", and the array must be terminated by a NULL pointer.

// Return Value
// On Success: The execve function does not return because the current process image is replaced by the new process image.
// On Failure: Returns -1, and errno is set to indicate the error.

// Common Errors
// EACCES: Permission denied. The file exists but cannot be executed.
// ENOENT: No such file or directory. The specified file does not exist.
// ENOMEM: Not enough memory to execute the program.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Child process
        const char *pathname = "/bin/ls";
        char *const argv[] = {
            "ls",
            "-l",
            NULL
        };
        char *const envp[] = {
            "PATH=/bin:/usr/bin",
            NULL
        };

        if (execve(pathname, argv, envp) == -1) {
            perror("execve");
            exit(1);
        }
    } else { // Parent process
        // Optionally, wait for child process to complete
        wait(NULL);
    }

    return 0;
}


// The fork function is used to:

// Create a New Process: It creates a new process that is a copy of the calling process.
// Allow Concurrent Execution: It enables concurrent execution of processes, allowing the 
// parent and child processes to run simultaneously.
// Facilitate Process Management: It is often used in combination with other functions like 
// execve to execute new programs in a separate process.

// Return Type: The fork function returns a pid_t type, which is an integer type used for process IDs.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // This is the child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        // Perform child-specific tasks here
    } else {
        // This is the parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        // Optionally, wait for the child process to complete
        wait(NULL);
    }

    return 0;
}

// Explanation
// Fork Creation: fork() creates a new process. After the fork() call, there are two processes:
// The parent process, which receives the PID of the child process.
// The child process, which receives 0.
// Parent Process: The parent process prints its own PID and the PID of the child.
// Child Process: The child process prints its PID and the PID of its parent.
// Error Handling: If fork fails, it returns -1 and sets errno.
// Key Points
// Process Duplication: The child process is a duplicate of the parent process but has its own PID. The child process inherits a copy of the parent’s memory, file descriptors, and execution context.
// Concurrent Execution: After fork, both the parent and child processes run concurrently. They can perform different tasks or the same tasks independently.
// Process IDs: The parent and child processes have different PIDs, and the parent can use the PID returned by fork to manage the child process (e.g., wait for it to complete).
// Error Handling: Always check the return value of fork to handle errors, such as resource limits being reached.
// Related Functions
// wait and waitpid: These functions are used by the parent process to wait for the termination of child processes and to retrieve their exit status.
// execve: Often used after fork to replace the child process’s image with a new program.