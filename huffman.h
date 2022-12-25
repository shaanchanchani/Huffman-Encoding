#include <stdbool.h>

#ifndef HW14_H
#define HW14_H		 

#define ASCII_SIZE 256


typedef struct TreeNode {
   int label;
   long count;
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
   TreeNode *ptr;
   struct ListNode *next;
} ListNode;

typedef struct LLnode {
   struct ListNode *head;
} LLnode;


/* construct a new tree, with the new label, and left and right branches */
/* get the count from left and right for the new count                   */
TreeNode *buildTreeNode(int label, TreeNode *left, TreeNode *right);

/* destroy a tree, deallocating all memory associated with the tree      */

void freeHuffmanTree(TreeNode *ptr);

/* given a huffman coding tree, print the huffman code for each ASCII    */
/* symbol                                                                */
void huffmanPrint(const TreeNode *ptr, FILE * fp);

/* is a given TreeNode a leaf node                                       */
int isLeafNode(const TreeNode *node);

/* return the count of a TreeNode                                        */
long treeNodeCount(TreeNode *node);

/* compare tree nodes based on the count				 */
int treeNodeCompare(TreeNode *tp1, TreeNode *tp2);

/*build huffman tree for a given ListNode				 */
TreeNode *buildHuffmanTree(ListNode *list);

ListNode *addListNode(ListNode **list, TreeNode *new_object, 
                  int (*cmpFunction)(TreeNode *, TreeNode *));

//ListNode *removeListNode(ListNode **list);
ListNode *removeListNode(ListNode **list);

/* destroy an entire linked list, freeing all memory used.                */
void freeList(ListNode *list);

/* print an entire linked list                                           */
void printList(const ListNode *list, FILE * fp);

TreeNode* newNode();

void helper(const TreeNode *node, int index, char *huffmanCode, FILE * fp);

void print2DUtil(struct TreeNode* root, int space);

void headerPrint(TreeNode*HuffmanTree,FILE * fp);

void printHeaderHelper(FILE *file, TreeNode*tn, int*count, int* byte);
#endif
