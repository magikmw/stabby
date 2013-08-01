#include "ds.h"
#include <string.h>

/* Add an item with given value (size - sizeof(something)) after the node 'before' */
void list_insert(list_p list, lnode_p before, void *data, int size)
{
    if (list->first == NULL) {
        list_add(list, data, size);
    } 
    else if (before == list->last) {
        list_add(list, data, size);
    }
    else if (before == NULL) {
        lnode_p node = (lnode_p)malloc(sizeof(struct linked_node));
        node->data = malloc(size);
        memcpy(node->data, data, size);

        node->next = list->first;
        node->prev = NULL;
        node->next->prev = node;
        list->first = node;
        list->length++;
    }
    else {
        lnode_p node = (lnode_p)malloc(sizeof(struct linked_node));
        node->data = malloc(size);
        memcpy(node->data, data, size);

        node->next = before->next;
        node->prev = before;
        before->next = node;
        node->next->prev = node;
        list->length++;
    }
}