#include<stdlib.h>
#include<stdio.h>
#include <math.h>


long twopower(int power){
    long num = 1;
    for (int i = 0; i < power; i++){
        num *= 2;
    }
    return num;
}

double twopowerdec(int power){
    double num = 0;
    for (int i = 0; i < power; i++){
        num /= 2;
    }
    return num;
}


int findbias(int bitsize){
    long das = 1;
    for (long i = 0; i < bitsize - 1; i++){
        das *= 2;
    }
    return das - 1;
}

int* convertbinaryint(int* num, unsigned int number, int bitsize){
    for (int i = bitsize - 1; i >= 0; i--){
        if (number % 2 != 0){
            num[i] = 1;
        }else{
            num[i] = 0;
        }
        number /= 2;
    }
    return num;
}

//  4 d
// 0100 1101
// 0 1001 101

int main(int argc, char* argv[argc + 1]){
    // if (argc < 2){
    //     printf("insufficient arguments\n");
    //     return (0);
    // }

    FILE* fp  = fopen("test1.txt", "r");

    //main number
    unsigned int number;
    int bitsize;
    int* mainbinary;
    //int binarylength;

    double answer;
    //int part
    int bitsizeint;

    //for the exponent part
    int precision;
    int bias;
    int exp;

    //for the mantissa
    int bitsizeman;

    while(fscanf(fp, "%d %d %d %x %d", &bitsize, &bitsizeint, &bitsizeman, &number, &precision) != EOF){
        
        int x = number; 
        printf("%d %d %d %d %d\n", bitsize, bitsizeint, bitsizeman, x, precision );
        // make the binary for the hex
        mainbinary = malloc(bitsize * sizeof(int));
        for (int i = 0; i < bitsize; i++){
            mainbinary[i] = 0;
        }
        mainbinary = convertbinaryint(mainbinary, number, bitsize);

        exp = 0;
        for(int i = bitsizeint; i > 0; i--){
            if (mainbinary[i] == 1){
                exp += 1 * twopower(bitsizeint - i);
            }
        }
        bias = findbias(bitsizeint);
        exp -= bias;
        answer = 1.0;
        if (exp == (-1 * bias)){
            exp = 1 - bias;
            answer = 0.0;
        }
        
        for(int i = bitsizeint + 1; i < bitsize; i++){
            if(mainbinary[i] == 1){
                double fraction = 1.0 / twopower(i - bitsizeint);
                answer += fraction;
            }
        }

        answer *= pow(2, exp);

        if(mainbinary[0] == 0){
            printf("%.*f\n",precision, answer);
        }else{
            printf("%.*f\n",precision, -1 * answer);
        }

        free(mainbinary);
    }
    
    return 0;
}