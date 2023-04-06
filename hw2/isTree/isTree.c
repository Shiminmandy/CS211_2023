#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to determine whether an undirected graph is a tree

// A recursive function that returns true if no cycles found
bool isTreeDFS (
    size_t graphNodeCount,
    AdjacencyListNode* adjacencyList,
    bool* visited,
    graphNode_t parent,
    graphNode_t current
) {
    //printf("current=%ld",current);
    //printf("Your boolean variable is: %s", visited[current] ? "true\n" : "false\n");
    // First see if current node has already been visited, indicating a cycle found
    /* ... */
    if (visited[current]==true)
    {
        //printf("should stop\n");
        return (false);
        //return EXIT_SUCCESS;
    }
    
    // Current node was not already visited, so now mark it as visited
    /* ... */
    if (visited[current]==false)
    {
        visited[current]=true;
    }
    
    
    // Now iterate through each of the neighboring graph nodes
    AdjacencyListNode* neighbor = adjacencyList[current].next;
    while (neighbor) {
        if (neighbor->graphNode!=parent) {
            // If the neighbor nodes is not the parent node (the node from which we arrived at current), call DFS
            /* ... */
            bool ans = isTreeDFS(graphNodeCount,adjacencyList,visited,current,neighbor->graphNode);
            if (ans==false) return false;
            
        }
        neighbor = neighbor->next;
    }
    // All DFS searches from current node found no cycles, so graph is a tree from this node
    return true;
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    FILE* fp = fopen(argv[1],"r");
    if (!fp)
    {
        perror("failed");
        return EXIT_FAILURE;
    }
    fclose(fp);
    /* ... */
    size_t graphNodeCount = adjMatrixToList(argv[1],&adjacencyList);
    // Array of boolean variables indicating whether graph node has been visited
    bool* visited = calloc ( graphNodeCount, sizeof(bool) );
    /* ... */

    /* ... */
    bool isTree = isTreeDFS(graphNodeCount,adjacencyList,visited,-1,0);
    for (graphNode_t i = 0; i < graphNodeCount; i++)
    {
        if (visited[i]==false)
        {
            isTree = false;
            break;
        }
        
    }
    freeAdjList(graphNodeCount,adjacencyList);
    free(visited);
    printf(isTree ? "yes" : "no");

    return EXIT_SUCCESS;
}
