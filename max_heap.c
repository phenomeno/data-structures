// Defining a max heap using an array.
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
  if (arr[p] <= value) {
    arr[i] = arr[p];
    arr[p] = value;
    bubble_up(arr, p, value);
  } else {
    arr[i] = value;
    return;
  }
}

void insert(struct heap* heap, int value) {
  if (heap->count == 0) {
    heap->bh[0] = value;
    heap->count++;
    return;
  }
  bubble_up(heap->bh, heap->count, value);
  heap->count++;
}

void traverse(struct heap* heap) {
  for (int i=0; i<heap->count; i++) {
    printf("Order%d\n", i);
    printf("%d\n", heap->bh[i]);
  }
}

void bubble_down(int* arr, int node_index, int count) {
  // Find greater child of the node_index
  // If left node is greater than right node
  int greater_node = NULL;
  if (arr[node_index*2+1] >= arr[node_index*2+2])
    greater_node = node_index*2+1;
  else
    greater_node = node_index*2+2;
  // Compare last element with greater child ()
  // if new element is less, then than greater child, then pass bubble own the array and the child eleemnt index
  if (arr[count] < arr[greater_node]) {
    arr[node_index] = arr[greater_node];
    arr[greater_node] = arr[count];
    bubble_down(arr, greater_node, count);
  } else {
    // if new element is greater than set new element to the index of the greater chil and siwtch
    return;
  }
}

// Delete maximum value
void extract(struct heap* heap) {
  if (heap->count == 0) {
    return;
  }
  heap->bh[0] = NULL;
  bubble_down(heap->bh, 0, heap->count);
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
  printf("first traverse");
  traverse(heap);
  extract(heap);
  printf("second traverse");
  traverse(heap);
  return 0;

}
