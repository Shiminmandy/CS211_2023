#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {

  // Open the filename given as the first command line argument for reading
  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }

  char buf[256];

  char* string = fgets(buf, 256, fp);
  int x = atoi(string);
  char* string2 = fgets(buf,256,fp);
  int y = atoi(string2);
  
  int square1 = x*x + y*y;
  int root1 = sqrt(square1);
  
  if(root1*root1 == square1){
  	printf("%d\n", root1);
  	return EXIT_SUCCESS;
  }else{
  	if((x-y)>0){
  		int square2 = x*x - y*y;
  		int root2 = sqrt(square2);
  		if(root2*root2 == square2){
  			printf("%d\n", root2);
  			return EXIT_SUCCESS;
  		}else{
  			printf("%d\n",-1);
  		}
  	}else{
  		int square2 = y*y - x*x;
  		int root2 = sqrt(square2);
  		if(root2*root2 == square2){
  			printf("%d\n", root2);
  			return EXIT_SUCCESS;
  		}else{
  			printf("%d\n",-1);
  		}
  	}
  }


  return EXIT_SUCCESS;
  

}
