#include <stdio.h>
#include <limits.h>

#define MAX 20
#define INF 999999

int n;                          // No. of cities
int dist[MAX][MAX];             // Distance matrix
int dp[1<<MAX][MAX];            // DP table
int parent[1<<MAX][MAX];        // To reconstruct the path

// --------------------- TSP USING DP (BITMASK + HELD-KARP) --------------------
int TSP(int mask, int pos) {
    if (mask == (1<<n) - 1)      // All cities visited
        return dist[pos][0];     // Return to starting city

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    int city;

    for (city = 0; city < n; city++) {
        if (!(mask & (1 << city))) {     // If city is not visited
            int newAns = dist[pos][city] + 
                          TSP(mask | (1 << city), city);

            if (newAns < ans) {
                ans = newAns;
                parent[mask][pos] = city;  // Store path
            }
        }
    }

    return dp[mask][pos] = ans;
}

// ---------------------------- MAIN PROGRAM -----------------------------------
int main() {
    int i, j;

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("\nEnter the distance matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    // Initialize DP array
    for (i = 0; i < (1<<n); i++)
        for (j = 0; j < n; j++)
            dp[i][j] = -1;

    int minCost = TSP(1, 0);     // Start from city 0

    // ---------------------- PRINT RESULT -------------------------
    printf("\nMinimum cost: %d\n", minCost);

    printf("Tour: 0 ");
    int mask = 1, city = 0;

    while (1) {
        int nextCity = parent[mask][city];
        if (nextCity == 0 || nextCity == INF) break;

        printf("-> %d ", nextCity);
        mask |= (1 << nextCity);
        city = nextCity;

        if (mask == (1<<n)-1) break;
    }
    printf("-> 0\n");   // Return to start

    return 0;
}

