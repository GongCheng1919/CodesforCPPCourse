#include <iostream>
#include <string>
#include <vector>
using namespace std;


// 查找所有重复次数大于2并且在原始字符中总重复字符数大于9的最长重复子串 
void findAllRepeatedSubstrings(const std::string& input, 
    std::vector<std::string>& repeatedSubstrings,
    std::vector<int>& repetitionCounts) {

    // std::vector<std::string> repeatedSubstrings;
    // std::vector<int> repetitionCounts;
    
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '^') continue;
        for (int j = i+1; j < input.length(); j++) {
            // if (input[j+1] == '^') break;
            std::string substring = input.substr(i, j - i);
            if (substring[substring.length()-1] == '^'){
                break;
            }
            
            int count = 1;

            for (int k = i+substring.length(); k < input.length(); k ++) {
                // if (substring == "go "){
                //     std:cout<<"input.substr(k, substring.length())="<<input.substr(k, substring.length())<<std::endl;
                // }
                if (input.substr(k, substring.length()) == substring) {
                    count++;
                } 
                // else {
                //     break;
                // }
            }
            if (count >= 2 && substring.length()>2){
                bool alreadyExists = false;
                for (int l = 0; l < repeatedSubstrings.size(); l++) {
                    if (repeatedSubstrings[l] == substring)
                    {
                        alreadyExists = true;
                        repetitionCounts[l] += count;
                        break;
                    }
                }

                if (!alreadyExists) {
                    repeatedSubstrings.push_back(substring);
                    repetitionCounts.push_back(count);
                }
            }
        }
    }

    // for (int i = 0; i < repeatedSubstrings.size(); i++) {
    //     std::cout << repeatedSubstrings[i] << ": " << repetitionCounts[i] << std::endl;
    // }
}


// 实现一个函数findMostLengthRepeatedSubstrings查找字符串中最长的重复字串（至少重复2次），并且返回重复字符串以及重复次数
std::pair<std::string, int> findMostLengthRepeatedSubstrings(const std::string& input) {
    std::vector<std::string> repeatedSubstrings;
    std::vector<int> repetitionCounts;

    findAllRepeatedSubstrings(input, repeatedSubstrings, repetitionCounts);

    int maxLength = 0;
    int max_saved_chars = 0;
    int maxIndex = -1;
    int maxcount = 0;
    string max_string=" ";

    // std::cout<<"Step ******************** length = "<<repeatedSubstrings.size()<<std::endl;
    // std::cout<<input<<std::endl;
    for (int i = 0; i < repeatedSubstrings.size(); i++) {
        // 这里的筛选条件应该是，选择减少字符数最多的压缩，比如一个4字符的有8个，可以被替换为2字符，减少（4-2）*8=16字符。另外一个8字符的2个，可以减少（8-2）*2=12个字符。当然应该选择前者
        // int reduced_chars = (repeatedSubstrings[i].length()-2)*repetitionCounts[i];
        // if (reduced_chars > max_saved_chars) {
        //     max_saved_chars = reduced_chars;
        //     maxIndex = i;
        //     maxcount = repetitionCounts[i];
        // }
        if (repeatedSubstrings[i].length() > maxLength) {
            maxLength = repeatedSubstrings[i].length();
            maxIndex = i;
            maxcount = repetitionCounts[i];
            max_string = repeatedSubstrings[i];
        }else if (repeatedSubstrings[i].length() == maxLength){ 
            if (repetitionCounts[i]>maxcount){
            // maxLength = repeatedSubstrings[i].length();
            maxIndex = i;
            maxcount = repetitionCounts[i];
            max_string = repeatedSubstrings[i];
            }else {
                
                // std::cout<<max_string<<std::endl;
                // for (int k=0;k<repeatedSubstrings.size();k++){
                //     std::cout<<"\t"<<repeatedSubstrings[k]<<":"<<repetitionCounts[k]<<std::endl;
                // }
                if (repeatedSubstrings[i]<max_string){
                    // std::cout<<"max_string="<<max_string<<", repeatedSubstrings[i]="<<repeatedSubstrings[i]<<std::endl;
                    maxIndex = i;
                    maxcount = repetitionCounts[i];
                    max_string = repeatedSubstrings[i];
                }
            }
        }
        
        // std::cout<<"max_string="<<max_string<<std::endl;
        // std::cout<<"i = "<<i<<", maxLength = "<<maxLength<<", maxIndex = "<<maxIndex<<", maxcount = "<<maxcount<<"===";
        // std::cout << repeatedSubstrings[i] << ": " << repetitionCounts[i] << std::endl;
    }
    // std::cout <<"final results: maxIndex="<<maxIndex<<"  " <<repeatedSubstrings[maxIndex] << ": " << repetitionCounts[maxIndex] << std::endl;
    // std::cout<<max_string<<std::endl;

    if (maxIndex != -1) {
        return std::make_pair(repeatedSubstrings[maxIndex], repetitionCounts[maxIndex]);
    } else {
        return std::make_pair("", 0);
    }
}

