#ifndef GDS_H
#define GDS_H

// TODO add restrict to func params and inline to func signatures
// TODO check error codes for everything
// TODO bring back GDS and GDSE naming
// TODO test light vector and other stuff

// ------------------------------------------------------------------------------------------------------------------------------------

/* GDS(Generic Data Structures) is a C library designed to aid C developers in their development process by
providing them with data structures they can use throughout their projects. Besides efficiency, the focus
for most of these data structures is on user-control, allowing the programmer using this 
library to do what he wants, excatly how he wants it. */

// Error Handling ----------------------------------------------------------------------------------------------------------

/* Some functions return error codes. There are a number of generic error codes defined below.
1. GDS_GEN_ERR_INCONSISTENT_ARGS - this is returned when there is a mismatch in multiple arguments sent 
to a function. For example, this value may be returned from a function that accepts parameters start_pos
and end_pos, where end_pos must be greater than start_pos.

2. GDS_GEN_ERR_INVALID_ARG - refers to the case where a call to a function has been performed,
while providing an invalid argument. Why the argument may be invalid, depends on the function in 
question - perhaps it was a NULL pointer, perhaps it was an invalid number. The function will return
a value, x being the 'index' of the invalid argument(starting from 1). 

3. GDS_GEN_ERR_INERNAL_ERR - refers to the case where a function in the API relies on a call to an internal
function which failed. In this case, the library is at fault. The API doesn't mention this error because it
is a valid return value for functions that return gds_err by default. */

typedef int gds_err;

#define GDS_SUCCESS 0
#define GDS_FAILURE -1

#define _GDS_GEN_ERR_BASE 1000

#define _GDS_GEN_ERR_INVALID_ARG_BASE (_GDS_GEN_ERR_BASE + 10)
#define GDS_GEN_ERR_INCONSISTENT_ARGS (_GDS_GEN_ERR_INVALID_ARG_BASE + 0)
#define GDS_GEN_ERR_INVALID_ARG(x) (_GDS_GEN_ERR_INVALID_ARG_BASE + x)
#define GDS_GEN_ERR_INTERNAL_ERR 1002

// Struct opaqueness ------------------------------------------------------------------------------------------------------

/* Each data structure is nicely encapsulated by making the struct itself opaque. As such, the definitions are 
found in the corresponding .c files. However, if the user wishes for more control, he may want to make the 
structs not opaque. This can be done by commenting the macro below (GDS_ENABLE_OPAQUE_STRUCTS). */

// #define GDS_ENABLE_OPAQUE_STRUCTS

// ------------------------------------------------------------------------------------------------------------------------------------

#endif // GDS_H
