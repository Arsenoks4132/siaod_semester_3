#include <random>
#include <iostream>
#include <fstream>

using namespace std;

struct product
{
    int code;
    char name[50];
};

int main()
{
    cout << sizeof(product) << endl;
}