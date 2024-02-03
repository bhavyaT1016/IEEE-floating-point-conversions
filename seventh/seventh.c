#include<stdio.h>
#include<stdlib.h>


int checkdomain(long num, long bitsize){
    long das = 1;
    for (long i = 0; i < bitsize - 1; i++){
        das *= 2;
    }
    if (num > das - 1){return 1;}

    if (num < (-1 * das)){return -1;}
    return 0;
}

long twopower(long power){
    long num = 1;
    for (long i = 0; i < power; i++){
        num *= 2;
    }
    return num;
}

long* addone(long* binary, long bitsize){
    int carry = 1;
    for (long i = bitsize - 1; i >= 0; i-- ){
        if(binary[i] == 0 && carry == 1){
            binary[i] = 1;
            break;
        }else{
            binary[i] = 0;
            carry = 1;
        }
    }
    return binary;
}

long* onescompliment(long* binary, long bitsize){
    for (long i = 0; i < bitsize; i++){
        if(binary[i] == 0){
            binary[i] = 1;
        }else{
            binary[i] = 0;
        }
    }
    return binary;
}

long* makebinary(long* binary, long num, long bitsize){
    long cpy = num;
    int isnegative = 0;
    if (cpy < 0){isnegative = 1;}
        for (long i = bitsize - 1; i >= 0; i--){
            if(cpy % 2 == 0){binary[i] = 0;}
            else{binary[i] = 1;}
            cpy /= 2;
        }
    if (isnegative == 1){
        binary = onescompliment(binary, bitsize);
        binary = addone(binary, bitsize);
    }
    return binary;
}

long* maxbinary(long* binary, long bitsize){
    binary[0] = 0;
    for (long i = 1; i < bitsize; i++){
        binary[i] = 1;
    }
    return binary;
}

long* minbinary(long* binary, long bitsize){
    binary[0] = 1;
    for (long i = 1; i < bitsize; i++){
        binary[i] = 0;
    }
    return binary;
}

void printnum(long* binary, long bitsize){
    for (long i = 0; i < bitsize; i++){
        printf("%ld", binary[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[argc+1]){
    // if (argc < 2){
    //     printf("insufficient arguments\n");
    //     return 0;
    // }
    FILE *fp = fopen("test2.txt", "r");
    long num;
    long bitsize;
    long* binary;
    while (fscanf(fp, "%ld %ld", &num, &bitsize) != EOF){
        //printf("%ld %ld\n", num, bitsize);
        if (bitsize <= 0 ){
            continue;
        }
        binary = malloc(bitsize * sizeof(long));
        int check = checkdomain(num, bitsize);
        if (check == 0){
            binary = makebinary(binary, num, bitsize);
        }else if(check > 0){
            binary = maxbinary(binary, bitsize);
        }else{
            binary = minbinary(binary, bitsize);
        }
        printnum(binary,bitsize);   
        free(binary);
    }
}