// Making a doubly-linked list with -append, -prepend, -search, -delete, -construct, -destruct, length of list
// gcc linked_list.c -g, lldb a.out, r

// Standard input-output library and standard library for...??
#include <stdio.h>
#include <stdlib.h>

// Start building the basic building blocks. Our 'atom' has a value and a previous and next node since we have a doubly-linked list.
// The derefence operator is declaring a variable called prev which holds the address of a struct linked_list_node type.
// prev is technically an integer since it holds a memory address.
struct linked_list_node {
  float value;
  struct linked_list_node* prev;
  struct linked_list_node* next;
};

// Create a list that holds our linked_list_node. Ours has a head and a tail that are not apart of the actual list. Also has count.
// Don't need to add values or next/prev or even assign memory to it just yet. We'll do that once we initialize.
struct linked_list {
  struct linked_list_node* head;
  struct linked_list_node* tail;
  unsigned count;
};

// Initialize a linked_list. This is a function called create_list() that returns an integer that holds the memory address of a struct linked_list.
// First, we create a variable called list whose type is an integer that holds the memory address of a struct linked_list, and that address is
// defined by malloc(sizeof(struct linked_list)).
// list->head is syntatic sugar for (*list).head, which dereferences our integer-address (pointer) named list and access the member called head.
// Remember head was also an integer-address type that holds an address of something with a struct linked_list_node type. So we assign an address to
// this variable with malloc(sizeof(struct linked_list_node)).
// We need to fully define the members. So for list->head, it also needs to have a prev and next (also value, but this is not relevant so we leave the garbage value).
// The prev/next are also a integer-address type, so we assign it NULL or another integer-address type, such as list->tail.
// Don't forget to return the list, which is technically a integer-address type of struct linked_list.
struct linked_list* create_list() {
  struct linked_list* list = malloc(sizeof(struct linked_list));
  list->head = malloc(sizeof(struct linked_list_node));
  list->tail = malloc(sizeof(struct linked_list_node));
  list->head->prev = NULL;
  list->head->next = list->tail;
  list->tail->prev = list->head;
  list->tail->next = NULL;
  list->count = 0;
  return list;
}

// This function returns nothing, and takes in an integer-address of type struct linked_list, which we will call list.
// We define a variable which is an integer-address of type struct linked_list_node, which we will call node,
// and to this node we will assign the integer-address of list->head.
// Then while node->next exists- which means it will stop when node = list->tail since list->tail->next = NULL.
// While it goes on, assign our variable node as node->next and free (opposite of malloc) the previous node.
// Because there is nothing after tail, we won't end up freeing tail so we free it after the loop.
// Finally we free the list. It is important to free the molecular elements first, or else we will end up freeing the list,
// and not having the address to its molecular elements to free.
void destruct_list(struct linked_list* list) {
  struct linked_list_node* node = list->head;
  int i = 0;
  while (node->next) {
    node = node->next;
    free(node->prev);
  }
  free(list->tail);
  free(list);
}

// In order to avoid having to loop through the enitre list each time we need a count O(n), we use list->count.
int len(struct linked_list* list) {
  // struct linked_list_node* node = list->head;
  // int i = 0;
  // while (node->next) {
  //   i++;
  //   node = node->next;
  // }
  // return i-1;
  return list->count;
}

// Need to append a node to the list, so we create the address for the node,
// fill in the necessary members for it, and "add" it to the list.
// It is added by setting the next member node of the last node to this new node,
// and setting the prev member node of the tail node to this new node.
void append(struct linked_list* list, float appendee) {
  struct linked_list_node* node = malloc(sizeof(struct linked_list_node));
  node->value = appendee;
  node->prev = list->tail->prev;
  node->next = list->tail;
  list->tail->prev->next = node;
  list->tail->prev = node;
  list->count++;
}

// Same idea as above, but set the prev node of the first node to our new node,
// and the next node of our head node to our new node.
void prepend(struct linked_list* list, float appendee) {
  struct linked_list_node* node = malloc(sizeof(struct linked_list_node));
  node->value = appendee;
  node->prev = list->head;
  node->next = list->head->next;
  list->head->next->prev = node;
  list->head->next = node;
  list->count++;
}

// To delete a node, we need to create an integer-address variable called node and have it point to the first node.
// We loop for index number of times. Once we in the loop, we need to check if our index # exceeds the number
// of nodes we have, and we check this by checking if the next node is the tail node, which means it is at the last
// node and we cannot go to the next node. But, we should be able to land on the final node if we have an
// index number within bounds of our node count, so the last possible node will be the second to last node.
// Once we get to our desired node, we set the next node of the node previous to our node to the node next of us.
// We then set the prev node of the next node to the node previous to us.
// Then we free the node and lower the count.
void delete(struct linked_list* list, unsigned index) {
  struct linked_list_node* node = list->head->next;
  for (unsigned i=0; i<index; i++) {
    if (node->next == list->tail) {
      printf("Out of index.");
      return;
    }
    node = node->next;
  }
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);
  list->count--;
}

// To return a value when given index, we need to a O(n) search.
// So we define a variable for the first node of our list. Then loop for index number of times.
// Check if index is out of range.
// Then once we get to our node, return the value.
float get(struct linked_list* list, unsigned index) {
  struct linked_list_node* node = list->head->next;
  for (unsigned i=0; i<index; i++) {
    if (node->next == list->tail) {
      printf("Out of index.");
      return 0;
    }
    node = node->next;
  }
  return node->value;
}

// Create the main function which the processor enters.
// First create a variable called my_list that holds an integer-address of struct linked_list.
// Add stuff, delete stuff, prepend stuff, destroy etc.
int main() {
  struct linked_list* my_list = create_list();
  append(my_list, 3);
  prepend(my_list, 2.3);
  delete(my_list, 0);
  printf("%f\n", get(my_list, 0));
  printf("%d\n", len(my_list));
  destruct_list(my_list);
  return 0;
}
