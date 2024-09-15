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

void show_file(char *fname)
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

    
    if (tb.size() % 2 != 0)
    {
        tb.insert(tb.begin(), new table(-1, 0));
    }

    tb.insert(tb.begin(), new table(-1, 0));

    int m = ceil(tb.size() / 2.0);
    int q = floor(tb.size() / 2.0);

    while (q > 0)
    {
        if (tb[m]->code == code)
        {
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

    if (tb[m]->code == code)
    {
        return tb[m]->offset;
    }
    return -1;
}

product *read_record(char *fname, int offset)
{
    product *x = new product();
    FILE *file = fopen(fname, "rb");
    fseek(file, sizeof(product) * offset, SEEK_SET);
    fread(x, sizeof(product), 1, file);
    fclose(file);
    return x;
}

// Функция проверки корректности поиска
void show_file_with_test(char *fname)
{
    fstream file;
    file.open(fname, ios::binary | ios::in);
    product *x = new product();
    while (file.read((char *)x, sizeof(product)))
    {
        if (read_record(fname, bin_search(fname, x->code))->code != x->code)
        {
            cout << "--- ";
        }
        cout << x->code << " " << x->name << endl;
    }
    file.close();
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

    product *x = read_record(fname, offset);

    cout << "Найденная запись: " << x->code << " " << x->name << endl;

    cout << endl;
    cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "мс" << endl;
    return 0;
}