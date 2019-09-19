
#include <stdio.h>
#include <string.h>
int main(){
    char list[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    float lett[26]={0};
    int c = getchar(),i;
    float sum=0;
    while (c != EOF)
    {
        for (i=0;i<26;i++){
            if(list[i]==c | list[i+26]==c){
                lett[i]++;
            }
        }
        c = getchar();
    }
    for (i=0;i<26;i++){
        sum=sum+lett[i];
    }
    for (i=0;i<26;i++){
        if(lett[i]!=0){
            printf("%c %.4f\n",list[i],(lett[i]/sum));
        }
    }
}

