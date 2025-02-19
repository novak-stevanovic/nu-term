#include "nt_core/_nt_draw_list.h"
#include <stdlib.h>

struct DrawList draw_list;

void _draw_list_init()
{
    draw_list.head = NULL;
    draw_list.head = NULL;
}

struct DrawItem* _draw_item_create(struct NTWindow* window)
{

    struct DrawItem* new = (struct DrawItem*)malloc(sizeof(struct DrawItem*));

    new->window = window;
    new->next = NULL;

    return new;
}

void _draw_list_push_back(struct NTWindow* window)
{
    struct DrawItem* new_item = _draw_item_create(window);

    if((draw_list.head == NULL) && (draw_list.tail == NULL))
    {
        draw_list.head = new_item;
        draw_list.tail = new_item;
    }
    else if((draw_list.head != NULL) && (draw_list.tail != NULL))
    {
        draw_list.tail->next = new_item;
        draw_list.tail = new_item;
    }
}

void _draw_list_push_front(struct NTWindow* window)
{
    struct DrawItem* new_item = _draw_item_create(window);

    if((draw_list.head == NULL) && (draw_list.tail == NULL))
    {
        draw_list.head = new_item;
        draw_list.tail = new_item;
    }
    else if((draw_list.head != NULL) && (draw_list.tail != NULL))
    {
        struct DrawItem* old_head = draw_list.head;
        draw_list.head = new_item;
        new_item->next = old_head;
    }
}

void _draw_list_pop()
{
    if((draw_list.head != NULL) && (draw_list.tail != NULL))
    {
        struct DrawItem* next = draw_list.head->next;
        free(draw_list.head);
        draw_list.head = next;

        if(next == NULL) draw_list.tail = NULL;
    }
}
