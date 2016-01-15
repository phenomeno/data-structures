// Defining a min heap using an array.
#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

struct heap {
  int count;
  int bh[HEAP_SIZE];
};

struct heap* create_bh() {
  struct heap* heap = malloc(sizeof(struct heap));
  heap->count = 0;
  return heap;
}

void bubble_up(int* arr, int i, int value) {
  int p = (i-1)/2;
  if (i == 0) {
    return;
  }
  if (arr[p] > value) {
    arr[i] = arr[p];
    arr[p] = value;
    bubble_up(arr, p, value);
  } else {
    arr[i] = value;
  }
}

void insert(struct heap* heap, int value) {
  if (heap->count == 0) {
    heap->bh[0] = value;
  } else {
    bubble_up(heap->bh, heap->count, value);
  }
  heap->count++;
}

void traverse(struct heap* heap) {
  for (int i=0; i<heap->count; i++) {
    printf("Order%d\n", i);
    printf("%d\n", heap->bh[i]);
  }
}

void bubble_down(int* arr, int node_index, int last_node) {
  // Find greater child of the node_index
  // If left node is less than right node
  int lesser_node = NULL;
  if (arr[node_index*2+1] == INT_MIN)
    return;
  if (arr[node_index*2+1] <= arr[node_index*2+2])
    lesser_node = node_index*2+1;
  else
    lesser_node = node_index*2+2;
  // Compare last element with lesser child ()
  // if new element is greater, then than greater child, then pass bubble own the array and the child eleemnt index
  printf("arrlast_node %d\n", last_node);
  if (last_node > arr[lesser_node]) {
    arr[node_index] = arr[lesser_node];
    arr[lesser_node] = last_node;
    bubble_down(arr, lesser_node, last_node);
  } else {
    // if new element is greater than set new element to the index of the greater chil and siwtch
    return;
  }
}

// Delete minimum value
void extract(struct heap* heap) {
  if (heap->count == 0) {
    return;
  }
  heap->bh[0] = NULL;
  int last_node = heap->bh[heap->count-1];
  heap->bh[heap->count-1] = INT_MIN;
  heap->count--;
  bubble_down(heap->bh, 0, last_node);
}

int main() {
  struct heap* heap = create_bh();
  insert(heap, 3);
  printf("first\n");
  traverse(heap);
  insert(heap, 5);
  printf("second\n");
  traverse(heap);
  insert(heap, 6);
  printf("third\n");
  traverse(heap);
  insert(heap, 199);
  printf("4th\n");
  traverse(heap);
  insert(heap, 1);
  printf("5third\n");
  traverse(heap);
  insert(heap, 200);
  printf("6third\n");
  traverse(heap);
  insert(heap, 7);
  printf("first traverse\n");
  traverse(heap);
  extract(heap);
  printf("second traverse\n");
  traverse(heap);
  return 0;

}
