#ifndef NT_PADDING_CONTAINER_H
#define NT_PADDING_CONTAINER_H

#include "nt_base/nt_container.h"
#include "nt_shared/nt_padding_manager.h"

typedef struct NTPaddingContainer
{
    NTContainer _base;
    NTPaddingManager _padding_manager;

    void (*_padding_container_calculate_children_req_size)(
            const struct NTPaddingContainer* padding_container,
            size_t* out_width, size_t* out_height);

} NTPaddingContainer;

void nt_padding_container_init(NTPaddingContainer* padding_container, 

        void (*padding_container_calculate_children_req_size)
        (const NTPaddingContainer* padding_container,
         size_t* out_width, size_t* out_height),

        void (*container_arrange_func)(const NTContainer* container, 
            GDSArray* out_children_data));

#endif // NT_PADDING_CONTAINER_H
