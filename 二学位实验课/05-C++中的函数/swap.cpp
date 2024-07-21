#include <iostream>
#include <vector>
#include <unordered_map>

struct Gift {
    std::string name;
    int quantity;
};

struct Child {
    int id;
    std::string name;
    std::vector<int> exchangeList;
    std::vector<Gift> gifts;
};


void swapGifts(Child& child1, Child& child2) {
    bool child1_has_the_gift = false, child2_has_the_gift = false;
    for (auto& gift : child1.gifts) {
        if (child2.gifts[0].name == gift.name) {
            gift.quantity++;
            child1_has_the_gift = true;
            break;
        }
    }
    if (!child1_has_the_gift) {
        Gift child2_gift = child2.gifts[0];
        child2_gift.quantity = 1;
        child1.gifts.push_back(child2_gift);
    }
    for (auto& gift : child2.gifts) {
        if (child1.gifts[0].name == gift.name) {
            gift.quantity++;
            child2_has_the_gift = true;
            break;
        }
    }
    if (!child2_has_the_gift) {
        Gift child1_gift = child1.gifts[0];
        child1_gift.quantity = 1;
        child2.gifts.push_back(child1_gift);
    }
    child1.gifts[0].quantity--;
    child2.gifts[0].quantity--;

    // 如果child1也在child2想要交换礼物的列表里，则把child2中关于child1的交换给去掉
    for (int i = 0; i < child2.exchangeList.size(); i++) {
        if (child2.exchangeList[i] == child1.id) {
            child2.exchangeList.erase(child2.exchangeList.begin() + i);
            break;
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Child> children;

    for (int i = 0; i < n; i++) {
        std::string name;
        int quantity;
        std::string giftName;
        std::cin >> name >> quantity >> giftName;

        std::vector<int> exchangeList(quantity);
        for (int j = 0; j < quantity; j++) {
            std::cin >> exchangeList[j];
        }
        std::vector<Gift> giftList(1, {giftName, quantity});

        Child child = {i, name, exchangeList, giftList};
        children.push_back(child);
    }

    for (auto& child : children) {
        for (int exchangeIndex : child.exchangeList) {
            if (exchangeIndex!=child.id && child.gifts[0].quantity > 0 && children[exchangeIndex].gifts[0].quantity > 0) {
                // print()
                // std::cout << child.name << " " << children[exchangeIndex].name << " "<<exchangeIndex << std::endl;
                swapGifts(child, children[exchangeIndex]);
            }
        }
    }

    for (const auto& child : children) {
        std::cout << child.name << " ";
        for (const auto& gift : child.gifts) {
            if (gift.quantity == 0) continue;
            std::cout << gift.name << ": " << gift.quantity;
            if (&gift != &child.gifts.back()) 
                std::cout << " ";
        }
        if (&child != &children.back())
            std::cout << std::endl;
        // << child.gifts.name << " " << child.second.gift.quantity << std::endl;
    }

    return 0;
}