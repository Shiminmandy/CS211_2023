#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
// https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>
// https://www.cplusplus.com/reference/cfloat/
#include <float.h>

#define FLOAT_SZ sizeof(float)*CHAR_BIT
#define EXP_SZ (FLOAT_SZ-FLT_MANT_DIG)
#define FRAC_SZ (FLT_MANT_DIG-1)

int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of multiplier
    /* ... */
    char buff;
    unsigned int multiplier = 0; 
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        buff = fgetc(fp);
        if(buff=='1'){
            multiplier += (1<<i);
        }
    } // now binary is int of input
    //printf("multiplier: %d\n",multiplier);
    // notice that you are reading two different lines; caution with reading
    /* ... */
    buff = fgetc(fp);
    // first, read the binary number representation of multiplcand
    /* ... */
    unsigned int multiplicand = 0; 
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        buff = fgetc(fp);
        if(buff=='1'){
            multiplicand += (1<<i);
        }
    } // now binary is int of input

    //printf("multiplicand: %d\n",multiplicand);
    float product = *(float *) &multiplier * *(float *) &multiplicand; // you are not allowed to print from this.
    unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.
    //printf("ref_bits: %d\n",1&ref_bits>>(EXP_SZ+FRAC_SZ));
    // SIGN
    /* ... */
    //printf("product: %f\n",product);
    bool sign = 1/product<0.0;
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ)));

    // EXP
    // get the exp field of the multiplier and multiplicand
    /* ... */
    unsigned int multiplier_nosign = multiplier<<1; // move sign bit
    unsigned int e_multiplier = (multiplier_nosign>>24);
    //printf("e_multiplier:%d\n",e_multiplier);
    unsigned int multiplicand_nosign = multiplicand<<1; // move sign bit
    unsigned int e_multiplicand = (multiplicand_nosign>>24);
    //printf("e_multiplicand:%d\n",e_multiplicand);
    // add the two exp together
    /* ... */
    unsigned int exp = e_multiplicand+e_multiplier;
    //printf("exp aafter addition:%d\n",exp);
    // subtract bias
    /* ... */
    exp = exp - 127-127;
    // FRAC
    // get the frac field of the multiplier and multiplicand
    /* ... */
    unsigned int f_multiplier = multiplier<<9;
    //printf("f-multiplier:%d\n",f_multiplier);
    unsigned int f_multiplicand = multiplicand<<9;
    // assuming that the input numbers are normalized floating point numbers, add back the implied leading 1 in the mantissa
    /* ... */
    
    double m_multiplier = (multiplier==0) ? 0.0:1.0;
    double m_multiplicand = (multiplicand==0) ? 0.0: 1.0;
    double fra = 0.0;
    
    for (size_t i = 31; 9<=i; i--)
    {
        if (((f_multiplier>>i)& (0b1))==1)
        {
            fra = pow(2.0,32-i);
            m_multiplier = m_multiplier+ 1/fra;
        }
        
    }
    //printf("m_multiplier:%lf\n",m_multiplier);
    for (size_t i = 31; 9<=i; i--)
    {
        if (((f_multiplicand>>i)& (0b1))==1)
        {
            fra = pow(2.0,32-i);
            m_multiplicand = m_multiplicand+ 1/fra;
        }
        
    }
    //printf("m_multiplicand:%lf\n",m_multiplicand);
    // multiply the mantissas
    /* ... */
    double multiply = m_multiplicand*m_multiplier;
    
    if (multiply==0.0)
    {
        exp=0;
    }
    double number = ldexp ( multiply, exp );
    //printf("number:%lf\n",number);
    // while(multiply>=10){
    //     multiply = multiply/10;
    //     exp+=1;
    // }
    
    //printf("exp after multiply:%d\n",exp);
    //multiply = multiply * pow(10,exp);
    double fraction = sign ? number : number;
    //printf("fraction: %lf\n",multiply);
    signed short trial_exp=(1<<(EXP_SZ-1))-1; // start by assuming largest possible exp (before infinity) 
    // do trial division until the proper exponent E is found
    /* ... */
    if (fraction==0.0)
    {
        trial_exp=0;
    }else{
        for (signed short i = trial_exp; i >= -1022; i--)
        {
            if ((fraction / pow(2,i)>=1) && (fraction / pow(2,i) <2))
            {
                trial_exp = i;
                break;
            }
            
        
        }
        
    }
    unsigned short bias = (1<<(EXP_SZ-1))-1;  // bias=1023    1.frac * 2^trail_exp
    signed short exp_new = trial_exp + bias;
    if (fraction==0.0)
    {
        exp_new=0;
    }else if(trial_exp==1023 && fraction<1.0){
        exp_new=0;
    }

    if (fraction==0.0)
    {
        fraction = fraction;
        //fraction = fraction / pow(2,trial_exp) - 1;
    }else if(trial_exp==1023 && fraction<1.0){
        fraction = fraction / pow(2,-1022);
        //printf("\nfrac: %lf\n",fraction);
    }else{
        fraction = fraction / pow(2,trial_exp) - 1;
    }

    bool frac_array[FRAC_SZ+1]; // one extra LSB bit for rounding
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        //frac_array[frac_index] = false; // frac set to zero to enable partial credit
        /* ... */
        if ((fraction * 2 >=0) && (fraction*2 <1))
        {
            frac_array[frac_index]=false;
            fraction = fraction * 2;
        }else if((fraction * 2 >=1) && (fraction*2 <2)){
            frac_array[frac_index]=true;
            fraction = fraction * 2 - 1;
        }else if(fraction==0.0){
            frac_array[frac_index]=false;
        }
        
    }
    // overflow and normalize
    /* ... */

    // rounding
    /* ... */
    bool carry = false;
    if (frac_array[0]==true)
    {
        carry = true;
        
    }
    for (int fra_index=1; fra_index<=FRAC_SZ; fra_index++)
    {
        if(frac_array[fra_index]==true && carry==true)
        {
            frac_array[fra_index]=false;
        }else if(frac_array[fra_index]==false && carry==true){
            frac_array[fra_index]=true;
            carry=false;
        }
    }
    
    // move decimal point
    /* ... */

    // PRINTING
    // print exp
    for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&exp_new>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    }
    printf("_");

    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
        assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }
    // // print frac
    // for ( int bit_index=FRAC_SZ-1; 0<=bit_index; bit_index-- ) {
    //     bool trial_bit = 1&frac>>bit_index;
    //     printf("%d",trial_bit);
    //     assert (trial_bit == (1&ref_bits>>(bit_index)));
    // }

    return(EXIT_SUCCESS);

}
