int max(const int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp) {
    int output[n]; // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output to arr[]
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radix(int arr[], int n) {
    // Find the maximum number to know number of digits
    int m = max(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void radixsort(int list[], int len){

    // Separate +ve and -ve sub arrays
    int posList[20],negList[20],j=0,k=0;
    for(int i=0;i<len;++i)
        if (list[i] > 0)
            posList[j++] = list[i];
        else
            negList[k++] = -list[i];

    radix(posList,j);
    radix(negList,k);

    // re merge them
    int i = 0;
    while (k>0)
        list[i++] = -negList[--k];

    for(int l = 0;l<j;++l)
        list[i++] = posList[l];
}