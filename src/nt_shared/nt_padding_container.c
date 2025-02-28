#include "nt_base/nt_padding_container.h"
#include "nt_shared/nt_padding.h"

static void _calculate_req_size(const NTObject* object, size_t* out_width, size_t* out_height);

void nt_padding_container_init(NTPaddingContainer* padding_container, 

        void (*padding_container_calculate_children_req_size)
        (const NTPaddingContainer* padding_container,
            size_t* out_width, size_t* out_height),

        void (*container_arrange_func)(const NTContainer* container, 
            GDSArray* out_children_data))
{

    nt_container_init((NTContainer*)padding_container, _calculate_req_size, container_arrange_func);

    nt_padding_manager_init(&padding_container->_padding_manager, padding_container);

}

static void _calculate_req_size(const NTObject* object, size_t* out_width, size_t* out_height)
{
    NTPaddingContainer* _object = (NTPaddingContainer*)object;

    size_t children_width, children_height;

    _object->_padding_container_calculate_children_req_size(_object, 
            &children_width, &children_height);

   struct NTPadding* padding = nt_padding_manager_get_padding(&_object->_padding_manager);

   *out_width += nt_padding_calculate_width(padding);
   *out_height += nt_padding_calculate_height(padding);
}
