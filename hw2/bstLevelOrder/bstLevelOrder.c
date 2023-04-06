#include <stdlib.h>
#include <stdio.h>
#include "../bstReverseOrder/bst.h"
#include "../queue/queue.h"

// A program to perform a LEVEL ORDER (BREADTH-FIRST) TRAVERSAL of a binary search tree

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE BINARY SEARCH TREE
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    BSTNode* root = NULL;
    int key;
    while ( fscanf(fp, "%d", &key)!=EOF ) {
        root = insert (root, key);
    }
    fclose(fp);

    // USE A QUEUE TO PERFORM LEVEL ORDER TRAVERSAL
    Queue queue = { .front=NULL, .back=NULL };

    /* ... */
    enqueue(&queue,root); //add root to queue
    while(queue.front!=NULL){ // while queue is not empty
        BSTNode* pointer = dequeue(&queue); // get the first BSTNode of queue

        printf("%d ",pointer->key); // print the key of the pointer
        if (pointer->l_child != NULL)
        {
            enqueue(&queue,pointer->l_child);
        }
        if (pointer->r_child !=NULL)
        {
            enqueue(&queue,pointer->r_child);
        }
        //free(pointer);       

    }

    delete_bst(root);
    return EXIT_SUCCESS;
}
