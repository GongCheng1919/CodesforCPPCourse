#include <iostream>  
#include <cmath> // 用于 sqrt 和 pow 函数  
  
// 枚举类型，定义图形种类  
enum ShapeType {  
    Circle,  
    Rectangle,  
    Triangle  
};  
  
// 共用体，用于存储不同类型图形的数据  
union ShapeData {  
    struct {  
        double radius; // 圆形的半径  
    } circle;  
    struct {  
        double width, height; // 矩形的宽度和高度  
    } rectangle;  
    struct {  
        double base, height; // 三角形的底边和高  
    } triangle;  
};  
  
// 结构体，表示一个图形  
struct Shape {  
    ShapeType type;  
    ShapeData data;  
  
    // 计算面积的成员函数  
    double area() const {  
        switch (type) {  
            case Circle:  
                if (data.circle.radius < 0) return -1;  
                return M_PI * data.circle.radius * data.circle.radius;  
            case Rectangle:  
                if (data.rectangle.width < 0 || data.rectangle.height < 0) return -1;  
                return data.rectangle.width * data.rectangle.height;  
            case Triangle:  
                if (data.triangle.base < 0 || data.triangle.height < 0) return -1;  
                return 0.5 * data.triangle.base * data.triangle.height;  
            default:  
                return 0.0; // 默认情况处理  
        }  
    }  
};  
  
int main() {  
    int a, b, k;  
    std::cin >> a >> b >> k;  
    int **arr1 = new int*[a];  
    for(int i = 0; i < a; i++){  
        arr1[i] = new int[b];  
    }  
  
    int **arr2 = new int*[a];  
    for(int i = 0; i < a; i++){  
        arr2[i] = new int[b];  
    }  
  
    int **ans = new int*[a];  
    for(int i = 0; i < a; i++){  
        ans[i] = new int[b];  
    }  
  
    for(int i = 0; i < a; i++){  
        for(int j = 0; j < b; j++){  
            std::cin >> arr1[i][j];  
        }  
    }  
  
    for(int i = 0; i < a; i++){  
        for(int j = 0; j < b; j++){  
            std::cin >> arr2[i][j];  
            ans[i][j] = arr1[i][j] + arr2[i][j];  
        }  
    }  
  
    for(int i = 0; i < a; i++){  
        for(int j = 0; j < b; j++){  
            std::cout << ans[i][j] << " \n"[j == b - 1];  
            ans[i][j] *= k;  
        }  
  
    }  
    std::cout << std::endl;  
    for(int i = 0; i < a; i++){  
        for(int j = 0; j < b; j++){  
            std::cout << ans[i][j] << " \n"[j == b - 1];  
        }  
    }  
  
    return 0;  
}
