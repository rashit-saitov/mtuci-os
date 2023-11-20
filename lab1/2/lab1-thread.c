#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>

void *printInfo(void *arg) {
    pthread_t tid = pthread_self();
    printf("ID потока: %lu, Родительский PID: %d\n", tid, getppid(), myCurrentTime());
    return NULL;
}

int myCurrentTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timeString[12];
    strftime(timeString, sizeof(timeString), "%H:%M:%S", &tm);
    printf("Время: %s.%03d\n", timeString, (int)(t % 1000));
    return 0;
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, printInfo, NULL);
    pthread_create(&tid2, NULL, printInfo, NULL);
    printf("PID главного процесса: %d\n", getpid());
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}