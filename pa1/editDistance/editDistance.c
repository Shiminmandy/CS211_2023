#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t min ( size_t x, size_t y ) {
    return x<y ? x : y;
}

size_t minDis(char* source, char* target){
    if(strlen(source)==0) return strlen(target);
    if(strlen(target)==0) return strlen(source);
    size_t dp[strlen(source)+1][strlen(target)+1];//make 2D array 
    //dp[0][0] is empty char
    for(int i = 0; i<=strlen(source);i++) dp[i][0]=i; //Distance form char in source to empty
    for(int i = 0; i<=strlen(target);i++) dp[0][i]=i; //Distance from char in target to empty

    for(int i = 1; i<=strlen(source);i++){
        for(int j = 1; j<=strlen(target);j++){
            if(source[i-1]==target[j-1]){
                dp[i][j]=dp[i-1][j-1];
            }else{
                // steps need from
                //insert = dp[i][j-1]
                //delete = dp[i-1][j]
                //replace = dp[i-1][j-1]
                dp[i][j]=1+min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1]);
            }
        }
    }
    return dp[strlen(source)][strlen(target)];
}


int main(int argc, char* argv[])
{

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char source[32];
    char target[32];

    fscanf (inputFile, "%s\n%s", source, target);

    printf("%ld\n", minDis ( source, target ));

    return EXIT_SUCCESS;

}
