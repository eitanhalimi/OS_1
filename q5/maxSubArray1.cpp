// C++ Program for Maximum Subarray Sum using Kadane's Algorithm
// complexity: O(n)
// src: https://www.geeksforgeeks.org/dsa/largest-sum-contiguous-subarray/

#include <bits/stdc++.h>
using namespace std;

// Function to find the maximum subarray sum O(n)
int maxSubarraySum(vector<int> &arr) {
    int res = arr[0];
    int maxEnding = arr[0];

    for (int i = 1; i < arr.size(); i++) {
      
        // Find the maximum sum ending at index i by either extending 
        // the maximum sum subarray ending at index i - 1 or by
        // starting a new subarray from index i
        maxEnding = max(maxEnding + arr[i], arr[i]);
      
        // Update res if maximum subarray sum ending at index i > res
        res = max(res, maxEnding);
    }
    return res;
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
