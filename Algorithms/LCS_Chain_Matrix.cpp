#include <bits/stdc++.h>

using namespace std;

string lcs(const char *X, const char *Y, int m, int n) {
    int L[m + 1][n + 1];

    /* Following steps build L[m+1][n+1] in bottom up fashion. Note
       that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    // Following code is used to print LCS
    int index = L[m][n];

    // Create a character array to store the lcs string
    char lcs[index + 1];
    lcs[index] = '\0'; // Set the terminating character

    // Start from the right-most-bottom-most corner and
    // one by one store characters in lcs[]
    int i = m, j = n;
    while (i > 0 && j > 0) {
        // If current character in X[] and Y are same, then
        // current character is part of LCS
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1]; // Put current character in result
            i--;
            j--;
            index--;     // reduce values of i, j and index
        }

            // If not same, then find the larger of two and
            // go in the direction of larger value
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    return string(lcs);
}

// Pretty printing of a matrix chain product
void printParenthesis(int i, int j, int n, int *bracket, char &name) {
    // If only one matrix left in current segment
    if (i == j) {
        cout << name++;
        return;
    }

    cout << "(";

    // Recursively put brackets around subexpression
    // from i to bracket[i][j].
    // Note that "*((bracket+i*n)+j)" is similar to
    // bracket[i][j]
    printParenthesis(i, *((bracket + i * n) + j), n,
                     bracket, name);

    // Recursively put brackets around subexpression
    // from bracket[i][j] + 1 to j.
    printParenthesis(*((bracket + i * n) + j) + 1, j,
                     n, bracket, name);
    cout << ")";
}

// dimension of A[i] is p[i-1] x p[i]
void matrixChainOrder(const int p[], int n) {
    // 0th row and 0th column of m[][] are not used. Just to avoid n-1 vs n pretty code
    int m[n][n];

    // bracket[i][j] stores optimal break point in
    // subexpression from i to j.
    int bracket[n][n];

    /* m[i,j] = Minimum number of scalar multiplications
    needed to compute the matrix A[i]A[i+1]...A[j]*/

    // cost is zero when multiplying one matrix.
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    // L is chain length.
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;

                    // Each entry bracket[i,j]=k shows
                    // where to split the product arr
                    // i,i+1....j for the minimum cost.
                    bracket[i][j] = k;
                }
            }
        }
    }

    // The first matrix is printed as 'A', next as 'B',
    // and so on
    char name = 'A';

    cout << "Result is : ";
    printParenthesis(1, n - 1, n, (int *) bracket, name);
    cout << "\nOptimal Cost is : " << m[1][n - 1];
}

int main() {
//    char X[] = "ACDGBTF";
//    char Y[] = "DBCATGF";
//
//    cout << lcs(X, Y, strlen(X), strlen(Y));


    int arr[] = {5,10,20,10};
    int n = sizeof(arr) / sizeof(arr[0]);
    matrixChainOrder(arr, n);

    return EXIT_SUCCESS;
}