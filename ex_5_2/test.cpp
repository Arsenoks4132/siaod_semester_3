#include <random>
#include <iostream>
#include <fstream>

using namespace std;

struct tst
{
    int code;
    string name;
};

int main()
{
    tst x;
    x.code = 123;
    x.name = "mask";

    fstream tab("test.dat", ios::binary | ios::out | ios::trunc);
    tab.write((char *) &x, sizeof(tst));
    
    tab.close();

    fstream rd("test.dat", ios::binary | ios::in);

    tst *y = new tst();
    rd.read((char *) y, sizeof(tst));
    cout << y->code << " " << y->name;
    rd.close();
}