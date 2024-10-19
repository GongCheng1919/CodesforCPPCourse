#include <iostream>  
#include<string>
using namespace std;

// ����ö������  
enum Grade {
    A, B, C, D, F, INVALID
};

// ��������  
Grade getGrade(int score);
string gradeToString(Grade grade);

int main() {
    int score;
    cin >> score;

    Grade grade = getGrade(score);
    if (grade == INVALID) {
        cout << "Invalid score" ;
    }
    else {
        cout << gradeToString(grade) ;
    }

    return 0;
}

// ��������  
Grade getGrade(int score) {
    // ʵ�ָú���  
    if (score >= 90 && score <= 100) return A;
    else if (score >= 80 && score < 90) return B;
    else if (score >= 70 && score < 80) return C;
    else if (score >= 60 && score < 70) return D;
    else if (score >= 0 && score < 60) return F;
    else return INVALID;
}

// ��������  
string gradeToString(Grade grade) {
    // ʵ�ָú���  
    switch (grade) {
    case A: return "A";
    case B: return "B";
    case C: return "C";
    case D: return "D";
    case F: return "F";
    default: return "Invalid";
    }
}