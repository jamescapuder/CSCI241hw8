#ifndef HUFFMAN_H
#define HUFFMAN_H
typedef struct tree_{
  int character;
  int freq;
  struct tree_* left;
  struct tree_* right;
  struct tree_* next;
} tree;
//typedef struct tree_ tree;
int leaf(tree* t);
void free_tree(tree* t);
#endif
