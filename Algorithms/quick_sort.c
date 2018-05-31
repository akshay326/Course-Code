void quicksort(int*,int,int);

/**
 * Places the pivot element at correct position in array
 * @return Pivot Index
 */
int partition(int*,int,int);

void quicksort(int *a,int left, int right){
    if (left < right){
        int pivot = partition(a,left,right);

        quicksort(a,left,pivot-1);
        quicksort(a,pivot+1,right);
    }
}

int partition(int *a, int left, int right){
    int pivot = right, temp; // TODO change pivot here
    for(int i=left;i<right;++i)
        if (a[i] > a[pivot]){ // Swap them
            temp = a[i];
            a[i] = a[pivot];
            a[pivot] = temp;
        }
}