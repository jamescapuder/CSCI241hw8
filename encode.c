#include "huffman.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>


tree* link_list(int* freqs){
	tree* head = malloc(sizeof(tree));
	head->character = -1;
	head->freq = 1;
	head->left=NULL;
	head->right=NULL;
	head->next=NULL;
	for (int i=0;i<ASCII_LEN;i++){

	}
}


void get_freqs(int* freqs, FILE* input){
	int c;
	while (EOF != (c=fgetc(input))){
		*(freqs+c)+=1;
	}
}

int main(int argc, char* argv[]){
	int freqs[ASCII_LEN];
	char* freq_keys[ASCII_LEN];
	char paths[ASCII_LEN]="";
	FILE *input;
	FILE *output;

	if (argc>3 || argc<2){
		printf("invalid input.\n usage: encode <toencode> [outfile]\n");
		exit(EXIT_FAILURE);
	}
	if (argc==3){
		output = fopen(argv[2],"w");
	} else{
		output = stdout;
	}
	for (int i=0; i<ASCII_LEN;i++){
		freqs[i]=0;
		freq_keys[i]=NULL;
	}

}
