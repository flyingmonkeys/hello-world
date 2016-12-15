//
//  main.c
//  
//
//  Created by California on 7/19/14.
//
//
// run with >./main
//


#include <stdio.h>

typedef int bool;

void func1(int a)
{
    printf("Func1 invoked with value %d\n",a);
}

void func2(int a)
{
    printf("Func2 invoked with value %d\n",a);
}

void (*funcArray[])(int) =
{
    func1,
    func2
};

struct node
{
    int data; /* node data*/
    struct node *pNextNode;
};

struct node *pHead; /* Head of the linked list, make this global for simplicity */

void (*pFunction)(struct node *, struct node *); // pointer to a function returning a void

/* Input: Pointer to where new nodeData is to be inserted, and a pointer to the new nodeData*/
void insertElement(struct node *pInsertionPoint, struct node *pNewData)

{
    struct node *pTemp;
    
    pTemp = (pInsertionPoint)->pNextNode; /*Store where the next node was located */
    pInsertionPoint->pNextNode = pNewData; /* Replace the next node address with the new inserted node */
    (pNewData->pNextNode) = pTemp; /* Store the old next node into the newly inserted node */
}


/* Input: Pointer to where old nodeData is to be removed */
bool deleteElement(struct node *pOldData)

{
    bool success = 0; /* return back success or failure if the node to be removed can't be found (could happen) */
    struct node *pTemp = pHead; /* Start at the head */
    
    /* Find the node that precedes the node to be removed, so we can change the linked list pointer to the next node */
    while( (pTemp != NULL) && (pTemp->pNextNode != pOldData) )
    {
        pTemp = pTemp->pNextNode;
    }
    
    /* Once we're here, we either hit the end of the list (found the null pointer) or we found the node to be removed. pTemp now points to the node that precedes the node to be removed */
    if (pTemp != NULL)
    {
        pTemp->pNextNode = (pTemp->pNextNode)->pNextNode;
        //     free(pTemp->pNextNode); /* Do this if nodes are dynamically allocated */
        success = 1;
    }
    
    return (success);
}

int bitReverse(int x)

{
    int i=0x0001; // will act as a mask and as a counter
    int y=0; // bit-reversed output
    
    for (i = 0x0001; i != 0x10000; i <<= 1)
    {
        y <<= 1; /* Make room for next bit */
        if (x & i) y |= 1; /* OR in a bit if the masked value is non-zero */
    }
    
    return (y);
}

void test1(int *b)
{
	printf("in test1\n%d\n",*b);
}

void test2(int **b)
{
	printf("in test2\n");
	printf("Address of a=%d\n",*b);
	printf("value of a=%d\n",**b);
}

int main(void)
{
    void (*funcPtr)(int);
	int x;
	struct node *pHeadNode,*pNewNode,headNode,node1,node2,newNode;
	int array[0x2000];
	int a;
	int *p_a;
    char st[] = "richard";
    char *st2 = "simeon";
    
    /* Create an array of strings this way */
    char *st3[] = {
// char **st3 = { <-- this does not work!
        "word1",
        "word2"
    };
    
    /* String manipulation */
    /* %s expects a pointer to a string */
    /* %c expects a character */
    printf("%s\n",st);    // print whole word to the \0 null character terminator
    printf("%c\n",st[2]); // print 3rd character
    printf("%c\n",*(st+3)); // another way to print 4th character
    printf("%s\n",st2+2);  // print whole word starting at 3rd character to null terminator
    printf("%s\n",&st2[3]); // another way to start at 4th character
    
    printf("%s\n",st3[1]);
    
    printf("\n");
    
	int *pAddr = &array[0];
    
    /* The following lines are used to read/write a value to an absolute address (e.g. memory mapped register) */
    unsigned int *pBaseAddr = (unsigned int *)(0x0000);
    
    //*(pBaseAddr + 0x1234) = 0xABCD;
    //	(*((unsigned int *)(0x1234))) = 0xABCD; // an example to set the value in absolute address 0x1234 for 0xABCD
    
	a=77;
	p_a = &a;
    
	test1(p_a); // pass a pointer
	test2(&p_a); // pass a double pointer
    
	printf("a=%d\n",*(&a));
    
    //*(pAddr + 0x1234) = 0xABCD;
    
	pAddr[5] = 0xabcd;
    
	pAddr = array; // set pAddr to the beginning of array
    
	printf("Hello World!\n");
    
	x = bitReverse(0x1234);
    printf("bitReverse of 0x1234 is 0x%x\n",x);
    
    /* Configure headNode -> node1 -> node2 */
	headNode.pNextNode = &node1;
	node1.pNextNode = &node2;
	node2.pNextNode = NULL;
    
    /* pHead points to head node */
	pHead = &headNode;
	pHeadNode = &headNode;
    
    /* Create a new node and insert this into the linked list after node1 */
	pNewNode = &newNode;

#if 0
    insertElement(&node1,&newNode);
#else
	pFunction = &insertElement;
//	(*pFunction)(&node1,&newNode); // this is one way to call a function using a function pointer
     pFunction(&node1,&newNode); // this is another way to call a function using a function pointer
#endif
    
    /* Delete node1 */
	deleteElement(&node1);
    
    
    printf("hello world\n");
    
    func1(88);

    funcArray[0](23);
    
    funcArray[0] = func1;
    
    funcArray[0](11);
    
    funcPtr = funcArray[1];
    
    funcPtr(99);    // call function pointed to by funcPtr
    (*funcPtr)(86); // another way to call function pointed to by funcPtr
    (*(funcArray+1)) = func1;
    
    funcArray[1] = func1;
    funcArray[1](67);
    
    funcPtr(66); // this is one way to call a function using a function pointer
 //   (*(funcPtr+1))(76);
    (*funcPtr)(76); // this is another way to call a function using a function pointer
    
    return 0;
}
