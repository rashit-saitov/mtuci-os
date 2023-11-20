#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 > 0) {
        pid2 = fork();
        if (pid2 > 0) {
            printf("Родительский процесс: pid = %d, pid дочернего процесса 1 = %d, pid дочернего процесса 2 = %d\n", getpid(), pid1, pid2);
            system("ps -x");
            myCurrentTime();
            wait(NULL);
            wait(NULL);
        } else if (pid2 == 0) {
            printf("Дочерний процесс: pid = %d, pid родительского = %d\n", getpid(), getppid());
            myCurrentTime();
        } else {
            printf("Дочерний процесс: pid = %d, pid родительского = %d\n", getpid(), getppid());
            myCurrentTime();
        }
    } else if (pid1 == 0) {
        printf("Дочерний процесс: pid = %d, pid родительского = %d\n", getpid(), getppid());
    } else {
        perror("Ошибочка");
        return 1;
    }

    return 0;
}

int myCurrentTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timeString[12];
    strftime(timeString, sizeof(timeString), "%H:%M:%S", &tm);
    printf("Время: %s.%03d\n", timeString, (int)(t % 1000));
    return 0;
}