// C++ Program to find the maximum subarray sum using nested loops 
// Time Complexity: O(n^2)
// src: https://www.geeksforgeeks.org/dsa/largest-sum-contiguous-subarray/

#include <bits/stdc++.h>
using namespace std;

// Function to find the maximum subarray sum O(n^2)
int maxSubarraySum(vector<int> &arr) {
    int res = arr[0];
  
    // Outer loop for starting point of subarray
  	for(int i = 0; i < arr.size(); i++) {
    	int currSum = 0;
      
        // Inner loop for ending point of subarray
        for(int j = i; j < arr.size(); j++) {
        	currSum = currSum + arr[j];
          
            // Update res if currSum is greater than res
            res = max(res, currSum);
        }
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
