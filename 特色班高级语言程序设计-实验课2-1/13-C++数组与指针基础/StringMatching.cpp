#include <iostream>
#include <valarray>

using namespace std;

int main() {
    string str, pat;
    cin >> str >> pat;

    int currIndex = 0;
    bool flag = false;

    while(true) {
        string remain = str.substr(currIndex, string::npos);
        int pos = remain.find(pat);
        if (pos == string::npos)
            break;
        currIndex += pos;
        cout << currIndex << endl;
        if (!flag)
            flag = true;
        currIndex++;
        if (currIndex > str.length())
            break;
    }

    if (!flag)
        cout << "-1" << endl;
}
