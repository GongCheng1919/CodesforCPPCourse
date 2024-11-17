#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {
    int rows1 = mat1.size();
    int cols1 = mat1[0].size();
    int rows2 = mat2.size();
    int cols2 = mat2[0].size();

    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    int m, n, s;


    cin >> m >> n >> s;
    vector<vector<int>> mat1(m, vector<int>(n)), mat2(n, vector<int>(s));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> mat1[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < s; j++){
            cin >> mat2[i][j];
        }
    }


    vector<vector<int>> result = multiplyMatrices(mat1, mat2);
    printMatrix(result);

    return 0;
}
