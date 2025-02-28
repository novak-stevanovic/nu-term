#include "nt_shared/nt_padding_manager.h"

void nt_padding_manager_init(NTPaddingManager* padding_manager, NTPaddingContainer* container)
{
    padding_manager->_container = container;

    nt_padding_init_default(&padding_manager->_padding);
}

struct NTPadding* nt_padding_manager_get_padding(NTPaddingManager* padding_manager)
{
    return &padding_manager->_padding;
}

void nt_padding_manager_apply(NTPaddingManager* padding_manager)
{
    // TODO 
}
