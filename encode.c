#include "huffman.h"
#include<stdlib.h>
//#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<ctype.h>
#include<errno.h>

#define ASCII_LEN 256

tree* insert_tree(tree* toins, tree* head);

tree* link_list(int* freqs){
	tree* head = safe_malloc(sizeof(tree));
	head->character = 255;
	head->freq = 1;
	head->left=NULL;
	head->right=NULL;
	head->next=NULL;
	for (int i=0;i<ASCII_LEN;i++){
		if (freqs[i]>0){
			tree* temp = safe_malloc(sizeof(tree));
			temp->character = i;
			temp->left=NULL;
			temp->right = NULL;
			temp->next=NULL;
			temp->freq = freqs[i];
			head = insert_tree(temp, head);
			//printf("%c: %d\n", temp->character, temp->freq);
		}
	}
	return head;
}

tree* make_forrest(tree* head){

  tree *l, *r;
  while(head->next != NULL){
    l = head;
    r = head->next;
    tree* temp = safe_malloc(sizeof(tree));
    temp->left = l;
    temp->right = r;
    temp->next=NULL;
    temp->character = 0;
    temp->freq = l->freq+r->freq;
    head = head->next->next;
    if (head==NULL){return temp;}
    else{head = insert_tree(temp, head);}
  }
  return head;

}

void make_code_map(char* codes[ASCII_LEN],tree*head, char code_cont[]){
  if (head!=NULL){
    if (head->character != 0){
      codes[head->character]=strdup(code_cont);
      return;
    } else{
      strcat(code_cont, "0");
      make_code_map(codes, head->left, code_cont);
      *(code_cont + strlen(code_cont)-1)='1';
      //strcat(code_cont, "1");
      make_code_map(codes, head->right, code_cont);
      *(code_cont + strlen(code_cont)-1)='\0';
    }
  }
}
void printt(tree* head){
  if (NULL == head->left && NULL == head->right){
    printf("1");
    printf("%d", head->character);
  }else{
    printf("0");
    printt(head->left);
    printt(head->right);
  }
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
	  //printf("%c\n", c);
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
	errno=0;
	input = fopen(argv[1], "r");
	if (errno){exit(EXIT_FAILURE);}
	if (argc==3){
		output = fopen(argv[2],"w");
	} else{
		output = stdout;
	}
	for (int i=0; i<ASCII_LEN;i++){
		freqs[i]=0;
		freq_keys[i]=NULL;
	}
	get_freqs(freqs, input);
	tree* freq_list = link_list(freqs);
	tree* forrest = make_forrest(freq_list);
	//print_tree(freq_list);
	make_code_map(freq_keys, forrest, paths);
	//for (int i=0; i<ASCII_LEN; i++){	
	//printf("%c: %s\n", i, freq_keys[i]);
	//}
	write_tree(forrest, output);
	write_str(freq_keys[255], output);
	rewind(input);
	int ch;
	while (EOF != (ch=fgetc(input))){
	  //printf("%d: ", ch);
	  //printf("%c: ", ch);
	  //printf("%s\n", freq_keys[ch]);
	  
	  //if (freq_keys[ch]!=NULL){
	    write_str(freq_keys[ch], output);
	    //}
	}
	write_str(freq_keys[255],output);
	fclose(input);
	fclose(output);
}
