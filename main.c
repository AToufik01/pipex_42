
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
// #define R 0
// #define W 1
// int ft_strlen(char *str)
// {
//     int i;
//     i = 0;
//     while(str[i])
//         i++;
//     return (i);
// }
// int main()
// {
//     int fd[2];
//     char message [100];
//     int nboctets;
//     char *phrase = " message envoye au pere par le fils";
//     pipe(fd);
//     if (fork( ) == 0 )
//     {
//         close(fd[R]);
//         write (fd[W], phrase, ft_strlen(phrase) + 1);
//         close(fd[W]);
//     }
//     else
//     {
//         close(fd[W]);
//         nboctets = read(fd[R], message , 100) ;
//         printf("Lecture %d octets: %s\n", nboctets, message);
//         close (fd[R]);
//     }
//     return 0 ;
// }

// int main () {

//     int fd;

//    /* first rename if there is any file */
// //    rename("file.txt", "newfile.txt");

//    fd = open("file.txt", O_WRONLY);
//    close(fd);
//    if(fd == -1 ) {
//       perror("EWW: ");
//       return(-1);
//    }
      
//    return(0);
// }

// #include <stdio.h>
// #include <errno.h>

// int main() {
//     FILE *file = fopen("nonexistentfile.txt", "r");
//     if (file == NULL) {
//         perror("Error opening file");
//     printf("hhhhhh\n");
//         // Output might be: "Error opening file: No such file or directory"
//     }
//     return 0;
// }


// #include <stdlib.h>
// #include <unistd.h>

// int pid;
// int pipe1[2];
// int pipe2[2];

// void exec1()
// {
//   // input from stdin (already done)
//   // output to pipe1
//   dup2(pipe1[1], 1);
//   // close fds
//   close(pipe1[0]);
//   close(pipe1[1]);
//   // exec
//   execlp("ps", "ps", "aux", NULL);
//   // exec didn't work, exit
//   perror("bad exec ps");
//   _exit(1);
// }

// void exec2()
// {
//   // input from pipe1
//   dup2(pipe1[0], 0);
//   // output to pipe2
//   dup2(pipe2[1], 1);
//   // close fds
//   close(pipe1[0]);
//   close(pipe1[1]);
//   close(pipe2[0]);
//   close(pipe2[1]);
//   // exec
//   execlp("grep", "grep", "root", NULL);
//   // exec didn't work, exit
//   perror("bad exec grep root");
//   _exit(1);
// }

// void exec3()
// {
//   // input from pipe2
//   dup2(pipe2[0], 0);
//   // output to stdout (already done)
//   // close fds
//   close(pipe2[0]);
//   close(pipe2[1]);
//   // exec
//   execlp("grep", "grep", "sbin", NULL);
//   // exec didn't work, exit
//   perror("bad exec grep sbin");
//   _exit(1);
// }
// int main()
// {
//   // create pipe1
//   if (pipe(pipe1) == -1)
//   {
//     perror("bad pipe1");
//     exit(1);
//   }

//   // fork (ps aux)
//   if ((pid = fork()) == -1)
//   {
//     perror("bad fork1");
//     exit(1);
//   }
//   else if (pid == 0)
//     exec1();
//   // parent

//   // create pipe2
//   if (pipe(pipe2) == -1)
//   {
//     perror("bad pipe2");
//     exit(1);
//   }

//   // fork (grep root)
//   if ((pid = fork()) == -1)
//   {
//     perror("bad fork2");
//     exit(1);
//   }
//   else if (pid == 0)
//     exec2();
//     // pipe1 --> grep --> pipe2
//   // parent

//   // close unused fds
//   close(pipe1[0]);
//   close(pipe1[1]);

//   // fork (grep sbin)
//   if ((pid = fork()) == -1)
//   {
//     perror("bad fork3");
//     exit(1);
//   }
//   else if (pid == 0)
//     exec3();
//     // pipe2 --> grep --> stdout
//   // parent
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main(int argc, char* argv[])
// {
//     int fd[2];
//     if (pipe(fd) == -1)
//         return 0;
//     int pid1 = fork();
//     if (pid1 < 0)
//         return 2;
//     if (pid1 == 0)
//     {
//         // Child process 1 (ping)
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execlp("ls", "ls", NULL);
//     }
//     int pid2 = fork();
//     if (pid2 < 0)
//         return 3;
//     if (pid2 == 0)
//     {
//         // Child process 2 (grep)
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execlp("wc -l", "wc -l", "rtt", NULL);
//     }
//     close(fd[0]);
//     close(fd[1]);
//     waitpid(pid1, NULL, 0);
//     // waitpid(pid2, NULL, 0);
//     return 0;
// }