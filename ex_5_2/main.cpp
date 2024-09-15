#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

struct product
{
    int code;
    char name[50];
};

void generate_file(string fname, int cnt) {
    random_device rd;
    mt19937 gen(rd());

    ifstream product_names;
    product_names.open("product_names.txt");
    vector<string> names;
    string p_name;
    while (!product_names.eof())
    {
        getline(product_names, p_name);
        names.push_back(p_name);
    }
    product_names.close();

    fstream temp;
    temp.open("temp.txt", ios::out | ios::trunc);
    
    for (int i = 0; i < cnt; ++i) {
        temp << (100000 + rd() % 899999) << " " << names[rd() % names.size()] << '\n';
    }
    temp.close();
    temp.open("temp.txt", ios::in);

    fstream file;
    file.open(fname, ios::binary | ios::out | ios::trunc);
    product* x = new product();

    while (temp >> x->code >> x->name)
    {
        file.write((char *) x, sizeof(product));
    }

    file.close();
    temp.close();
}

void show_file(string fname) {
    fstream file;
    file.open(fname, ios::binary | ios::in);
    product* x = new product();
    int code;
    while (file.read((char *) x, sizeof(product))) {
        code = x->code;
        //cout << x->code << " " << x->name << endl;
    }
    cout << code << endl;
    file.close();
}

void linear_search(string fname, int code) {
    fstream file;
    file.open(fname, ios::binary | ios::in);
    product* x = new product();
    while (file.read((char *) x, sizeof(product))) {
        if (x->code == code) {
            cout << x->code << " " << x->name << endl;
            break;
        }
    }
    file.close();
}

int main()
{
    string fname = "test.bin";
    generate_file(fname, 1000000);
    show_file(fname);

    cout << "Введите код для поиска: ";
    int code;
    cin >> code;
    
    
    auto begin = chrono::high_resolution_clock::now();
    linear_search(fname, code);
    auto end = chrono::high_resolution_clock::now();


    cout << endl;
    cout<<chrono::duration_cast<chrono::milliseconds>(end-begin).count()<<"мс"<< endl;
    return 0;
}