void findRepeatedSubstrings(const std::string& input,
            std::vector<std::string>& repeatedSubstrings,
            std::vector<int>& repetitionCounts){
    std::string search_input = input;
    int i = 0;
    while(search_input.length()){
        std::pair<std::string, int> tmp=findMostLengthRepeatedSubstrings(search_input);
        std::string repeatedSubstring = tmp.first;
        int repetitionCount = tmp.second;
        // std::cout<<"Step "<<i++<<": "<<search_input<<", repeatedSubstring: "<<repeatedSubstring<<", count: "<<repetitionCount<<std::endl;
        if (repeatedSubstring=="" || repetitionCount==0) break;
        repeatedSubstrings.push_back(repeatedSubstring);
        repetitionCounts.push_back(repetitionCount);

        // 将search_input中所有关于tmp.first的字符串替换为空字符串
        std::string replacement ="^";
        int pos = search_input.find(repeatedSubstring);
        while (pos != std::string::npos) {
            search_input.replace(pos, repeatedSubstring.length(), replacement);
            pos = search_input.find(repeatedSubstring, pos + replacement.length());
        }
    }

}

// 实现一个压缩字符串表示的函数，其通过上述的findRepeatedSubstrings查找出一个字符串中的所有重复次数大于2的子串，然后保留所有子串中总重复字符数>9的所有字串，然后在原始字符串中使用一个'^'字符紧接着该共享字符串的地址替换掉原始的共享字串，以压缩字符串长度存储 
std::string compressString(const std::string& input) {
    std::vector<std::string> repeatedSubstrings;
    std::vector<int> repetitionCounts;

    findRepeatedSubstrings(input, repeatedSubstrings, repetitionCounts);
     for (int i = 0; i < repeatedSubstrings.size(); i++) {
        std::cout << repeatedSubstrings[i] << ":" << repetitionCounts[i]<<":"<<i << std::endl;
    }

    std::string compressedString = input;
    for (int i = 0; i < repeatedSubstrings.size(); i++) {
        // if (repetitionCounts[i] * repeatedSubstrings[i].length() > 9) {
        std::string replacement = "^" + std::to_string(i);
        size_t pos = compressedString.find(repeatedSubstrings[i]);
        while (pos != std::string::npos) {
            compressedString.replace(pos, repeatedSubstrings[i].length(), replacement);
            pos = compressedString.find(repeatedSubstrings[i], pos + replacement.length());
        }
        // }
    }

    return compressedString;
}

int main() {
    std::string input;
    // std::cout << "Enter a long string: ";
    std::getline(std::cin, input);

    std::string compressedString = compressString(input);
    std::cout << "Compressed string: " << compressedString << std::endl;
    std::cout << "Compressed ratio: " << input.length()<<"/" <<compressedString.length() << std::endl;

    return 0;
}