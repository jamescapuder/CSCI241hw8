#ifndef HUFFMAN_H
#define HUFFMAN_H
typedef struct tree{
  int character;
  int freq;
  tree* left;
  tree* right;
  tree* next;
} tree;
int leaf(tree* t);
void free_tree(tree* t);
#endif
