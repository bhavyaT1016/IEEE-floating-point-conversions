#include<stdlib.h>
#include<stdio.h>
#include<math.h>


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

int findbias(int bitsizeint){
    int das = 1;
    for (int i = 0; i < bitsizeint - 1; i++){
        das *= 2;
    }
    return das - 1;
}

int* makebinary(int* binary, int num, int bitsize){
    int cpy = num;
    for (int i = bitsize - 1; i >= 0; i--){
        if(cpy % 2 == 0){
            binary[i] = 0;
        }else{
            binary[i] = 1;
        }
        cpy /= 2;
    }
    return binary;
}

int* convertbinarydec(int* num, double number, int bitsize, int bitsizeint){
    double cpy = number;
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

//6.375  
//0.5 
double preround(double numtoround, double smallestnum){
    int factor = numtoround / smallestnum;//12
    double lower = factor * smallestnum; //6
    double upper = lower + smallestnum; //6.5
    double mid = (lower + upper) / 2; //6.25

    if(numtoround > mid){
        return upper;
    }else if(numtoround < mid){
        return lower;
    }else{
        if (factor % 2 == 0){
            return lower;
        }else{
            return upper;
        }
    }

}

int findexp(double decimal){
    int exp = 0;
    double cpy = decimal; 
    if(decimal > 1){
        while(cpy >= 2){
            exp ++;
            cpy /= 2;
        }
        return exp;
    }else if(decimal != 0){
        while(cpy < 1){
            cpy *= 2;
            exp--;
        }
        return exp;
    }
    
    return exp;
}

int* combine(int* main, int* decimal, int* integer, int bitsize, int bitsizedec, int bitsizeint){
    int integerindex = 1;
    int decimanindex = 0;
    if (bitsizeint == 0){
        while(decimal[decimanindex] != 1){
            decimanindex++;
        }
        decimanindex++;
    }
    for(int i = 0; i < bitsizedec; i++){
        if (integerindex < bitsizeint){
            main[i] = integer[integerindex];
            integerindex ++;
        }else if(decimanindex < bitsizedec){
            main[i] = decimal[decimanindex];
            decimanindex ++;
        }else{
            main[i] = 0;
        }
    }
    return main;
}

void assemble(int* exponent, int* decimal, int bitsizeexp, int bitsizemantissa, int isnegative){
    printf("%d", isnegative);
    for (int i = 0; i < bitsizeexp; i++){
        printf("%d", exponent[i]);
    }
    for (int i = 0; i < bitsizemantissa; i++){
        printf("%d", decimal[i]);
    }
    printf("\n");
}

void assemblesubnormal(int* decimal, int bitsizeexp, int bitsizemantissa, int bitsizedec, int isnegative, int exp){
    printf("%d", isnegative);
    for (int i = 0; i < bitsizeexp; i++){
        printf("0");
    }
    int index = (-1 * exp);
    for(int i = 0 ; i < bitsizemantissa; i++){
        if(index < bitsizedec){
            printf("%d", decimal[index]);
            index++;
        }else{
            printf("0");
        }
    }
    printf("\n");
}






int main(int argc, char* argv[argc + 1]){
    // if (argc < 2){
    //     printf("insufficient arguments\n");
    //     return (0);
    // }

    FILE* fp  = fopen("test1.txt", "r");

    int isnegative = 0;
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

    int* combinedbinary;
    int* exponentbin; 

    //for the exponent part
    int bitsizeexp;
    int exp;
    int bias;


    //for the mantissa
    int bitsizeman;
    
    while(fscanf(fp, "%lf %d %d %d", &number, &bitsize, &bitsizeexp, &bitsizeman) != EOF){

        if(number < 0){
            isnegative = 1;
        }else{
            isnegative = 0;
        }

        mainbinary = malloc(bitsize * sizeof(int));
        for (int i = 0; i < bitsize; i++){
            mainbinary[i] = 0;
        }

        if (number < 0){
            number *= -1;
        }

        exp = findexp(number);
        number = preround(number, pow(2, exp) *  pow(2, -1 * bitsizeman));
        int expafter = findexp(number);
        if (expafter > exp){
            exp++;
        }

        whole = number;
        if (whole < 0){
            whole *= -1;
        }
        
        decimal = number - (double)whole;
        if(decimal < 0){
            decimal *= -1;
        }

        bitsizeint = findbitsizeint(whole);
        wholebin = malloc(bitsizeint * sizeof(int));
        wholebin = convertbinaryint(wholebin, whole, bitsizeint);
   
        decimalbinary = malloc(64 * sizeof(int));
        decimalbinary = convertbinarydec(decimalbinary, decimal, 64, bitsizeint);

        combinedbinary = malloc(64 * sizeof(int));
        combinedbinary = combine(combinedbinary, decimalbinary, wholebin, bitsize, 64, bitsizeint);

        bias = findbias(bitsizeexp);
        exp += bias;

        exponentbin = malloc(bitsizeexp * sizeof(int));
        if(exp <= 0){
            exp = 1 - bias;
            assemblesubnormal(decimalbinary, bitsizeexp, bitsizeman, 64, isnegative, exp);

        }else{
            exponentbin = makebinary(exponentbin, exp, bitsizeexp);
            assemble(exponentbin, combinedbinary, bitsizeexp, bitsizeman, isnegative);
            
        }   

        free(exponentbin);
        free(decimalbinary);
        free(wholebin);
        free(mainbinary);
        free(combinedbinary);
    }
    
    return 0;
}