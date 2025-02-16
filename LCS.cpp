#include <iostream>
#include <vector>
using namespace std;

// Function to find LCS length and return the LCS sequence
string findLCS(const string &X, const string &Y) {
    int m = X.size();
    int n = Y.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1]; // Match
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // No match
            }
        }
    }

    // Reconstruct the LCS string
    int i = m, j = n;
    string lcs;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs; // Add to result
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return lcs;
}

int main() {
    string X, Y;

    // Take user input
    cout << "Enter first string: ";
    cin >> X;
    cout << "Enter second string: ";
    cin >> Y;

    string lcs = findLCS(X, Y);
    cout << "LCS: " << lcs << endl;
    
    return 0;
}
