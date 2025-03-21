#include "nt_shared/nt_lock.h"
#include <sys/eventfd.h>
#include <unistd.h>

void nt_lock_init(NTLock* lock, bool init_unlocked)
{
    uint64_t init_val = (uint64_t)init_unlocked;

    lock->_efd = eventfd(init_val, NULL);
}

void nt_lock_lock(NTLock* lock)
{
    uint64_t value;
    read(lock->_efd, &value, sizeof(uint64_t));
}

void nt_lock_unlock(NTLock* lock)
{
    uint64_t value = 1;
    write(lock->_efd, &value, sizeof(uint64_t));
}

void nt_lock_destroy(NTLock* lock) 
{
    close(lock->_efd);
}

