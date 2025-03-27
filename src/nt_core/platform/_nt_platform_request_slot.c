#include "nt_core/platform/_nt_platform_request_slot.h"

#define SLOT_LOCK(slot) nt_lock_lock(&slot->_lock)
#define SLOT_UNLOCK(slot) nt_lock_unlock(&slot->_lock)

void nt_platform_request_slot_init(NTPlatformRequestSlot* slot)
{
    slot->_empty = true;
    slot->_occupied = false;

    nt_lock_init(&slot->_lock, true);
}

void nt_platform_request_slot_destroy(NTPlatformRequestSlot* slot)
{
    slot->_empty = true;
    slot->_occupied = false;

    nt_lock_destroy(&slot->_lock);
}

void nt_platform_request_slot_designate(NTPlatformRequestSlot* slot)
{
    SLOT_LOCK(slot);

    slot->_occupied = true;

    SLOT_UNLOCK(slot);
}

void nt_platform_request_slot_write(NTPlatformRequestSlot* slot,
        const NTPlatformRequest* request)
{
    SLOT_LOCK(slot);

    slot->_request = *request;
    slot->_empty = false;

    SLOT_UNLOCK(slot);
}

void nt_platform_request_slot_is_occupied(NTPlatformRequestSlot* slot,
        bool* out_occupied)
{
    SLOT_LOCK(slot);

    if(out_occupied != NULL) *out_occupied = slot->_occupied;

    SLOT_UNLOCK(slot);
}

void nt_platform_request_slot_is_empty(NTPlatformRequestSlot* slot,
        bool* out_empty)
{
    SLOT_LOCK(slot);

    if(out_empty != NULL) *out_empty = slot->_empty;

    SLOT_UNLOCK(slot);
}

void nt_platform_request_slot_depose(NTPlatformRequestSlot* slot)
{
    SLOT_LOCK(slot);

    slot->_occupied = false;
    slot->_empty = true;

    SLOT_UNLOCK(slot);
}

void nt_platform_request_slot_get_request_copy(NTPlatformRequestSlot* slot,
        NTPlatformRequest* out_request)
{
    SLOT_LOCK(slot);

    *out_request = slot->_request;

    SLOT_UNLOCK(slot);
}
