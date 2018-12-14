//
// Created by Alexandra Zaharia on 13/12/18.
//

#include <stdio.h>
#include "linked_list.h"

void print(LinkedList* list)
{
    if (!list || !list->head) return;
    Node* node = list->head;
    while (node) {
        printf("%d ", *((int*) node->data));
        node = node->next;
    }
    printf("\n");
}

int main()
{
    LinkedList* list = linked_list_create();
    int status;
    int values[] = {2, 1, 3, 0, 5, 4};

    status = list->insert_start(list, &values[0]); printf("%d: | ", status); print(list);
    status = list->insert_start(list, &values[1]); printf("%d: | ", status); print(list);
    status = list->insert_end(list, &values[2]); printf("%d: | ", status); print(list);
    status = list->insert_at(list, &values[3], 0); printf("%d: | ", status); print(list);
    status = list->insert_at(list, &values[4], -1); printf("%d: | ", status); print(list);
    status = list->insert_at(list, &values[4], 5); printf("%d: | ", status); print(list);
    status = list->insert_at(list, &values[4], 4); printf("%d: | ", status); print(list);
    status = list->insert_at(list, &values[5], 4); printf("%d: | ", status); print(list);
    status = *((int*) list->remove_start(list)); printf("Removed %d: | ", status);// print(list);
    status = *((int*) list->remove_end(list)); printf("Removed %d: | ", status); //print(list);

    list->free(list);
}