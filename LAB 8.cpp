#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print the DP table
void printTable(int **dp, int m, int n) {
    printf("\nLCS DP Table:\n\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%3d ", dp[i][j]);
        }
        printf("\n");
    }
}

// Function to compute LCS using DP
char* computeLCS(char *X, char *Y, int m, int n) {
    // Allocate DP table
    int **dp = (int**) malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++)
        dp[i] = (int*) malloc((n + 1) * sizeof(int));

    // Fill the DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1])
                             ? dp[i - 1][j]
                             : dp[i][j - 1];
        }
    }

    // Print table
    printTable(dp, m, n);

    // Length of LCS
    int index = dp[m][n];
    printf("\nLength of LCS: %d\n", index);

    // Allocate memory for LCS string
    char *lcs = (char*) malloc((index + 1) * sizeof(char));
    lcs[index] = '\0';

    // Traceback to build one LCS
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--; j--; index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    // Free DP table memory
    for (int k = 0; k <= m; k++)
        free(dp[k]);
    free(dp);

    return lcs;
}

int main() {
    char *X, *Y;
    int size1, size2;

    // Dynamic memory allocation
    printf("Enter size of string X: ");
    scanf("%d", &size1);

    printf("Enter size of string Y: ");
    scanf("%d", &size2);

    X = (char*) malloc((size1 + 1) * sizeof(char));
    Y = (char*) malloc((size2 + 1) * sizeof(char));

    // Input the strings
    printf("Enter string X: ");
    scanf("%s", X);

    printf("Enter string Y: ");
    scanf("%s", Y);

    // Validations
    if (strlen(X) == 0 || strlen(Y) == 0) {
        printf("Error: Empty strings not allowed.\n");
        return 0;
    }

    printf("\nInput Strings:\nX = %s\nY = %s\n", X, Y);

    // Compute LCS
    char *result = computeLCS(X, Y, strlen(X), strlen(Y));

    // Print result
    printf("\nOne Longest Common Subsequence: %s\n\n", result);

    // Free memory
    free(X);
    free(Y);
    free(result);

    return 0;
}

