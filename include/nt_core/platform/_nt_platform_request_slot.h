#ifndef __NT_PLATFORM_REQUEST_SLOT_H__
#define __NT_PLATFORM_REQUEST_SLOT_H__ 

#include "nt_core/platform/nt_platform_request.h"
#include "nt_shared/nt_lock.h"

typedef struct NTPlatformRequestSlot
{
    NTLock _lock;
    bool _empty;
    NTPlatformRequest _request;
    bool _occupied;
} NTPlatformRequestSlot;

void nt_platform_request_slot_init(NTPlatformRequestSlot* slot);
void nt_platform_request_slot_destroy(NTPlatformRequestSlot* slot);

void nt_platform_request_slot_designate(NTPlatformRequestSlot* slot);

void nt_platform_request_slot_write(NTPlatformRequestSlot* slot,
        const NTPlatformRequest* request);

void nt_platform_request_slot_is_occupied(NTPlatformRequestSlot* slot,
        bool* out_occupied);

void nt_platform_request_slot_is_empty(NTPlatformRequestSlot* slot,
        bool* out_empty);

void nt_platform_request_slot_depose(NTPlatformRequestSlot* slot);

void nt_platform_request_slot_get_request_copy(NTPlatformRequestSlot* slot,
        NTPlatformRequest* out_request);

#endif // __NT_PLATFORM_REQUEST_SLOT_H__
