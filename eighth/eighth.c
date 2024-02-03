#include<stdlib.h>
#include<stdio.h>


int findbitsizeint(int num){
    int count = 0;
    while (num > 0){
        count++;
        num /= 2;
    }
    return count;
}

int* convertbinaryint(int* num, int number, int bitsize){
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

int findnegativeexp(int* num, int bitsize){
    int count = 0;
    for(int i = 0; i < bitsize; i++){
        if(num[i] == 0){
            count--;
        }else{
            count--;
            return count;
        }
    }
    return count;
}

int* convertbinarydec(int* num, double number, int bitsize){
    double cpy = number;
    //int flag = 0;
    for (int i = 0; i < bitsize; i++){
        cpy *= 2;
        if (cpy < 1){
            num[i] = 0;
        }else{
            num[i] = 1;
            cpy -= 1;
        }
    }
    return num;
}

int* combine(int* main, int* decimal, int* integer, int bitsize, int bitsizedec, int bitsizeint, int exp){
    int integerindex = 1;
    int decimanindex = 0;
    if (exp == 0){
        for (int i = 0; i < bitsize; i++){
            if (decimanindex < bitsizedec){
                main[i] = decimal[decimanindex];
                decimanindex ++;
            }else{
                main[i] = 0;
            }
        }
        return main;
    }
    if (exp < 0){
        decimanindex = -1 * exp;
        for (int i = 0; i < bitsize; i++){
            if (decimanindex < bitsizedec){
                main[i] = decimal[decimanindex];
                decimanindex ++;
            }else{
                main[i] = 0;
            }
        }
        return main;
    }
    for (int i = 0; i < bitsize; i++){
        if (integerindex < bitsizeint){
            main[i] = integer[integerindex];
            integerindex++;
        }else if (decimanindex < bitsizedec){
            main[i] = decimal[decimanindex];
            decimanindex ++;
        }else{
            main[i] = 0;
        }
    }
    return main;
}






int main(int argc, char* argv[argc + 1]){
    if (argc < 2){
        printf("insufficient arguments\n");
        return (0);
    }

    FILE* fp  = fopen(argv[1], "r");
    //main number
    double number;
    int bitsize;
    int* mainbinary;

    //int part
    int whole;
    int bitsizeint;
    int* wholebin;

    //decimal part
    double decimal;
    int* decimalbinary;

    //for the exponent part
    int exp;
    while(fscanf(fp, "%lf %d", &number, &bitsize) != EOF){

        whole = number;
        mainbinary = malloc(bitsize * sizeof(int));
        for (int i = 0; i < bitsize; i++){
            mainbinary[i] = 0;
        }
        decimal = number - (double)whole;
        bitsizeint = findbitsizeint(whole);
        wholebin = malloc(bitsizeint * sizeof(int));
        wholebin = convertbinaryint(wholebin, whole, bitsizeint);
        decimalbinary = malloc(bitsize * sizeof(int));
        decimalbinary = convertbinarydec(decimalbinary, decimal, bitsize);

        if (bitsizeint == 0){
            exp = findnegativeexp(decimalbinary, bitsize);
        }else{
            exp = bitsizeint - 1;
        }
        
        mainbinary = combine(mainbinary, decimalbinary, wholebin, bitsize, bitsize, bitsizeint, exp);


        printf("1.");
        for (long i = 0; i < bitsize; i++){
            printf("%d", mainbinary[i]);
        }
        printf(" %d\n", exp);

        free(decimalbinary);
        free(wholebin);
        free(mainbinary);
    }
    
    return 0;
}