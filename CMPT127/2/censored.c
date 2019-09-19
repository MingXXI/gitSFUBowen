#include <stdio.h>
#include <string.h>

int main( int argc, char* argv[]){
	char oneword[128];     //word
	int i = 0;
	int j = 0;
  	char current;        //c
 	int check = 0;   //flag
	while ((current = getchar()) != EOF){
		check = 0;
    		if(('a' <= current && current <= 'z')||('A' <= current && current <= 'Z')|| current == '\''){
      			oneword[i] = current ;
      			i++;
    		}
    		else
    		{
      			oneword[i] = 0 ;
      			j = 1;

      			while(j < argc)
      			{
        			if (strcmp(oneword, argv[j]) == 0)
        			{
          				printf("CENSORED");
          				check = 1;
          				break;
        			}
        			j++;
      			}

      			if (check != 1)
      			{
        			printf("%s",oneword);
      			}

      			printf("%c",current);
      			i = 0;

    		}

  	}
   	 return 0;
}
