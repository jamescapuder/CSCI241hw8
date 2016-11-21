#include "huffman.h"
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<ctype.h>

#define ASCII_LEN 255

tree* insert_tree(tree* toins, tree* head);

tree* link_list(int* freqs){
	tree* head = malloc(sizeof(tree));
	head->character = -1;
	head->freq = 1;
	head->left=NULL;
	head->right=NULL;
	head->next=NULL;
	for (int i=0;i<ASCII_LEN;i++){
		if (freqs[i]>0){
			tree* temp = malloc(sizeof(tree));
			temp->character = i;
			temp->left=NULL;
			temp->right = NULL;
			temp->next=NULL;
			insert_tree(temp, head);
		}
	}
	return head;
}

tree* insert_tree(tree* toins, tree* head){
	tree* temp = head;
	if (toins->freq > temp->freq){
		while (temp->next!=NULL && toins->freq > temp->next->freq){
			temp = temp->next;
		}
		toins->next = temp->next;
		temp->next = toins;
	}else{
		toins->next = head;
		head=toins;
	}

	return head;
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
	char paths[ASCII_LEN];
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
