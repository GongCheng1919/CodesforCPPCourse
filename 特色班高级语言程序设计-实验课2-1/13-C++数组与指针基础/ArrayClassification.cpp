#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    int n;
    cin>>n;

    vector<int> arr(n);
    vector<int> odd;
    vector<int> even;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if (arr[i] % 2){
            odd.push_back(arr[i]);
        } else {
            even.push_back(arr[i]);
        }
    }
    for(int i = 0; i < odd.size(); i++){
        cout << odd[i];
        if (i != odd.size() - 1)
            cout << " ";
    }
    cout << endl;
    for(int i = 0; i < even.size(); i++){
        cout << even[i];
        if (i != even.size() - 1)
            cout << " ";
    }
}
