#ifndef NT_PADDING_MANAGER_H
#define NT_PADDING_MANAGER_H

#include "nt_shared/nt_padding.h"

struct NTPaddingContainer;
typedef struct NTPaddingContainer NTPaddingContainer;

typedef struct NTPaddingManager
{
    struct NTPadding _padding;

    NTPaddingContainer* _container;
} NTPaddingManager;

void nt_padding_manager_init(NTPaddingManager* padding_manager, NTPaddingContainer* container);

struct NTPadding* nt_padding_manager_get_padding(NTPaddingManager* padding_manager);

void nt_padding_manager_apply(NTPaddingManager* padding_manager);

//static 
size_t _nt_padding_manager_get_content_width(NTPaddingManager* padding_manager);
//static 
size_t _nt_padding_manager_get_content_height(NTPaddingManager* padding_manager);

#endif // NT_PADDING_MANAGER_H
