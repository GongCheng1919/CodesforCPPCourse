#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Database {
private:
    std::vector<std::pair<std::string, std::string>> data;

public:
    // 查询操作
    std::string query(const std::string& key) const {
        for (const auto& p : data) {
            if (p.first == key) {
                return p.second;
            }
        }
        return "Not found"; // 返回一个默认值或者抛出异常
    }

    // 插入操作
    void insert(const std::string& key, const std::string& value) {
        auto it = std::find_if(data.begin(), data.end(), [&key](const auto& p) {
            return p.first == key;
        });
        if (it == data.end()) {
            data.push_back({key, value}); // 如果key不存在，则插入新的键值对
        } else {
            it->second = value; // 如果key存在，则更新对应的值
        }
    }

    // 删除操作
    void deleteKey(const std::string& key) {
        auto it = std::remove_if(data.begin(), data.end(), [&key](const auto& p) {
            return p.first == key;
        });
        if (it != data.end()) {
            data.erase(it, data.end());
        }
    }

    // 更新操作
    void update(const std::string& key, const std::string& value) {
        auto it = std::find_if(data.begin(), data.end(), [&key](const auto& p) {
            return p.first == key;
        });
        if (it != data.end()) {
            it->second = value; // 如果key存在，更新对应的值
        } else {
            data.push_back({key, value}); // 如果key不存在，插入新的键值对
        }
    }

    // 打印所有数据区的内容
    void print() const {
        for (const auto& p : data) {
            std::cout << p.first << " " << p.second << std::endl;
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    Database db;
    std::string key, value, operation;
    for (int i = 0; i < n; ++i) {
        std::cin >> key >> value >> operation;
        // if (operation == "q") {
        //     std::cout << "Query result: " << db.query(key) << std::endl;
        // } else 
        if (operation == "i") {
            db.insert(key, value);
        } else if (operation == "d") {
            db.deleteKey(key);
        } else if (operation == "u") {
            db.update(key, value);
        }
    }
    db.print();
    return 0;
}