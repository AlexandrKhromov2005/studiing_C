#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} node_t;

void pushback(node_t **head, int val) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->val = val;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node_t *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print(node_t * head){
    if (head == NULL) {
        printf("list is empty\n");
        return;
    }

    node_t * current = head;
    while (current->next != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("%d\n", current->val);
}

void pushfront(node_t **head, int val) {
    node_t * new_head = (node_t *) malloc(sizeof(node_t));
    new_head->val = val;
    new_head->next = *head;
    *head = new_head;
}

void popback(node_t **head) {
    if (*head == NULL) {
        return;  // Список пуст, ничего не делаем
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    node_t *current = *head;
    node_t *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    free(current);
    prev->next = NULL;
}

void popfront(node_t **head) {
    node_t * new_head = (*head) ->next;
    free(*head);
    *head = new_head;
}

void clearMemory(node_t **head) {
    while (*head != NULL) {
        popfront(head);
    }
}

int getValByIndex(node_t **head, int index) {
    if (head == NULL) {
        printf("list is empty\n");
        return -1;
    } 

    node_t * current = *head;

    while (current != NULL && index > 0) {
        current = current->next;
        index--;
    }

    if (current == NULL) {
        printf("index %d is ou tof range\n", index);
        return -2;
    } 
    else {
        return current->val;
    }
}

void popNodeByIndex(node_t **head, int index) {
    if (*head == NULL) {
        printf("list is empty\n");
        return;
    }

    node_t *current = *head;
    node_t *prev = NULL;

    while (current != NULL && index > 0) {
        prev = current;
        current = current->next;
        index--;
    }

    if (current == NULL) {
        printf("index %d is out of range\n", index);
        return;
    } else {
        if (prev == NULL) {
            // Удаляем голову списка
            *head = current->next;
        } else {
            // Удаляем элемент из середины или конца списка
            prev->next = current->next;
        }
        free(current);
    }
}

int listLen(node_t * head){
    if (head == NULL) {
        return 0;
    }

    node_t * current = head;
    int len = 1;
    while (current->next != NULL) {
        len++;
        current = current->next;
    }
    return len;
}


int main() {
    node_t *head = NULL;

    for (int i = 0; i < 5; i++) {
        pushback(&head, i);
    }

    for (int i = -1; i > -5; i--) {
        pushfront(&head, i);
    }

    popback(&head);

    popfront(&head);

    print(head);

    printf("length is %d\n", listLen(head));

    printf("on the 3rd position is %d\n", getValByIndex(&head, 3));

    popNodeByIndex(&head, 3);

    print(head);

    clearMemory(&head);

    print(head);

    printf("length is %d\n", listLen(head));
    

    return 0;
}