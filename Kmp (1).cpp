#include <iostream>
#include <string>

using namespace std;

void computeLPSArray(string pat, int M, int* lps) {
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // LPS[0] is always 0

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    // Print the LPS array
    cout << "LPS Array: ";
    for (int i = 0; i < M; i++) {
        cout << lps[i] << " ";
    }
    cout << endl;
}

void KMPSearch(string pat, string txt) {
    int M = pat.length();
    int N = txt.length();

    int lps[M];

    // Compute LPS array
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    string txt, pat;

    cout << "Enter the text: ";
    getline(cin, txt);

    cout << "Enter the pattern: ";
    getline(cin, pat);

    KMPSearch(pat, txt);

    return 0;
}
