// Making a queue- a linked list with two operations, queue and dequeue.
// Queue appends to the end of the list.
// Dequeue will return the value of the first item and delete it from the list.
#include <stdio.h>
#include <stdlib.h>

struct linked_list_node {
  int value;
  struct linked_list_node* prev;
  struct linked_list_node* next;
};

struct linked_list {
  struct linked_list_node* head;
  struct linked_list_node* tail;
  int count;
};

struct linked_list* create_list() {
  struct linked_list* list = malloc(sizeof(struct linked_list));
  list->head = malloc(sizeof(struct linked_list_node));
  list->tail = malloc(sizeof(struct linked_list_node));
  list->head->next = list->tail;
  list->head->prev = NULL;
  list->tail->next = NULL;
  list->tail->prev = list->head;
  list->count = 0;
  return list;
}

void destruct_list(struct linked_list* list) {
  struct linked_list_node* node = list->head;
  int c = list->count;
  for (unsigned i = 0; i < c+1; i++) {
    struct linked_list_node* next_node = node->next;
    free(node);
    node = next_node;
  }
  free(list->tail);
  free(list);
}

void queue(struct linked_list* list, int queuee) {
  struct linked_list_node* node = malloc(sizeof(struct linked_list_node));
  node->value = queuee;
  node->next = list->tail;
  node->prev = list->tail->prev;
  list->tail->prev->next = node;
  list->tail->prev = node;
  list->count++;
}

int dequeue(struct linked_list* list) {
  struct linked_list_node* freee = list->head->next;
  int val = list->head->next->value;
  list->head->next = list->head->next->next;
  free(freee);
  list->count--;
  return val;
}

int main() {
  struct linked_list* list = create_list();
  queue(list, 3);
  queue(list, 123);
  printf("%d\n",dequeue(list));
  printf("%d\n",dequeue(list));
  // printf("%d\n", a);
  destruct_list(list);
  return 0;
}
