void merge(int *, int, int, int);
void mergeSort(int *, int, int);
void mergeSortIterative(int *, int);

void mergeSort(int *a, const int l, const int r) {
    if (r > l) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l,m, r);
    }
}

void mergeSortIterative(int *a, const int n) {
    // size doubles up every loop

    for (int size = 1; size < n; size *= 2)
        for (int left = 0; left < n - 1; left += 2 * size) {

            int mid = left + size - 1;

            int right = left + 2 * size - 1;
            if (right > n - 1) // If right end exceeds total length, truncate it
                right = n - 1;

            merge(a, left, mid, right);
        }
}

/*
 * 1. Complexity of both algorithms in the case of large datasets
 * 2. Which sort is the best one for large datasets
 */
void merge(int a[], int l, int m, int r) {
    // Create a small array
    // Better than creating a duplicate for original array
    int *b = malloc((r - l + 1) * sizeof(int));

    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r)
        if (a[i] < a[j]) {
            b[k] = a[i];
            ++k;
            ++i;
        } else {
            b[k] = a[j];
            ++k;
            ++j;
        }

    if (i > m) // Copy elements in the left side
        while (k < r - l + 1) {
            b[k] = a[j];
            ++k;
            ++j;
        }
    else // Copy elements in the right side
        while (k < r - l + 1) {
            b[k] = a[i];
            ++k;
            ++i;
        }

    for (k = 0; k < r - l + 1; ++k)
        a[l + k] = b[k];
}