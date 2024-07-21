#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Student {
public:
    Student(int id, std::string name) : id(id), name(name) {
        students[id] = name;
        totalStudents++;
    }

    std::string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    static int getTotalStudents() {
        return totalStudents;
    }

    static std::string getNameById(int id) {
        return students[id];
    }

    static int getIdByName(const std::string& name) {
        for (const auto& student : students) {
            if (student.second == name) {
                return student.first;
            }
        }
        return -1; // return -1 if name not found
    }

    static void printStudentsAlphabetically() {
        std::vector<std::string> names;
        for (const auto& student : students) {
            names.push_back(student.second);
        }
        std::sort(names.begin(), names.end());
        for (const auto& name : names) {
            std::cout << name << std::endl;
        }
    }

private:
    const int id;
    std::string name;
    static std::map<int, std::string> students;
    static int totalStudents;
};

std::map<int, std::string> Student::students = {};
int Student::totalStudents = 0;

int main() {
    // Student s2(1, "Bob");
    // Student s1(2, "Alice");
    // Student s3(3, "Charlie");
    // int n;
    int id;
    string name;
    // cin >> n;
    cin >> id >> name;
    while (id != -1) {
        Student s(id, name);
        cin >> id >> name;
    }
    // for (int i = 0; i < n; i++) {
    //     cin >> id >> name;
    //     Student s(id, name);
    // }

    // std::cout << "Total students: " << Student::getTotalStudents() << "\n";
    // std::cout << "Name of student with ID 2: " << Student::getNameById(2) << "\n";
    // std::cout << "ID of student with name 'Charlie': " << Student::getIdByName("Charlie") << "\n";

    // std::cout << "Students in alphabetical order:\n";
    cout<<Student::getTotalStudents()<<endl;
    Student::printStudentsAlphabetically();

    return 0;
}
