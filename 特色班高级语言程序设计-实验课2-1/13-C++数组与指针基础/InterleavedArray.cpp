#include <iostream>
using namespace std;

int main() {
    int row;
    cin >> row;

    int* col = new int[row];
    int totalElements = 0;

    for (int i = 0; i < row; i++) {
        cin >> col[i];
        totalElements += col[i];
    }

    int* data = new int[totalElements];
    int** arr = new int*[row];
    int cnt = 0;

    for (int i = 0; i < row; i++) {
        arr[i] = data + cnt;
        for (int j = 0; j < col[i]; j++) {
            arr[i][j] = ++cnt;
            cout << arr[i][j];
            if (j != col[i] - 1)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    int amount;
    cin >> amount;
    int* index = new int[amount];

    for (int i = 0; i < amount; i++) {
        cin >> index[i];
        if (index[i] < totalElements) {
            cout << *(data + index[i]) << endl;
        } else {
            cout << "ERROR" << endl;

            delete[] data;
            delete[] arr;
            delete[] col;
            delete[] index;
            return 0;
        }
    }

    delete[] data;
    delete[] arr;
    delete[] col;
    delete[] index;

    return 0;
}
