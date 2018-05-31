#include <bits/stdc++.h>
#include "header.hpp"

using namespace std;

// A Huffman tree node
struct MinHeapNode {

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child
    struct MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) {
        left = NULL;
        right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(struct MinHeapNode *l, struct MinHeapNode *r) {
        return (l->freq > r->freq);
    }
};

void printCodes(struct MinHeapNode *root, const string &str) {

    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode *, std::vector<MinHeapNode *>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {

        // Extract the two minimum
        // freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // $' is a special value for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes
    printCodes(minHeap.top(), "");
}
/*
 * Sample Code
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 52, 91, 2, 13, 16, 45 };

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);
 */
