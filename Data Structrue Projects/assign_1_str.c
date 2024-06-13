#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Big_Int{
    char n[310];
    int snum;
}big;

big* add(big n1,big n2){
   int size1=strlen(n1.n);
   int num1[310];
   for(int i=0;i<size1+1;i++){
    
    
   }
}



int main(){
    big n1,n2;

    printf("Enter the number 1: \n");
    char num1[310];
    scanf("%s",&num1);
    if(num1[0]=='-'){
        n1.snum=1;
        num1[0]='0';
    }
    else n1.snum=0;
    strcpy(n1.n,num1);

    printf("Enter the number 2: \n");
    char num2[310];
    scanf("%s",&num2);
    if(num2[0]=='-'){
        n2.snum=1;
        num2[0]='0';
    }
    else n2.snum=0;

    strcpy(n2.n,num2);

    printf("the addition of the number gives :\n");


}