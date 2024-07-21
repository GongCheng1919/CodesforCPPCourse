#include <iostream>

using namespace std;
class DynamicArray {
  private:
    int *arr;
    int size;
    int capacity;

  public:
    DynamicArray() {
        size = 0;
        capacity = 1;
        arr = new int[capacity];
    }

    // 初始化时指定容量
    DynamicArray(int capacity) : size(0), capacity(capacity) {
        arr = new int[capacity];
    }

    // 动态扩容
    void push(int val) {
        if (size == capacity) {
            int *newArr = new int[capacity * 2];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            capacity *= 2;
        }
        arr[size] = val;
        size++;
    }

    int pop() {
        if (size == 0) {
            cout << "Array is empty" << endl;
            return -1;
        }
        int val = arr[size - 1];
        size--;
        return val;
    }

    int head() {
        int ret = arr[0];
        if (size == 0) {
            cout << "Array is empty" << endl;
            return -1;
        }
        for (int i = 1; i < size; i++) {
            arr[i - 1] = arr[i];
        }
        size--;
        return ret;
    }

    void deleteElement(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds" << endl;
            return;
        }
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " \n"[i == size - 1];
        }
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    ~DynamicArray() {
        delete[] arr;
    }
};

int main() {
    int intialCapacity;
    cin >> intialCapacity;
    DynamicArray arr(intialCapacity);
    int temp;
    while (cin >> temp) {
        arr.push(temp);
        if (getchar() == '\n')
            break;
    }
    while (cin >> temp) {
        arr.push(temp);
        if (getchar() == '\n')
            break;
    }

    int deleteIndex;
    cin >> deleteIndex;
    arr.deleteElement(deleteIndex);
    cout << arr.getSize() << endl;
    arr.print();

    arr.pop();
    arr.head();
    arr.print();
    return 0;
}