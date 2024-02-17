#include"../h/printFucntions.h"


void print(const char* string,unsigned long number){
    int i = 0;
    while(string[i]!='\0'){
        if(string[i] != '%') putc(string[i]);
        else {
            if(string[i+1] == 'd'){
                unsigned long  divisor = 1;
                unsigned long temp = number;
                do{
                    temp /= 10;
                    divisor *= 10;
                }while(temp != 0);
                divisor /= 10;
                while(divisor > 0 ){
                    unsigned digit = (number / divisor) % 10;
                    putc(digit + '0');
                    divisor /= 10;
                }
                i++;
            }
        }
        i++;
    }
}

