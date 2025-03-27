#include "nt_core/platform/nt_platform_request.h"

#include <assert.h>
#include <string.h>

void nt_platform_request_init(NTPlatformRequest* request, 
        void (*perform_func)(void* data),
        void* data, size_t data_size)
{
    assert(data_size < NT_PLATFORM_REQUEST_MAX_DATA_SIZE);

    memcpy(request->_data, data, data_size);
    request->_perform_func = perform_func;
}


