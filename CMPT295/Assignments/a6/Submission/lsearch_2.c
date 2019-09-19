

int lsearch_2(int *A, int n, int target) {

    //.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
    // Question 3(a):  Replace this code with the new algorithm 
    //.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
    if (n <= 0){
        return -1;
    }

    int temp = A[n-1];
    A[n-1] = target;

    int i = 0;
    while(A[i] != target){
        i += 1;
    }

    A[n-1] = temp;

    if(i<(n-1)){
        return i;
    } else if(A[n-1] == target){
        return (n-1);
    } else {
        return -1;
    }
    //.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
    
}  // lsearch_2


