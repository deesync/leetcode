#include <stdio.h>
#include <stdlib.h>

typedef struct inthashnode_t {
	int key;
	int idx;
	struct inthashnode_t * next;
}
HNode;

typedef struct inthash_t {
	struct inthashnode_t * head;
	struct inthashnode_t * tail;

	void (*add)(struct inthash_t*, int, int);
	int (*find)(struct inthash_t*, int);
	void (*free)(struct inthash_t*);
}
IHash;


void __ih_add_tail(IHash* hash, int key, int idx)
{
//	if (!hash) return;

	// Just adding key to hash tail without check for existing key
	hash->tail->next = (HNode *) malloc(sizeof(HNode));
	hash->tail = hash->tail->next;
	
	hash->tail->key = key;
	hash->tail->idx = idx;
	hash->tail->next = NULL;
}

void __ih_add_head(IHash* hash, int key, int idx)
{
//	if (!hash) return;

	hash->head = (HNode *) malloc(sizeof(HNode));

	hash->head->key = key;
	hash->head->idx = idx;
	hash->head->next = NULL;

	hash->tail = hash->head;
	hash->add = __ih_add_tail;
}

int __ih_find(IHash* hash, int key)
{
	HNode* node = hash->head;

	while (node) {
		if (node->key == key) return node->idx;
		node = node->next;
	}

	return -1; // if not found
}

void __ih_free(IHash* hash)
{
	HNode *p, *q;

	for (p = hash->head; p != NULL; p = q) {
		q = p->next;
		free(p);
	}
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	int c, i, d, sgn = 1;
	int* r = NULL; // return

	IHash hash;
	// Hash initialization
	hash.head = NULL;
	hash.add = __ih_add_head;
	hash.find = __ih_find;
	hash.free = __ih_free;

	for (i = 0, d = numsSize-1; d >= 0; i += sgn*d--, sgn *= -1) { // speedhack for leetcode :)
		c = hash.find(&hash, nums[i]);
		 
		if (c < 0) {
			hash.add(&hash, target - nums[i], i);
			continue;
		}
	
		*returnSize = 2;
		r = (int *) malloc((*returnSize) * sizeof(int));

		r[0] = c < i ? c : i;
		r[1] = c < i ? i : c;

		return r;
	}

	hash.free(&hash);
	*returnSize = 0;
	return NULL;
}




int main()
{
	int test_arr[] = {1, 2, 4, 6, 9, 1, 9, 8, -2, -3, -20, 34, 0, 12, 5, 8};
	int len = sizeof(test_arr)/sizeof(test_arr[0]);
	
	int sum, r_len, *r_arr; 

	while(1) {
		puts("\n");
		for (int i = 0; i < len; ++i) printf("%5d", i); puts("");
		for (int i = 0; i < len; ++i) printf("%5d", test_arr[i]); puts("");

		printf("Enter target: ");
		scanf("%d", &sum);

		r_arr = twoSum(test_arr, len, sum, &r_len);
		
		if (r_len == 2)
			printf("\n\nLen: %d\nTwo Sum (indexes): %d %d\n", r_len, r_arr[0], r_arr[1]);
	}
	
	return 0;
}
