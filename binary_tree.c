// Binary search tree with insert, delete, and search
#include <stdio.h>
#include <stdlib.h>

// Create a binary tree node which has a left and right direction.
struct binary_tree_node {
  int key;
  char* value;
  struct binary_tree_node* left;
  struct binary_tree_node* right;
};

// Create a binary tree that has a binary tree node called root.
struct binary_tree {
  struct binary_tree_node* root;
};

// Initialize the bst by defining a root.
struct binary_tree* create_bst() {
  struct binary_tree* bst = malloc(sizeof(struct binary_tree));
  bst->root = malloc(sizeof(struct binary_tree_node));
  bst->root->key = NULL;
  bst->root->value = NULL;
  bst->root->left = NULL;
  bst->root->right = NULL;
  return bst;
}

// To insert, we compare the key until the bst node is null, meaning that there is nothing
// in the root, left, or right of the previous node from which it was sent.
// This is a recursive function.
// Also, before we send it to the left we need to create the node if is null.
void insert(struct binary_tree_node* bst_node, int key, char* value) {
  if (bst_node->key == NULL) {
    bst_node->key = key;
    bst_node->value = value;
  } else if (key < bst_node->key) {
    if (bst_node->left == NULL) {
      bst_node->left = malloc(sizeof(struct binary_tree_node));
      bst_node->left->key = NULL;
      bst_node->left->value = NULL;
      bst_node->left->left = NULL;
      bst_node->left->right = NULL;
    }
    insert(bst_node->left, key, value);
  } else {
    if (bst_node->right == NULL) {
      bst_node->right = malloc(sizeof(struct binary_tree_node));
      bst_node->right->key = NULL;
      bst_node->right->value = NULL;
      bst_node->right->left = NULL;
      bst_node->right->right = NULL;
    }
    insert(bst_node->right, key, value);
  }
}

// To search, we do something similar, in that if the key is equal then return,
// and if not keep going left or right. This is where we dereference the key,
// and that's why it can't be null.
char* search(struct binary_tree_node* bst_node, int key) {
  if (bst_node->key == key) {
    printf("%s\n", bst_node->value);
    return bst_node->value;
  } else if (key < bst_node->key) {
    search(bst_node->left, key);
  } else {
    search(bst_node->right, key);
  }
}

// Traverse from the root. Then print the left of the root. Then prints left if that has a left,
// and so it does a depth first traverse.
// We add tabs for the level of depth it has gone. Once it finishes the left and goes to the right,
// the count is preserved as a different one so it works out.
void traverse(struct binary_tree_node* bst_node, unsigned count) {
  for (unsigned x=0; x<count; x++) {
    printf("\t");
  }
  printf("%s\n", bst_node->value);

  if (bst_node->left != NULL) {
    traverse(bst_node->left, count+1);
  }
  if (bst_node->right != NULL) {
    traverse(bst_node->right, count+1);
  }
}

int main() {
  struct binary_tree* bst = create_bst();
  insert(bst->root, 3, "Foot");
  insert(bst->root, 1, "Stewart");
  insert(bst->root, 2, "Grace");
  insert(bst->root, 4, "Job");
  insert(bst->root, 5, "Burrito");
  traverse(bst->root, 0);
  return 0;
}
