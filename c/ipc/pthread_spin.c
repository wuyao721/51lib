#include <sys/mman.h>
#include <pthread.h>

pthread_spinlock_t *lock = NULL;

int a()
{
    pthread_spin_lock(lock);
    pthread_spin_unlock(lock);
}

int main()
{
    char   *ptr      = NULL;
    size_t size      = sizeof(pthread_spinlock_t);

    if( MAP_FAILED == (ptr = (char*)mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1,0))) { 
        return -1;
    }
    lock = (pthread_spinlock_t *)ptr;
    if (0 != pthread_spin_init(lock, PTHREAD_PROCESS_SHARED)) {
        return -1;
    }
    
    a();

    return 0;
}
