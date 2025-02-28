#ifndef _NT_DRAW_LIST_H_
#define _NT_DRAW_LIST_H_

struct NTWindow;
typedef struct NTWindow NTWindow;

typedef struct NTDrawItem
{
    NTWindow* window;
    struct NTDrawItem* next;
} NTDrawItem;

typedef struct NTDrawList
{
    NTDrawItem *head, *tail;
} NTDrawList;

// ----------------------------------------------------------------------------------------------------------------------------

void _nt_draw_list_init(NTDrawList* draw_list);

void _nt_draw_list_push_back(NTDrawList* draw_list, NTWindow* window);

void _nt_draw_list_push_front(NTDrawList* draw_list, NTWindow* window);

void _nt_draw_list_pop_front(NTDrawList* draw_list);

NTWindow* _nt_draw_list_get_head(NTDrawList* draw_list);

// ----------------------------------------------------------------------------------------------------------------------------

#endif // _NT_DRAW_LIST_H_

