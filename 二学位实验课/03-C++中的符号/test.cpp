#include<bits/stdc++.h>
using namespace std;

int countSubstr(char* str1, char* str2) {
    int count = 0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int i, j;
    for (i = 0; i < len1; i++) {
        for (j = 0; j < len2; j++) {
            if (str1[i] == str2[j]) {
                i++;
            }
            else {
                i -= j;
                break;
            }
        }
        if (j == len2) {
            count++;
            i -= j;
        }
    }
    return count;
}

int main() {
    char str1[100], str2[100];
    cin.getline(str1, 100);
    cin.getline(str2, 100);
    cout << countSubstr(str1, str2);
    return 0;
}