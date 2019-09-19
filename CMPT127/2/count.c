
#include <stdio.h>
#include <ctype.h>
int main()
{
    unsigned long int charcount=0,wordcount=0,linecount=0;
    int letter;
    int word=0;
    while( (letter = getchar()) != EOF ){
        charcount ++;
        if(letter == '\n'){
            linecount++;
            if (word ==1){
                wordcount ++;
                word=0;
            }
        }
        else if ((letter== 39) | (letter>64 & letter<91) | (letter<123 & letter>96)){
            if (word ==0){
                word =1;
            }
        }else if(letter==32){
            if (word ==1){
                wordcount ++;
                word =0;
            }
        }
        else {
            if (word ==1){
                wordcount ++;
                word =0;
            }
        }
    }
    printf( "%lu %lu %lu\n", charcount, wordcount, linecount );
}

