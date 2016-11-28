#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tools.h"

tree* extract_tree(FILE* input){
  
}

int bit_helper(FILE* input){
  
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

}
