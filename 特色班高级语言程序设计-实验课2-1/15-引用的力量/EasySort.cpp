#include <iostream>
#include <vector>

using namespace std;
void sort(vector<int>& arr){
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr);
    for(int i = 0; i < n; i++)
        cout << arr[i] << " \n"[i == n - 1];
}
