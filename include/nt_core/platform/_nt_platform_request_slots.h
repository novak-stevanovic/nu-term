#ifndef __NT_PLATFORM_REQUEST_SLOTS_H__
#define __NT_PLATFORM_REQUEST_SLOTS_H__

#include "nt_core/platform/_nt_platform_request_slot.h"

#define NT_PLATFORM_REQUEST_SLOTS_COUNT 10

typedef struct NTPlatformRequestSlots
{
    NTPlatformRequestSlot _slots[NT_PLATFORM_REQUEST_SLOTS_COUNT];
} NTPlatformRequestSlots;

void nt_platform_request_slots_init(NTPlatformRequestSlots* slots);
void nt_platform_request_slots_destroy(NTPlatformRequestSlots* slots);

NTPlatformRequestSlot* nt_platform_request_slots_get_slot_at
(NTPlatformRequestSlots* slots, size_t idx);

NTPlatformRequestSlot* nt_platform_request_slots_get_unoccupied
(NTPlatformRequestSlots* slots);

#endif // __NT_PLATFORM_REQUEST_SLOTS_H__
