#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	srand((unsigned)time(0));
	int arr[80000];
	for (int i=0;i<80000;i++){
		arr[i]=rand();
	}
	for (int i=0;i<79999;i++){
		int smallest=i;
		for(int j=i+1;j<80000;j++){
			if(arr[j]<arr[smallest]){
				smallest=j;
			}
		}
		int temp=arr[i];
		arr[i]=arr[smallest];
		arr[smallest]=temp;
	}
}

int main(){
    srand((unsigned)time(0));
    int arr[40000];
    for (int i=0;i<40000;i++){
        arr[i]=rand();
    }
    for (int i=0;i<39999;i++){
        int smallest=i;
        for(int j=i+1;j<40000;j++){
            if(arr[j]<arr[smallest]){
                smallest=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
    }
}

int main(){
    srand((unsigned)time(0));
    int arr[20000];
    for (int i=0;i<20000;i++){
        arr[i]=rand();
    }
    for (int i=0;i<19999;i++){
        int smallest=i;
        for(int j=i+1;j<20000;j++){
            if(arr[j]<arr[smallest]){
                smallest=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
    }
}

int main(){
    int arr[80000];
    for (int i=0;i<80000;i++){
        arr[i]=i;
    }
    for (int i=0;i<79999;i++){
        int smallest=i;
        for(int j=i+1;j<80000;j++){
            if(arr[j]<arr[smallest]){
                smallest=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
    }
}

int main(){
    int arr[40000];
    for (int i=0;i<40000;i++){
        arr[i]=i;
    }
    for (int i=0;i<39999;i++){
        int smallest=i;
        for(int j=i+1;j<40000;j++){
            if(arr[j]<arr[smallest]){
                smallest=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
    }
}

int main(){
    int arr[20000];
    for (int i=0;i<20000;i++){
        arr[i]=i;
    }
    for (int i=0;i<19999;i++){
        int smallest=i;
        for(int j=i+1;j<20000;j++){
            if(arr[j]<arr[smallest]){
                smallest=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
    }
}

int main(){
    int arr[80000];
    for (int i=0;i<80000;i++){
        arr[i]=80000-i;
    }
    for (int i=0;i<79999;i++){
        int smallest=i;
        for(int j=i+1;j<80000;j++){
            if(arr[j]<arr[smallest]){
                smallest=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
    }
}

int main(){
    int arr[40000];
    for (int i=0;i<40000;i++){
        arr[i]=40000-i;
    }
    for (int i=0;i<39999;i++){
        int smallest=i;
        for(int j=i+1;j<40000;j++){
            if(arr[j]<arr[smallest]){
                smallest=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
    }
}

int main(){
    int arr[20000];
    for (int i=0;i<20000;i++){
        arr[i]=20000-i;
    }
    for (int i=0;i<19999;i++){
        int smallest=i;
        for(int j=i+1;j<20000;j++){
            if(arr[j]<arr[smallest]){
                smallest=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest];
        arr[smallest]=temp;
    }
}

