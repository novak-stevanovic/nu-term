#ifndef _NT_DRAW_LIST_H_
#define _NT_DRAW_LIST_H_

struct DrawItem
{
    struct NTWindow* window;
    struct DrawItem* next;
};

struct DrawList
{
    struct DrawItem *head, *tail;
};

extern struct DrawList draw_list;

// ----------------------------------------------------------------------------------------------------------------------------

void _draw_list_init();

struct DrawItem* _draw_item_create(struct NTWindow* window);

void _draw_list_push_back(struct NTWindow* window);

void _draw_list_push_front(struct NTWindow* window);

void _draw_list_pop();

// ----------------------------------------------------------------------------------------------------------------------------


#endif // _NT_DRAW_LIST_H_

