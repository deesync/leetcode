#include <stdio.h>
#include <stdlib.h>

/* 
 * kewl readable version with callbacks, 
 * but could be optimized for better performance 
 */

struct node {
	int key;
	unsigned short idx;
	struct node *next;
};

struct list {
	struct node *head;
	struct node *tail;

	void (*add)(struct list *, int, int);
	int (*find)(struct list *, int);
	void (*free)(struct list *);
};


void ls_add_tail(struct list *list, int key, int idx)
{
	list->tail->next = (struct node *) malloc(sizeof(struct node));
	list->tail = list->tail->next;
	
	list->tail->key = key;
	list->tail->idx = idx;
	list->tail->next = NULL;
}

void ls_add_head(struct list *list, int key, int idx)
{
	list->head = (struct node *) malloc(sizeof(struct node));

	list->head->key = key;
	list->head->idx = idx;
	list->head->next = NULL;

	list->tail = list->head;
	list->add = ls_add_tail;
}

int ls_find(struct list *list, int key)
{
	struct node *node = list->head;

	while (node) {
		if (node->key == key) return node->idx;
		node = node->next;
	}

	return -1; // not found
}

void ls_free(struct list *list)
{
	struct node *p, *q;

	for (p = list->head; p != NULL; p = q) {
		q = p->next;
		free(p);
	}
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
	int *r;

	/* Init */
	struct list list = {
		.head = NULL,
		.add = ls_add_head,
		.find = ls_find,
		.free = ls_free,
	}; 

	/* Processing nums array with speedhack for leetcode */
	for (int i = 0, d = numsSize-1, s = 1; d >= 0; i += s*d--, s = -s) {
		int c = list.find(&list, nums[i]);
		 
		if (c < 0) {
			list.add(&list, target - nums[i], i);
			continue;
		}
	
		*returnSize = 2;
		r = (int *) malloc((*returnSize) * sizeof(int));

		r[0] = c;
		r[1] = i;

		list.free(&list);
		return r;
	}

	list.free(&list);

	*returnSize = 0;
	return NULL;
}


// ----------------------------- cut here --------------------------------------


// Test area
int main(void)
{
	int test_arr[] = {1, 2, 4, 6, 9, 1, 9, 8, -2, -3, -20, 34, 0, 12, 5, 8};
	int len = sizeof(test_arr)/sizeof(test_arr[0]);
	
	int sum, r_len; 

	while(1) {
		putchar('\n');
		for (int i = 0; i < len; ++i) printf("%5d", i); 
		putchar('\n');
		for (int i = 0; i < len; ++i) printf("%5d", test_arr[i]);
		putchar('\n');

		printf("Enter target: ");
		scanf("%d", &sum);

		int *r_arr = twoSum(test_arr, len, sum, &r_len);
		
		if (r_len == 2)
			printf("\n\nLen: %d\nTwo Sum (indexes): %d %d\n", r_len, r_arr[0], r_arr[1]);
	}
	
	return 0;
}
