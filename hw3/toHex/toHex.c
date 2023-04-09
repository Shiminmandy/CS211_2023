#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    fscanf(fp, "%d", &input);

    // print bits; you will see this kind of for loop often in this assignment
    // printf("%d\n",input);
    // for ( int bit=sizeof(signed int)*8-1; 0<=bit; bit-- ) {
    //     size_t bit_val = ((1<<1)-1) & input>>bit*1; // shift and mask
    //     char character = bit_val ? '1' : '0';
    //     printf("%c",character);
    // }
    for(int hex=3; 0<=hex; hex--){
        size_t hex_val = (0b1111) & input>>4*hex;
        if(hex_val<10){
            printf("%ld",hex_val);
        }else if(hex_val==10){
            printf("%c",'A');
        }else if(hex_val==11){
            printf("%c",'B');
        }else if(hex_val==12){
            printf("%c",'C');
        }else if(hex_val==13){
            printf("%c",'D');
        }else if(hex_val==14){
            printf("%c",'E');
        }else if(hex_val==15){
            printf("%c",'F');
        }
    }
    printf("\n");

    return EXIT_SUCCESS;

}
