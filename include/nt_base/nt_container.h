#ifndef NT_CONTAINER_H
#define NT_CONTAINER_H

#include "nt_base/nt_object.h"
#include "gds_vector.h"

struct GDSArray;
typedef struct GDSArray GDSArray;

struct NTWindow;
typedef struct NTWindow NTWindow;

typedef struct NTContainer
{
    NTObject _base;

    NTWindow* _background;
    GDSVector _children;

    // Fills 'out_children_data' array with draw data information
    // for each child
    void (*_container_arrange_func)(const NTContainer* container, 
            struct GDSArray* out_children_data);
    
} NTContainer;

void nt_container_init(NTContainer* container, 

        void (*object_calculate_req_size_func)(const NTObject* object,
            size_t* out_width, size_t* out_height),

        void (*container_arrange_func)(const NTContainer* container, 
            GDSArray* out_children_data));

const GDSVector* nt_container_get_children(const NTContainer* container);

NTWindow* nt_container_get_background(NTContainer* container);

void nt_container_set_background(NTContainer* container, NTWindow* new_background);

void nt_container_position_child(NTObject* child, const NTBounds* new_bounds);

#endif // NT_CONTAINER_H
