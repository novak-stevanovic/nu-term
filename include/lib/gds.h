#ifndef GDS_H
#define GDS_H

/* -----------------------------------------------------------------------------------------------------------------------------------------------

  * GDS(Generic Data Structures) is a C library designed to aid C developers in their development process by providing them with data structures
  * they can use throughout their projects. Besides efficiency, this library prides itself with robust error and program consistency checks.
  * All functions return crystal clear error codes, with each module(data structure) having a local scope for its error codes. The library
  * utilizes defensive programming to its maximum capacity by making sure that long, "procedurally-designed" functions perform defensive checks
  * each step of the way.
  *
  * Error Handling ---------------------------------------------------------------------------------------------------------------------------------
  *
  * Each data structure has a base value for its error codes(for example, GDSArray has 1000 as its base value). Some functions will return
  * simple indicators that the function failed(for example, NULL or -1, indicating a NULL argument). More complex functions will return
  * error codes. These functions have their own error code base values(for example gds_array_assign() has a base value of 10, built upon
  * the 1000 for GDSArray - meaning 1010). These error codes provide a way for the program to tell the user what went wrong. Most of these
  * refer to user error, for example, appending to the array when its at its max capacity.
  *
  * Error codes that have 'FERR' in them indicate that the error is fatal - the state of the data structure is compromised. These error codes
  * exist but may never happen.
  *
  * However, some of the error codes, denoted by the _ prefix in the macro definition, occur when the program fails due to invalid program 
  * state(perhaps happening due to an unhandled situation in the library source code). The library, by default, won't check for them and won't
  * return them. This is because, if these situations occur, it can be assumed that the library behavior is at fault.
  * A user may decide to enable them, find the error and fix the error for himself.
  * For exmaple, in theory, gds_vec_at() function must not fail if given the correct parameters) - but gds_vec_assign() will
  * perform the check nonetheless. A user may also decide to enable these checks if every bit of robustness is valued - while a small
  * decrement in performance is not an issue. To enable this, uncomment the macro below(GDS_ENABLE_ROBUST_CHECKS) and recompile the library.
  *
  * Struct opaqueness ------------------------------------------------------------------------------------------------------------------------------
  *
  * Each data structure is nicely encapsulated by making the struct itself opaque. As such, the definitions are found in the corresponding .c files.
  * However, if the user wishes for more control, he may want to make the structs not opaque. This can be done by uncommenting the macro below
  * (GDS_DISABLE_OPAQUE_STRUCTS) and recompiling the library.

* ------------------------------------------------------------------------------------------------------------------------------------------------ */

// #define GDS_ENABLE_ROBUST_CHECKS
// #define GDS_DISABLE_OPAQUE_STRUCTS

#ifdef GDS_ENABLE_ROBUST_CHECKS
#define gds_rcheck(condition, ret_val) if(!(condition)) return (ret_val)
#else
#define gds_rcheck(condition, ret_val)  
#endif // GDS_ENABLE_ROBUST_CHECKS

#endif // GDS_H
