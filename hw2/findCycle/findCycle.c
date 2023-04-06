#include "../graphutils.h"


bool dfs(size_t graphNodeCount,AdjacencyListNode* adjlist,graphNode_t current,bool* visited,bool* onPath,size_t* ans,size_t index){//queue has current node
    visited[current]=true;
    onPath[current]=true;
    //printf("path %ld",current);
    //printf("ans:%ld ",ans[current]);
    ans[index]=current;
    AdjacencyListNode* neighbor = adjlist[current].next;
    while (neighbor)
    {
        if (!visited[neighbor->graphNode])
        {
            //enqueue(&queue,neighbor);
            //push(&root,neighbor->graphNode);
            if (dfs(graphNodeCount,adjlist,neighbor->graphNode,visited,onPath,ans,index+1))
            {
                return true;
            }
            
        }else if(onPath[neighbor->graphNode]) {
                ans[index+1]=neighbor->graphNode;
                return true;
            }
        neighbor = neighbor->next;
        
    }
    onPath[current]=false;
    return false;
    
}
int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList;
    /* ... */
    size_t graphNodeCount = adjMatrixToList(argv[1],&adjacencyList);
    //printf("graphNode:%ld\n", graphNodeCount);
    bool* visited = calloc ( graphNodeCount, sizeof(bool) );
    bool* onPath = calloc ( graphNodeCount, sizeof(bool) );
    size_t* ans = calloc ( graphNodeCount+1, sizeof(size_t) );
    for (size_t i=0; i<graphNodeCount+1; i++) {
        ans[i] = (graphNodeCount+1); 
    }
    //printf("ans:%ld\n",ans[0]);
    //struct element* root = NULL;

    bool isCyclic = false;
    for (unsigned source=0; source<graphNodeCount; source++) {
        /* ... */
        // struct element* root = NULL;
        if (!visited[source])
        {
            //graphNode_t current = adjacencyList[source].graphNode;
            //graphNode_t* current=&(adjacencyList[source].graphNode);
            //enqueue(&queue,current);
            //struct element* root = NULL;
            //push(&root,source);
            if (dfs(graphNodeCount,adjacencyList,source,visited,onPath,ans,0))
            {
                isCyclic = true;
                break;
            }
            
        }
        
    }
    if (!isCyclic) { printf("DAG\n"); }
    if (isCyclic)
        {
            size_t start=0;
            size_t end = 0;
            //printf("isCyclic\n");
            // for (size_t i = 0; i < graphNodeCount+1; i++)
            // {
            //     printf("ans:%ld ",ans[i]);
            // }
            // printf("\n");
            
            for (size_t a = 0; a < graphNodeCount+1; a++)
            {
                for (size_t b = a+1; b < graphNodeCount+1; b++)
                {
                    /* code */
                    if (ans[a]==ans[b]&& (ans[a]!=graphNodeCount+1)&&(ans[b]!=graphNodeCount+1))
                    {
                        start=a;
                        end=b;
                        break;
                    }
                    
                }
                
            }
            
            // printf("start:%ld ", start);
            // printf("end:%ld",end);
                
            
            for (size_t k = start+1; k <=end; k++)
            {
                printf("%ld ",ans[k]);
            }
            printf("\n");
            
            
        }
    
    

    freeAdjList ( graphNodeCount, adjacencyList );
    free(visited);
    free(onPath);
    free(ans);
    return EXIT_SUCCESS;
}

