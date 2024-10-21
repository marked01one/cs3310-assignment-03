#include <algorithm>
#include <chrono>
#include <limits>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

int max_route(vector<vector<int>>& matrix, int n, int m) {
    if (n == 0 && m == 0) return matrix[n][m];
    if (n == 0) return max_route(matrix, 0, m-1) + matrix[n][m];
    if (m == 0) return max_route(matrix, n-1, 0) + matrix[n][m];

    int horizontal = max_route(matrix, n-1, m);
    int vertical = max_route(matrix, n, m-1);
    int diagonal = max_route(matrix, n-1, m-1);

    return max(diagonal, max(horizontal, vertical)) + matrix[n][m];
}

int max_route_dp(vector<vector<int>>& matrix, int n, int m, vector<vector<int>>& checker, vector<vector<int>>& cache) {
    if (checker[n][m] == 1) return cache[n][m];
    
    int max_value;
    
    if (n == 0 && m == 0) {
        max_value = matrix[n][m];
    }
    else if (n == 0) {
        max_value = max_route_dp(matrix, n, m-1, checker, cache) + matrix[n][m];
    }
    else if (m == 0) {
        max_value = max_route_dp(matrix, n-1, m, checker, cache) + matrix[n][m];
    }
    else {
        int horizontal = max_route_dp(matrix, n-1, m, checker, cache);
        int vertical = max_route_dp(matrix, n, m-1, checker, cache);
        int diagonal = max_route_dp(matrix, n-1, m-1, checker, cache);
        max_value = max(diagonal, max(vertical, horizontal)) + matrix[n][m];
    }

    checker[n][m] = 1;
    cache[n][m] = max_value;
    return max_value;

}

int main() {
    int n = 9;
    int m = 9;
    vector<vector<int>> matrix(n, vector<int>(m, 0));


    random_device rd_1, rd_2;
    mt19937 gen_1(rd_1()), gen_2(rd_2());

    uniform_int_distribution<> dist_1(-1000, 1000);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) matrix[i][j] = dist_1(gen_1); 
    }


    vector<vector<int>> checker(n, vector<int>(m, 0));
    vector<vector<int>> cache(n, vector<int>(m, numeric_limits<int>::infinity() * -1));

    chrono::time_point start = chrono::high_resolution_clock::now();
    chrono::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed;
    
    cout << "Matrix size: (" << matrix.size() << ", " << matrix[0].size() << ")" << endl;
    
    start = chrono::high_resolution_clock::now();
    int max_value = max_route(matrix, n-1, m-1);
    cout << "\nMax value: " << max_value;
    end = chrono::high_resolution_clock::now();

    elapsed = end - start;
    cout << "\nTime taken: " << elapsed.count() * 1000 << " miliseconds" << endl;

    start = chrono::high_resolution_clock::now();
    int max_value_dp = max_route_dp(matrix, n-1, m-1, checker, cache);
    cout << "\nMax value (DP): " << max_value_dp;
    end = chrono::high_resolution_clock::now();

    elapsed = end - start;
    cout << "\nTime taken: " << elapsed.count() * 1000 << " miliseconds";
}