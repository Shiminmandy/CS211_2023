#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    char buff;
    unsigned int binary = 0; //00000000000000000000000000000000  32*0 we could use left shift 
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        buff = fgetc(fp);
        if(buff=='1'){
            binary += (1<<i);
        }
    } // now binary is int of input

    // float number = *(float *)&binary; // you are not allowed to do this.

    /* ... */
    unsigned int sign = binary>>31;
    // E
    /* ... */
    unsigned int binary_nosign = binary<<1; // move sign bit
    unsigned int e = (binary_nosign>>24)-127;

    // M
    /* ... */
    binary_nosign = binary<<9; 
    double m = 1.0;
    double fra = 0.0;
    for (size_t i = 31; 9<=i; i--)
    {
        if (((binary_nosign>>i)& (0b1))==1)
        {
            fra = pow(2.0,32-i);
            m = m+ 1/fra;
        }
        
    }
    // printf("m: %lf\n",m);
    // printf("e: %d\n",e);
    // printf("sign: %d\n",sign);
    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( m, e );
    //printf("number: %lf\n",number);
    number = sign ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
