#include "nt_core/_nt_draw_list.h"
#include <stdlib.h>

static NTDrawItem* _nt_draw_list_item_create(NTWindow* window)
{

    NTDrawItem* new = (NTDrawItem*)malloc(sizeof(NTDrawItem*));

    new->window = window;
    new->next = NULL;

    return new;
}

// ------------------------------------------------------------------------------------------

void _nt_draw_list_init(NTDrawList* draw_list)
{
    draw_list->head = NULL;
    draw_list->head = NULL;
}

void _nt_draw_list_push_back(NTDrawList* draw_list, NTWindow* window)
{
    NTDrawItem* new_item = _nt_draw_list_item_create(window);

    if((draw_list->head == NULL) && (draw_list->tail == NULL))
    {
        draw_list->head = new_item;
        draw_list->tail = new_item;
    }
    else if((draw_list->head != NULL) && (draw_list->tail != NULL))
    {
        draw_list->tail->next = new_item;
        draw_list->tail = new_item;
    }
}

void _nt_draw_list_push_front(NTDrawList* draw_list, NTWindow* window)
{
    NTDrawItem* new_item = _nt_draw_list_item_create(window);

    if((draw_list->head == NULL) && (draw_list->tail == NULL))
    {
        draw_list->head = new_item;
        draw_list->tail = new_item;
    }
    else if((draw_list->head != NULL) && (draw_list->tail != NULL))
    {
        NTDrawItem* old_head = draw_list->head;
        draw_list->head = new_item;
        new_item->next = old_head;
    }
}

void _nt_draw_list_pop_front(NTDrawList* draw_list)
{
    if((draw_list->head != NULL) && (draw_list->tail != NULL))
    {
        NTDrawItem* next = draw_list->head->next;
        free(draw_list->head);
        draw_list->head = next;

        if(next == NULL) draw_list->tail = NULL;
    }
}

NTWindow* _nt_draw_list_get_head(NTDrawList* draw_list)
{
    if(draw_list->head == NULL) return NULL;
    else return draw_list->head->window;
}
