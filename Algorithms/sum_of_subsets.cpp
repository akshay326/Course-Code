#include <bits/stdc++.h>
using namespace std;

static int total_nodes;

// prints subset found
void printSubset(int A[], int size) {
    for (int i = 0; i < size; i++)
        printf("%*d", 5, A[i]);

    printf("\n");
}

// qsort compare function
int comparator(const void *pLhs, const void *pRhs) {
    auto lhs = (int *) pLhs;
    auto *rhs = (int *) pRhs;

    return *lhs > *rhs;
}

// inputs
// s            - set vector
// t            - tuplet vector
// s_size       - set size
// t_size       - tuplet size so far
// sum          - sum so far
// ite          - nodes count
// target_sum   - sum to be found
void subset_sum(int s[], int t[],
                int s_size, int t_size,
                int sum, int ite,
                int const target_sum) {
    total_nodes++;

    if (target_sum == sum) {
        // We found sum
        printSubset(t, t_size);

        // constraint check
        if (ite + 1 < s_size && sum - s[ite] + s[ite + 1] <= target_sum) {
            // Exclude previous added item and consider next candidate
            subset_sum(s, t, s_size, t_size - 1, sum - s[ite], ite + 1, target_sum);
        }
        return;
    } else {
        // constraint check
        if (ite < s_size && sum + s[ite] <= target_sum) {
            // generate nodes along the breadth
            for (int i = ite; i < s_size; i++) {
                t[t_size] = s[i];

                if (sum + s[i] <= target_sum) {
                    // consider next level node (along depth)
                    subset_sum(s, t, s_size, t_size + 1, sum + s[i], i + 1, target_sum);
                }
            }
        }
    }
}

// Wrapper that prints subsets that sum to target_sum
void generateSubsets(int s[], int size, int target_sum) {
    auto *tuplet_vector = (int *) malloc(size * sizeof(int));

    int total = 0;

    // sort the set
    qsort(s, static_cast<size_t>(size), sizeof(int), &comparator);

    for (int i = 0; i < size; i++)
        total += s[i];

    if (s[0] <= target_sum && total >= target_sum)
        subset_sum(s, tuplet_vector, size, 0, 0, 0, target_sum);

    free(tuplet_vector);
}

int main() {
    int weights[] = {5, 8, 4, 6, 2, 9};
    int target = 11;

    int size = sizeof(weights) / sizeof(weights[0]);

    generateSubsets(weights, size, target);

    printf("Nodes generated %d\n", total_nodes);

    return 0;
}

