#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
        int arr[80000];
        for (int i=0;i<80000;i++){
                arr[i]=80000-i;
        }
	for (int i=1;i<80000;i++){
		int temp=arr[i];
		int pos =i;
		while (pos >0 && arr[pos-1]>temp){
			arr[pos]=arr[pos-1];
			pos--;
		}
		arr[pos]=temp;
	}
}

int main(){
    int arr[40000];
    for (int i=0;i<40000;i++){
        arr[i]=40000-i;
    }
    for (int i=1;i<40000;i++){
        int temp=arr[i];
        int pos =i;
        while (pos >0 && arr[pos-1]>temp){
            arr[pos]=arr[pos-1];
            pos--;
        }
        arr[pos]=temp;
    }
}


int main(){
    int arr[20000];
    for (int i=0;i<20000;i++){
        arr[i]=20000-i;
    }
    for (int i=1;i<20000;i++){
        int temp=arr[i];
        int pos =i;
        while (pos >0 && arr[pos-1]>temp){
            arr[pos]=arr[pos-1];
            pos--;
        }
        arr[pos]=temp;
    }
}

int main(){
    int arr[80000];
    for (int i=0;i<80000;i++){
        arr[i]=i;
    }
    for (int i=1;i<80000;i++){
        int temp=arr[i];
        int pos =i;
        while (pos >0 && arr[pos-1]>temp){
            arr[pos]=arr[pos-1];
            pos--;
        }
        arr[pos]=temp;
    }
}

int main(){
    int arr[40000];
    for (int i=0;i<40000;i++){
        arr[i]=i;
    }
    for (int i=1;i<40000;i++){
        int temp=arr[i];
        int pos =i;
        while (pos >0 && arr[pos-1]>temp){
            arr[pos]=arr[pos-1];
            pos--;
        }
        arr[pos]=temp;
    }
}


int main(){
    int arr[20000];
    for (int i=0;i<20000;i++){
        arr[i]=i;
    }
    for (int i=1;i<20000;i++){
        int temp=arr[i];
        int pos =i;
        while (pos >0 && arr[pos-1]>temp){
            arr[pos]=arr[pos-1];
            pos--;
        }
        arr[pos]=temp;
    }
}


int main(){
    srand((unsigned)time(0));
    int arr[80000];
    for (int i=0;i<80000;i++){
        arr[i]=rand();
    }
    for (int i=1;i<80000;i++){
        int temp=arr[i];
        int pos =i;
        while (pos >0 && arr[pos-1]>temp){
            arr[pos]=arr[pos-1];
            pos--;
        }
        arr[pos]=temp;
    }
}

int main(){
    srand((unsigned)time(0));
    int arr[40000];
    for (int i=0;i<40000;i++){
        arr[i]=rand();
    }
    for (int i=1;i<40000;i++){
        int temp=arr[i];
        int pos =i;
        while (pos >0 && arr[pos-1]>temp){
            arr[pos]=arr[pos-1];
            pos--;
        }
        arr[pos]=temp;
    }
}


int main(){
    srand((unsigned)time(0));
    int arr[20000];
    for (int i=0;i<20000;i++){
        arr[i]=rand();
    }
    for (int i=1;i<20000;i++){
        int temp=arr[i];
        int pos =i;
        while (pos >0 && arr[pos-1]>temp){
            arr[pos]=arr[pos-1];
            pos--;
        }
        arr[pos]=temp;
    }
}


