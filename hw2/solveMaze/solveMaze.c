#include "../graphutils.h" // header for functions to load and free adjacencyList
#include "../queue/queue.h" // header for queue

// A program to solve a maze that may contain cycles using BFS

int main ( int argc, char* argv[] ) {

    // First, read the query file to get the source and target nodes in the maze
    /* ... */
    graphNode_t source;
    graphNode_t target;
    FILE* fp = fopen(argv[2],"r");
    if (!fp)
    {
        printf("error");
        return EXIT_FAILURE;
    }
    fscanf(fp,"%ld %ld", &source, &target);
    fclose(fp);
    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    /* ... */
    size_t graphNodeCount = adjMatrixToList(argv[1],&adjacencyList);
    // USE A QUEUE TO PERFORM BFS
    Queue queue = { .front=NULL, .back=NULL };

    //An array that keeps track of who is the parent node of each graph node we visit
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited
    }

    /* ... */
    bool* visited = calloc ( graphNodeCount, sizeof(bool) );
    graphNode_t current = source;
    parents[current]=current;
    while ( current != target ) {

        // so long as we haven't found the target node yet, iterate through the adjacency list
        // add each neighbor that has not been visited yet (has no parents) to the queue of nodes to visit
        /* ... */
        AdjacencyListNode* neighbor = adjacencyList[current].next;

        while (neighbor)
        {
            if (visited[neighbor->graphNode]==false)
            {
                enqueue(&queue,neighbor);
                parents[neighbor->graphNode]=current;
                visited[neighbor->graphNode]=true;
            }
            neighbor = neighbor->next;
            
        }
        
        
        // Visit the next node at the front of the queue of nodes to visit
        /* ... */
        AdjacencyListNode* outNode=dequeue(&queue);
        current = outNode->graphNode;
    }

    // Now that we've found the target graph node, use the parent array to print maze solution
    // Print the sequence of edges that takes us from the source to the target node
    /* ... */
    graphNode_t cur = target;

    while (cur!=source)
    {
        printf("%ld %ld\n", cur,parents[cur]);
        cur = parents[cur];
        
    }
    

    
    

    // free any queued graph nodes that we never visited because we already solved the maze
    while ( queue.front ) {
        /* ... */
        dequeue(&queue);
        //printf( "%d\n", *data );
        //free(data);
    }
    
    freeAdjList ( graphNodeCount, adjacencyList );
    free (parents);
    free(visited);
    //fclose(fp);
    return EXIT_SUCCESS;
}
