#include "huffman.h"
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<ctype.h>

int leaf (tree* t){
  return (t->left==NULL && t->right==NULL)?1:0;
}
void free_tree(tree* t){
  if(leaf(t)){
    free(t);
    return;
  }
  free_tree(t->left);
  free_tree(t->right);
  free(t);
}
