#include <iostream>
#include <algorithm>//score用 
#include <functional>//greater用 
using namespace std;

int main() {
    int scores[10] = {78, 92, 65, 88, 70, 95, 82, 60, 100, 85};

    
    sort(scores, scores + 10, greater<int>());

    cout << "成绩从高到低排序结果：" << endl;
    for (int i = 0; i < 10; i++) {
        cout << scores[i];
        if (i != 9) cout << " ";
    }
    cout << endl;

    return 0;
}
