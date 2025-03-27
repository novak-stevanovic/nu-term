#include "nt_core/platform/_nt_platform_request_slots.h"
#include <assert.h>

void nt_platform_request_slots_init(NTPlatformRequestSlots* slots)
{
    size_t i;
    for(i = 0; i < NT_PLATFORM_REQUEST_SLOTS_COUNT; i++)
    {
        nt_platform_request_slot_init(&slots->_slots[i]);
    }
}

void nt_platform_request_slots_destroy(NTPlatformRequestSlots* slots)
{
    size_t i;
    for(i = 0; i < NT_PLATFORM_REQUEST_SLOTS_COUNT; i++)
    {
        nt_platform_request_slot_destroy(&slots->_slots[i]);
    }
}

NTPlatformRequestSlot* nt_platform_request_slots_get_slot_at
(NTPlatformRequestSlots* slots, size_t idx)
{
    assert(idx < NT_PLATFORM_REQUEST_SLOTS_COUNT);

    return &slots->_slots[idx];
}

NTPlatformRequestSlot* nt_platform_request_slots_get_unoccupied
(NTPlatformRequestSlots* slots)
{
    size_t i;
    bool occupied;
    for(i = 0; i < NT_PLATFORM_REQUEST_SLOTS_COUNT; i++)
    {
        nt_platform_request_slot_is_occupied(&slots->_slots[i], &occupied);

        if(!occupied) return &slots->_slots[i];
    }

    return NULL;
}
