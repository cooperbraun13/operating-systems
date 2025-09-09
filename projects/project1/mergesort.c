
#include <stdlib.h>
#include <stdio.h>

struct node* mergesort(struct node* head, int size);
struct node* merge(struct node *head1, struct node *head2);

struct node{
	int data;
	struct node *next;
};

// merge two sorted linked lists
struct node* merge(struct node *head1, struct node *head2) {
  // new list head
  struct node *head = NULL;
  // last node in new list
  struct node *tail = NULL;

  while (head1 != NULL && head2 != NULL) {
    struct node *temp;
    if (head1->data <= head2->data) {
      temp = head1;
      head1 = head1->next;
    } else {
      temp = head2;
      head2 = head2->next;
    }

    // first node becomes head
    if (head == NULL) {
      head = temp;
      tail = temp;
    } else {
      // attach after tail
      tail->next = temp;
      tail = temp;
    }
  }

  if (head1 != NULL) tail->next = head1;
  else if (head2 != NULL) tail->next = head2;

  return head;
}

int main(){
	printf("Hello, World!\n");
	return 0;
}
