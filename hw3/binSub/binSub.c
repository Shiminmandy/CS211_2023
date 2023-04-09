#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
// https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[CHAR_BIT]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=CHAR_BIT-1; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        buff = fgetc(fp);
        if(buff=='0'){
            minuend[i] = false;
        }else if(buff=='1'){
            minuend[i] = true;
        }
        //printf("%i",minuend[i]);
    }

    // notice that you are reading two different lines; caution with reading
    /* ... */
    buff = fgetc(fp);
    //printf("\n");
    // second, read the subtrahend (number to subtract)
    bool subtrahend[CHAR_BIT]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=CHAR_BIT-1; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        buff = fgetc(fp);
        if(buff=='0'){
            subtrahend[i] = false;
        }else if(buff=='1'){
            subtrahend[i] = true;
        }
        //printf("%i",subtrahend[i]);
    }
    //printf("\n");
    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    // flip all bits
    /* ... */
    for(int i = CHAR_BIT-1; 0<=i; i--){
        if(subtrahend[i] == true){
            subtrahend[i] =false;
        }else if(subtrahend[i] == false){
            subtrahend[i] = true;
        }
        //printf("%i",subtrahend[i]);
    }
    //printf("\n");
    // add one
    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i=0; i<CHAR_BIT; i++) { // iterate from LSB to MSB
        /* ... */
        if (subtrahend[i]==true&&carry==true)
        {
            subtrahend[i]=false;
        }else if(subtrahend[i]==false&&carry==true){
            subtrahend[i]=true;
            carry=false;
        }
        //printf("%i",subtrahend[i]);
    }
    //printf("\n");
    // Add the minuend and the negated subtrahend
    bool difference[CHAR_BIT];
    /* ... */
    carry = false;
    for (int i = 0; i < CHAR_BIT; i++)
    {
        if (subtrahend[i]==true&&minuend[i]==true&&carry==false)
        {
            difference[i]=false;
            carry=true;
        }else if(subtrahend[i]==true&&minuend[i]==true&&carry==true){
            difference[i]=true;
        }else if(subtrahend[i]==false&&minuend[i]==true&&carry==true){
            difference[i]=false;
        }else if(subtrahend[i]==true&&minuend[i]==false&&carry==true){
            difference[i]=false;
        }else if(subtrahend[i]==false&&minuend[i]==false&&carry==true){
            difference[i]=true;
            carry=false;
        }else if(subtrahend[i]==true&&minuend[i]==false&&carry==false){
            difference[i]=true;
        }else if(subtrahend[i]==false&&minuend[i]==true&&carry==false){
            difference[i]=true;
        }else{
            difference[i]=false;
        }
        
    }
    
    // print the difference bit string
    for (int i=CHAR_BIT-1; 0<=i; i--)
        printf("%d",difference[i]);

    return EXIT_SUCCESS;

}
