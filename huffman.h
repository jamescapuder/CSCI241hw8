#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
typedef struct tree_{
  int character;
  int freq;
  struct tree_* left;
  struct tree_* right;
  struct tree_* next;
} tree;
//typedef struct tree_ tree;
unsigned int contained;
int indy;
int leaf(tree* t);
void free_tree(tree* t);
void write_tree(tree* head, FILE* outfile);
void write_bit(unsigned int to_write, FILE* outfile);
void write_str(const char* to_w, FILE* outfile);
#endif
