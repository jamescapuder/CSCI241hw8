#include "huffman.h"
#include<stdlib.h>
//#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<ctype.h>
#include<errno.h>

void* safe_malloc(size_t t){

  errno = 0;
  void* pointer = malloc(t);
  if (errno != 0){perror("could not malloc");exit(EXIT_FAILURE);}
  else{return pointer;}

}

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

void write_bit(unsigned int to_write, FILE* outfile){  
  unsigned int m = to_write ? (1<<(CHAR_BIT-1)):0;
  m = m >> indy++;
  contained |= m;
  if (indy >= CHAR_BIT){
    fprintf(outfile, "%c", (char) contained);
    indy=0;
    contained=0;
  }
}
void write_tree(tree* head, FILE* outfile){

  if (leaf(head)==1){
    write_bit(1, outfile);
    unsigned int m = (1<<(CHAR_BIT -1));
    for (int i=0; i<CHAR_BIT; i++){
      if (head->character & m){
	write_bit(1, outfile);
      }else{
	write_bit(0, outfile);
      }
      m = m >> 1;
    }
  }else {
    write_bit(0, outfile);
    write_tree(head->left, outfile);
    write_tree(head->right, outfile);
  }

}
void write_str(const char* to_w, FILE* outfile){

  for (unsigned long i=0;i<strlen(to_w);i++){
    if ('0'==to_w[i]){write_bit(0,outfile);}
    else if ('1'==to_w[i]){write_bit(1,outfile);}
  }

}
void flush_buffer(FILE* outfile){
  while (indy){
    write_bit(0, outfile);
  }
}
