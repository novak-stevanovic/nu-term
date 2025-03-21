#ifndef _NT_LOCK_H_
#define _NT_LOCK_H_

#include <stdbool.h>
#include <sys/eventfd.h>

// Thread-safe, async-safe simple synchronization mechanism
typedef struct NTLock
{
    eventfd_t _efd;
} NTLock;

void nt_lock_init(NTLock* lock, bool init_unlocked);

/* If internal counter is 0, the call will block the thread. Otherwise,
 * the counter will be set to 0 and the call will be non-blocking. */
void nt_lock_lock(NTLock* lock);

/* Increases the counter to 1 and wakes the waiting threads(if they exist). */
void nt_lock_unlock(NTLock* lock);

void nt_lock_destroy(NTLock* lock);

#endif // _NT_LOCK_H_
