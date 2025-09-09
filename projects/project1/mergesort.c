
#include <stdlib.h>
#include <stdio.h>

struct node* mergesort(struct node* head, int size);
struct node* merge(struct node * head1, struct node * head2);

struct node{
	int data;
	struct node * next;
};

int main(){
	printf("Hello, World!\n");
	return 0;
}
