#include <stdlib.h>
#include <stdio.h>

struct node* list_mergesort(struct node* head, int size);
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

// helper functions

// appends a new node with the given value to the end of the list
void append_node(struct node **head_ref, int value) {
  struct node *new_node = malloc(sizeof(struct node));
  new_node->data = value;
  new_node->next = NULL;
  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  }
  struct node *curr = *head_ref;
  while (curr->next != NULL) curr = curr->next;
  curr->next = new_node;
}

// prints the list from head to tail as [data] -> ... -> NULL
void print_list(struct node *head) {
  while (head != NULL) {
    printf("[%d] -> ", head->data);
    head = head->next;
  }
  printf("NULL\n");
}

int main(){
  // [3] -> [5] -> [9]
	struct node *head1 = NULL;
  append_node(&head1, 3);
  append_node(&head1, 5);
  append_node(&head1, 9);

  // [1] -> [6] -> [7]
  struct node *head2 = NULL;
  append_node(&head2, 1);
  append_node(&head2, 6);
  append_node(&head2, 7);

  printf("List 1: "); print_list(head1);
  printf("List 2: "); print_list(head2);

  struct node *merged = merge(head1, head2);
  printf("Merged: "); print_list(merged);
  
	return 0;
}
