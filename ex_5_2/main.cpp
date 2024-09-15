#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std;

struct product
{
    int code;
    char name[50];
};

struct table
{
    int code;
    int offset;
    table(int code, int offset)
    {
        this->code = code;
        this->offset = offset;
    }
};

bool compare_tables(const table *pr1, const table *pr2)
{
    return pr1->code < pr2->code;
}

void generate_file(string fname, int cnt)
{
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

    for (int i = 0; i < cnt; ++i)
    {
        temp << (100000 + rd() % 899999) << " " << names[rd() % names.size()] << '\n';
    }
    temp.close();
    temp.open("temp.txt", ios::in);

    fstream file;
    file.open(fname, ios::binary | ios::out | ios::trunc);

    product *x = new product();

    while (temp >> x->code >> x->name)
    {
        file.write((char *)x, sizeof(product));
    }

    // sort(for_sort.begin(), for_sort.end(), compare_products);
    file.close();
    temp.close();
}

void show_file(string fname)
{
    fstream file;
    file.open(fname, ios::binary | ios::in);
    product *x = new product();
    while (file.read((char *)x, sizeof(product)))
    {
        cout << x->code << " " << x->name << endl;
    }
    file.close();
}

void linear_search(string fname, int code)
{
    fstream file;
    file.open(fname, ios::binary | ios::in);
    product *x = new product();
    while (file.read((char *)x, sizeof(product)))
    {
        if (x->code == code)
        {
            cout << x->code << " " << x->name << endl;
            break;
        }
    }
    file.close();
}

int bin_search(char *fname, int code)
{
    fstream rd;
    rd.open(fname, ios::in | ios::binary);

    vector<table *> tb;

    int i = 0;
    product *x = new product();
    while (rd.read((char *)x, sizeof(product)))
    {
        tb.emplace_back(new table(x->code, i));
        ++i;
    }
    rd.close();

    sort(tb.begin(), tb.end(), compare_tables);

    if (tb.size() % 2 == 0)
    {
        tb.insert(tb.begin(), new table(-1, 0));
    }

    int m = ceil(tb.size() / 2.0);
    int q = floor(tb.size() / 2.0);

    table *found = nullptr;

    while (q > 0)
    {
        if (tb[m]->code == code)
        {
            found = tb[m];
            break;
        }

        if (tb[m]->code < code)
        {
            m += ceil(q / 2.0);
        }
        else
        {
            m -= ceil(q / 2.0);
        }
        q = floor(q / 2.0);
    }

    if (found)
    {
        x = new product();
        FILE *file = fopen(fname, "rb");
        fseek(file, sizeof(product) * found->offset, SEEK_SET);
        fread(x, sizeof(product), 1, file);
        cout << x->name << endl;
        return found->offset;
    }
    return -1;
}

int main()
{
    char *fname{"test.bin"};
    generate_file(fname, 10);
    show_file(fname);

    cout << "Введите код для поиска: ";
    int code;
    cin >> code;

    auto begin = chrono::high_resolution_clock::now();
    int offset = bin_search(fname, code);
    auto end = chrono::high_resolution_clock::now();

    cout << endl;
    cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "мс" << endl;
    return 0;
}