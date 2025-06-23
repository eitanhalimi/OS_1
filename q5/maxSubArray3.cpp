// C++ Program to find the maximum subarray sum using brute-force
// Time Complexity: O(n^3)
// src: https://cses.fi/book/book.pdf
#include <bits/stdc++.h>
using namespace std;

// Function to find the maximum subarray sum O(n^3)
int maxSubarraySum(const vector<int> &arr) {
    int best = 0;
    for (int a = 0; a < arr.size(); a++) {
        for (int b = a; b < arr.size(); b++) {
            int sum = 0;
            for (int k = a; k <= b; k++) {
                sum += arr[k];
            }
            best = max(best, sum);
        }
    }
    return best;
}

// Generate input array of N random integers in range [-25, 74]
vector<int> generateInput(int N, int seed) {
    srand(seed);
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 100 - 25; // [0, 99] -> [-25, 74]
    }
    return arr;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <seed> <N>" << endl;
        return 1;
    }

    int seed = atoi(argv[1]);
    int N = atoi(argv[2]);

    if (N <= 0) {
        cerr << "Error: N must be positive." << endl;
        return 1;
    }

    // Generate input array
    vector<int> arr = generateInput(N, seed);

    // Calculate the maximum subarray sum
    int result = maxSubarraySum(arr);
    cout << "Max1:" << result << endl;

    return 0;
}
