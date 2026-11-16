#include <iostream>
#include <string>
#include <cctype>//判断字母数字 
using namespace std;

int main() {
    string s;
    cout << "请输入一个字符串：";
    getline(cin, s);

    int letters = 0;   
    int digits = 0;    
    int others = 0;   

    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];//把每个单字拎出来方便isalpha和isdigit计算 
        if (isalpha(c)) {//认识字母的 
            letters++;
        } else if (isdigit(c)) {//认识数字 
            digits++;
        } else {
            others++;
        }
    }

    cout << "英文字母个数：" << letters << endl;
    cout << "数字个数：" << digits << endl;
    cout << "其他字符个数：" << others << endl;

    return 0;
}
