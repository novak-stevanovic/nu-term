#ifndef NT_OBJECT_H
#define NT_OBJECT_H

#include <stdlib.h>
#include <stdbool.h>

#include "nt_base/nt_bounds.h"

#define NT_OBJECT_DEFAULT_MIN_SIZE 0
#define NT_OBJECT_DEFAULT_MAX_SIZE 100000

#define NT_OBJECT_PREF_SIZE_UNSPECIFIED -1

typedef struct NTContainer NTContainer;

typedef struct NTObject
{
    NTContainer* _parent;

    // NTConstraints _constraints; // min and max sizes
    size_t _min_width, _min_height;
    size_t _max_width, _max_height;
    ssize_t _pref_width, _pref_height;

    size_t _required_width; 
    size_t _required_height;

    void (*_object_calculate_req_size_func)(const struct NTObject* object,
            size_t* out_width, size_t* out_height);

    NTBounds _bounds; 

    void (*_object_arrange_func)(struct NTObject* object);

    void (*_object_display_func)(struct NTObject* object);

    bool _tainted;

} NTObject;

void nt_object_init(NTObject* object, 

    void (*object_calculate_req_size_func)(const struct NTObject* object,
            size_t* out_width, size_t* out_height),

    void (*object_arrange_func)(struct NTObject* object),

    void (*object_display_func)(struct NTObject* object));

void nt_object_arrange(NTObject* object);

void nt_object_display(NTObject* object);

void nt_object_update_required_size(NTObject* object);

const NTBounds* nt_object_get_bounds(const NTObject* object);

size_t nt_object_calculate_abs_start_x(const NTObject* object);
size_t nt_object_calculate_abs_start_y(const NTObject* object);
size_t nt_object_calculate_abs_end_x(const NTObject* object);
size_t nt_object_calculate_abs_end_y(const NTObject* object);
NTBounds nt_object_calculate_abs_bounds(const NTObject* object);

size_t nt_object_get_min_width(const NTObject* object);
size_t nt_object_get_min_height(const NTObject* object);
size_t nt_object_get_max_width(const NTObject* object);
size_t nt_object_get_max_height(const NTObject* object);

void nt_object_set_position(NTObject* object, const NTBounds* new_bounds);

#endif // NT_OBJECT_H
