#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "huffman.h"


#ifdef TEST

TreeNode *buildTreeNode(int label, TreeNode *left, TreeNode *right)
{
    TreeNode* node = malloc(sizeof(TreeNode));

    if (!node){return NULL;}

    node->label = label;
    node->left = left;
    node->right = right;
    node->count = treeNodeCount(left)+treeNodeCount(right);

    return(node);
}

void freeHuffmanTree(TreeNode *tn)
{
    if (!tn){return;}
    freeHuffmanTree(tn -> left);
    freeHuffmanTree(tn -> right);
    free(tn);
}

int isLeafNode(const TreeNode *node)
{
    if(!node)
    {
        return(0);
    }    
    if ((!(node -> left)) && (!(node -> right)))
    {
        return(1);
    }
    return(0);
}

long treeNodeCount(TreeNode *node)
{
    if (!node)
    {
        return(0);
    }
    return(node->count);
}


ListNode *removeListNode(ListNode **list)
{
    ListNode *deleted;

    deleted = *list;
    if(deleted !=NULL)
    {
        *list = deleted->next;
        deleted->next = NULL;
    }
    return(deleted);
}


TreeNode *buildHuffmanTree(ListNode *list)
{
    ListNode *node1;
    ListNode *node2;
    ListNode *next_node;
    TreeNode *new_TreeNode;

    int label = ASCII_SIZE;
    node1 = removeListNode(&list);

    while(node1)
    {
        node2 = removeListNode(&list);
        if(node2 == NULL)
        {
            TreeNode *tn = (TreeNode*) node1->ptr;
            free(node1);
            return tn;
        }
        new_TreeNode = buildTreeNode(label,(TreeNode*)node1->ptr,(TreeNode*)node2->ptr);
        free(node2); 
        free(node1);
        if (!new_TreeNode)
        {
            freeList(list);
            return NULL;
        }

        next_node = addListNode(&list,new_TreeNode,treeNodeCompare);
        if(!next_node)
        {
            freeHuffmanTree(new_TreeNode);
            freeList(list);
            return NULL;
        }
        node1 = removeListNode(&list);
        label += 1;
    }
    return NULL;
}

void huffmanPrint(const TreeNode *tn, FILE * fp)
{
    char huffmanCode[ASCII_SIZE];

    if (!tn){return;}

    helper(tn,0,huffmanCode,fp);
}

/* helper function for a recursive call to print the huffman code

function arguments can be : const TreeNode *node, int index, char *huffmanCode, FILE * fp
call isleafNode function to check if the leafnode is ==1
write the helper function by recursively calling for left and right sub tree like hw13 
left when huffmanCode[index]='0' and '1' when right. 
*/
void helper(const TreeNode *node, int index, char *huffmanCode, FILE * fp)
{
    if(node == NULL){return;}    
    int i;

    if (isLeafNode(node))
    {
        fprintf(fp,"%c:",node->label);
        for(i = 0;i<index;i++)
        {
            fprintf(fp,"%c", huffmanCode[i]);
        }
        fprintf(fp,"\n");
        return;
    }
    huffmanCode[index] = '0';
    helper(node->left,(index+1),huffmanCode,fp);

    huffmanCode[index] = '1';
    helper(node->right,(index+1),huffmanCode,fp);

    // if(helper(node->left,(index+1), huffmanCode, fp))
    // {
    //     huffmanCode[index] = '0';
    //     return true;
    // }

    // if(helper(node->right, (index+1), huffmanCode, fp))
    // {
    //     huffmanCode[index] = '1';
    //     return true;
    // }
}
//compare tree nodes based on the count (compare path hw11)
int treeNodeCompare(TreeNode *tp1, TreeNode *tp2)
{
    long diff;

    diff = tp1->count - tp2->count;
    
    if(diff > 0)
    {
        return(1);
    }
    else{
        if(diff == 0)
        {
            return((tp1->label) - (tp2->label));
        }
        else {
            return(-1);
        }
    }
}

ListNode *addListNode(ListNode **list, TreeNode *new_object,int (*cmpFunction)(TreeNode *, TreeNode *))
{
    if(!new_object){return NULL;}

    ListNode *node;
    ListNode *prev;
    ListNode *curr;
    ListNode temp;

    node = malloc(sizeof(ListNode));
    temp.next = *list;
    prev = &temp;
    curr = *list; 

    while(curr)
    {
        if(cmpFunction(curr->ptr,new_object) > 0)
        {
            break;
        }
        else{
            prev = curr;
            curr = curr -> next;
        }
    }

    node->ptr = new_object;
    node->next = curr;
    prev->next = node;

    *list = temp.next;

    return(node);
}

void freeList(ListNode *list)
{
    if (list == NULL)
    {
        return;
    }
    else
    {
        ListNode *p;
        p = list -> next;
        freeHuffmanTree(list->ptr);
        free(list);
        list = p;
    }
    freeList(list);
}

void printList(const ListNode *list, FILE * fp)
{
    while(list)
    {
        fprintf(fp,"%c:",(list->ptr->label));
        fprintf(fp,"%ld\n", (list->ptr->count));
        list = list -> next;
    }
}
void headerPrint(TreeNode*HuffmanTree,FILE * fp)
{
    int count = 0; 
    int byte = 0;

    printHeaderHelper(fp,HuffmanTree,&count,&byte);

    if(!count)
    {
        fputc(0,fp);
    }
    else{
        fputc(byte,fp);
    }
}

void printHeaderHelper(FILE *file, TreeNode*tn, int*count, int*byte)
{
    if (!tn){return;}

    unsigned int byteSize = 8;

    if(isLeafNode(tn))
    {
        *byte = *byte | (1 << (byteSize - 1 - *count));
        *count += 1;

        if(*count == byteSize)
        {
            fputc(*byte, file);
            *byte = 0;
            *count = 0;
        }
        if(!*count)
        {
            fputc(tn->label,file);
        }
        else{
            *byte = *byte | (tn -> label >> *count);
            fputc(*byte, file);
            *byte = (tn->label & (0xFF >> (byteSize - *count))) << (byteSize - *count);
        }
        return;
    }
    
    *count += 1;
    if(*count == byteSize)
    {
        fputc(*byte, file);
        *byte = 0;
        *count = 0;
    }

    printHeaderHelper(file, tn->left, count, byte);
    printHeaderHelper(file, tn->right, count, byte);
}



#endif
