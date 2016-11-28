#include "huffman.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int bit_helper(FILE* input);

int traverser(FILE* input, tree* head);

char char_helper(FILE* input);

int bit_help_len = 0;
int current_byte=0;

tree* extract_tree(FILE* input){
  int current_bit = bit_helper(input);
  if (current_bit==EOF){
    printf("error?");
  }
  if (current_bit==1){
    char c = char_helper(input);
    tree* head = safe_malloc(sizeof(tree));
    head->character=c;
    head->next=NULL;
    head->left=NULL;
    head->right=NULL;
    return head;
  } else{
    tree* head = safe_malloc(sizeof(tree));
    head->left = extract_tree(input);
    head->right=extract_tree(input);
    return head;
  }
}

int traverser(FILE* input, tree* head){
  tree* temp = head;
  int temp_bit;
  while (!leaf(temp)){
    temp_bit = bit_helper(input);
    if (temp_bit==0){
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }
  return temp->character;
}
int bit_helper(FILE* input){
  if (bit_help_len-->0){
    int current_bit=0;
    if (current_byte & (1<<(CHAR_BIT-1))){
      current_bit=1;
    }
    current_byte = current_byte<<1;
    return current_bit;
  } else{
    current_byte = fgetc(input);
    if (EOF == current_byte){
      return EOF;
    }
    bit_help_len=CHAR_BIT;
    return bit_helper(input);
  }
}

char char_helper(FILE* input){
  int ch = 0;
  for (int i=0; i<CHAR_BIT;i++){
    int current_b = bit_helper(input);
    current_b = current_b << (CHAR_BIT-i -1);
    ch |= current_b;
  }
  return ch;
}

int main(int argc, char* argv[]){

  if (argc>3 || argc<2){
    printf("invalid input.\n usage: decode <todecode> [outfile]\n");
    exit(EXIT_FAILURE);
  }  
  FILE* input = fopen(argv[1], "r");
  FILE* output = stdout;
  if (argc==3){
    output = fopen(argv[2], "w");
  }
  tree* head = extract_tree(input);
  int to_end = traverser(input, head);
  
  while (1){
    int temp_char = traverser(input, head);
    if (temp_char == to_end){break;}
    fprintf(output, "%c", temp_char);
  }
  fclose(input);
  fclose(output);
}
