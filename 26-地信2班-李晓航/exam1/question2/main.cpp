#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    float price;
    int stock;

public:
   
    Book() {//构造函数 代表book的启始 
        title = "";//设定三个初始值 
        price = 0.0f;
        stock = 0;
    }

    ~Book() {//析构函数 代表book结束 
        cout << "Book 对象已销毁" << endl;
    }

    void input() {
        cout << "请输入书名：";
        cin.ignore();//可记录书名更加完整              
        getline(cin,title);

        cout << "请输入价格：";
        cin >> price;

        cout << "请输入库存：";
        cin >> stock;
    }

    void display() {
        cout << "书名：" << title << endl;
        cout << "价格：" << price << endl;
        cout << "库存：" << stock << endl;
    }
};

int main() {
    Book* p = new Book();
    p->input();//接入到input处 
    p->display();//接入到display处 
    delete p;//题目要求用完清除 

    return 0;
}
