#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int record_lock_lock(int fd)
{
    struct flock lock;
    
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    return fcntl(fd, F_SETLKW, &lock);
}

int record_lock_unlock(int fd)
{
    struct flock lock;
    
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    return fcntl(fd, F_SETLKW, &lock);
}

int main()
{
    int fd = -1;
    pid_t pid;

    if (-1 == (fd = open("/var/lock/subsys/fcntl.test", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR))) {
        return -1;
    }
    if (0 == (pid = fork())) {
        if (0 != record_lock_lock(fd)) {
            printf("error1\n");
        }
        sleep(2);
        printf("child do first.\n");
        if (0 != record_lock_unlock(fd)) {
            printf("error2\n");
        }
    } else if (pid > 0) {
        sleep(1);
        if (0 != record_lock_lock(fd)) {
            printf("error3\n");
        }
        printf("parent do second.\n");
        if (0 != record_lock_unlock(fd)) {
            printf("error4\n");
        }
    } else {
        // 
    }

    close(fd);
    return 0;
}
