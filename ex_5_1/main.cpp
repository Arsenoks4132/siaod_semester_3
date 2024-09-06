#include <iostream>
#include <cmath>

using namespace std;

int main() {
    unsigned char x=32;
    unsigned char maska = 1;
    cout << "Исходное число: " << +x << endl;
    x = x | (maska<<6);
    cout << "Полученное число с 1 в 7-м бите: " << +x;

    return 0;
}


