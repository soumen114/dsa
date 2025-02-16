#include <iostream>
#include <vector>
using namespace std;

// Function to find and print the LCS table
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

    // Print LCS table
    cout << "\nLCS Table:\n  ";
    for (int j = 0; j < n; j++) cout << "  " << Y[j]; // Print Y labels
    cout << endl;
    
    for (int i = 0; i <= m; i++) {
        if (i > 0) cout << X[i - 1] << " "; // Print X labels
        else cout << "  "; // Align first row
        
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << "  "; // Print DP values
        }
        cout << endl;
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
    cout << "\nLCS: " << lcs << endl;

    return 0;
}
