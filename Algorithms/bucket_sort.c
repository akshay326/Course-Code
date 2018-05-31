#include <stdlib.h>
#include <stdio.h>

/* for linked list in bucket */
struct node {
    int data;
    struct node *next;
};

typedef struct node node_t;

/* each bucket stores elements in a linked list */
struct bucket {
    int size;
    struct node *list;
};
typedef struct bucket bucket_t;

void insertsort(int *seq, int left, int right) {
    int i, j, element;
    for (i = left + 1; i < right; i++) {
        element = seq[i];
        for (j = i-1; i >=0 && seq[j] > element; j--) {
            seq[j+1] = seq[j];
        }
        seq[j+1] = element;
    }
}


// For an uniform distribution, this gives the best
// distribution of numbers throughout the buckets
int hash(int value, int numb_buckets, int max){
    int key = value * numb_buckets / max;
    return key;
}

void bucketsort(int seq[], int numb_buckets, int size, int max) {
    int i, j, left;
    int bucket_numb;

    /* allocate and initialize buckets */
    bucket_t *buckets = malloc(sizeof(bucket_t) * numb_buckets);
    for (i = 0; i < numb_buckets; i++) {
        buckets[i].size = 0;
        buckets[i].list = NULL;
    }

    /* distribute array elements into buckets */
    for (i = 0; i < size; i++) {
        bucket_numb = hash(seq[i], numb_buckets, max);
        /* allocate and initialize node to put into bucket */
        node_t *newnode = malloc(sizeof(node_t));
        newnode->data = seq[i];
        newnode->next = NULL;
        /* store node into linked list of bucket bucket_numb */
        buckets[bucket_numb].size++;
        newnode->next = buckets[bucket_numb].list; /* store at first place */
        buckets[bucket_numb].list = newnode;
        /* instead, we could store in-order, and then we wouldn't have to
           apply sorting to each list */
    }

    j = 0;
    node_t *prev;
    for (i = 0; i < numb_buckets; i++) {
        if (buckets[i].size > 0) {
            left = j;
            node_t *listptr = buckets[i].list;
            while (listptr != NULL) {
                seq[j++] = listptr->data;
                listptr = listptr->next;
            }
            insertsort(seq, left, j); // sort subarray
        }
    }
}