#ifndef _NT_PLATFORM_H_
#define _NT_PLATFORM_H_

#include <stdlib.h>

#define nt_platform

typedef struct NTPlatformRequest NTPlatformRequest;

/* -------------------------------------------------------------------------- */

/* NTPlatform is a module that allows for GUI updates to run on the designated
 * NTPlatform thread. Any changes to any GUI element(any NTObject) should
 * be performed via the nt_platform_execute() function(except NTObject
 * initialization). This also applies to changes to NTDisplay buffer.
 * This is done to avoid race conditions. */

void _nt_platform_init();

/* -------------------------------------------------------------------------- */


void _nt_platform_destroy();

/* -------------------------------------------------------------------------- */

/* Adds a request to the queue for execution. If this function was called
 * from NTPlatformThread, the request will be processed immediately. Otherwise,
 * the request will be processed after all queued requests have been processed.
 *
 * Thread-safe. */
void nt_platform_execute(NTPlatformRequest* request);

/* -------------------------------------------------------------------------- */

/* NTPlatform offers the possibility of designating NTPlatformRequest 'slots' 
 * that may be written to. Writing to these slots is both thread-safe and
 * async-safe. NTDisplay utilizes this to update display size. 
 *
 * If there are unprocessed requests in any of the existing slots,
 * they will always be processed before the requests from the queue
 * (nt_platform_execute).
 *
 * When writing to a slot, if the previous request still hasn't been processed,
 * it will be overwritten. This is also useful in terms of updating the display
 * size. In any case(overwriting or just writing), the NTPlatform thread will
 * be woken up and will resume the request processing. */
#define NT_PLATFORM_MAX_ASYNC_SLOTS 10

typedef struct NTPlatformRequestSlot NTPlatformRequestSlot;

// TODO: add error-handling
NTPlatformRequestSlot* nt_platform_designate_slot();
void nt_platform_write_to_slot(const NTPlatformRequest* request, NTPlatformRequestSlot* slot);
void nt_platform_depose_slot(NTPlatformRequestSlot* slot);

#endif // _NT_PLATFORM_H_
