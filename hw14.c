#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

long *countLetters(FILE *fp)
{
   long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
   if (asciiCount == NULL) {
      return NULL;
   }
   int ch;
   for (ch = 0; ch < ASCII_SIZE; ch++) {
      asciiCount[ch] = 0;
   }
   fseek(fp, 0, SEEK_SET);
   while ((ch = fgetc(fp)) != EOF) {
      asciiCount[ch] += 1;
   }
   return asciiCount;
}

// argv[1]: input file name 
// argv[2]: output file 1 name - to store the sorted characters
// argv[3]: output file 2 name - to store the huffman code of each characters
// argv[4]: output file 3 name - to store the header information
int main(int argc, char **argv)
{
   if (argc != 5) {
    printf("Not enough arguments");
    return EXIT_FAILURE;
   }
   FILE * inFile = fopen(argv[1], "r");
   if (inFile == NULL) {
      fprintf(stderr, "can't open the input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   /* read and count the occurrences of characters */
   long *asciiCount = countLetters(inFile);
   fclose(inFile);

   if (asciiCount == NULL) {
      fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
      return EXIT_FAILURE;
   }


   TreeNode* node;
   TreeNode* left;
   TreeNode* right;
   ListNode* list = NULL;
   TreeNode* HuffmanTree;

   int ch;
   for (ch = 0; ch < ASCII_SIZE; ch++) 
   {
      if(asciiCount[ch] != 0)
      {
         left = NULL;
         right = NULL;
         node = buildTreeNode(ch, left, right);
         if (!node)
         {
            freeList(list);
         }
         node -> count = asciiCount[ch];
         ListNode * updatedList = addListNode(&list,node,treeNodeCompare);
         if(!updatedList)
         {
            freeList(updatedList);
            freeHuffmanTree(node);
         }
      }
   }

   FILE *fp = fopen(argv[2], "w");
   printList(list,fp);
   fclose(fp);
   
   HuffmanTree = buildHuffmanTree(list);
   
   fp = fopen(argv[3], "w");
   huffmanPrint(HuffmanTree,fp);
   fclose(fp);

   fp = fopen(argv[4], "w");
   headerPrint(HuffmanTree,fp);
   fclose(fp);

   freeHuffmanTree(HuffmanTree);
   free(asciiCount);

   return EXIT_SUCCESS;
}
