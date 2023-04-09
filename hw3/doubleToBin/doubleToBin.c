#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[]) {

    // SETUP

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    double value;
    fscanf(fp, "%lf", &value);

    // the reference solution ('the easy way')
    // you are not allowed to print from this casted 'ref_bits' variable below
    // but, it is helpful for validating your solution
    unsigned long int ref_bits = *(unsigned long int*) &value;
    //printf("ref_bits: %ld\n", ref_bits);
    // THE SIGN BIT
    
    bool sign = 1/value<0.0;
    
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ))); // validate your result against the reference

    // THE EXP FIELD
    // find the exponent E such that the fraction will be a canonical fraction:
    // 1.0 <= fraction < 2.0
    double fraction = sign ? -value : value;
    //printf("\nfraction: %lf",fraction );
//
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
    
    
    //printf("trail_exp: %hi\n",trial_exp );


    unsigned short bias = (1<<(EXP_SZ-1))-1;  // bias=1023    1.frac * 2^trail_exp
    signed short exp = trial_exp + bias;
    if (fraction==0.0)
    {
        exp=0;
    }else if(trial_exp==1023 && fraction<1.0){
        exp=0;
    }
    
    //printf("exp: %d\n",exp);
    for ( int exp_index=EXP_SZ-1; 0<=exp_index; exp_index-- ) {
        bool exp_bit = 1&exp>>exp_index;
        printf("%d",exp_bit);
        //assert (exp_bit == (1&ref_bits>>(exp_index+FRAC_SZ))); // validate your result against the reference
    }
    printf("_");
    // you get partial credit by getting the exp field correct
    // even if you print zeros for the frac field next
    // you should be able to pass test cases 0, 1, 2, 3

    // THE FRAC FIELD
    // prepare the canonical fraction such that:
    // 1.0 <= fraction < 2.0
    /* ... */
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
    
    
    

    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
        // assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }

}
