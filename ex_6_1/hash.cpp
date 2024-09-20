#include "hash.h"

using namespace std;

dict::dict()
{
    this->count = 0;
    this->values.resize(10, nullptr);

    ifstream file;
    file.open("start.txt");

    string code, name;

    unispec *x = new unispec();
    for (int i = 0; i < 7; ++i)
    {
        file >> code >> name;
        x->code = code;
        x->name = name;
        this->insert(x);
        x = new unispec();
    }

    file.close();
    delete x;
}

int dict::format(string code)
{
    int cd = 0;
    for (int i = 0; i < code.length(); ++i)
    {
        cd += code[i];
    }
    return cd % this->values.size();
}

void dict::insert(unispec *el)
{
    int code = this->format(el->code);

    int i = 0;
    int ind = code;
    while (true)
    {
        if (ind + 7 * i > this->values.size())
        {
            this->rehash();
            continue;
        }
        if (this->values[ind + 7 * i])
        {
            ++i;
            continue;
        }
        this->values[ind + 7 * i] = el;
        this->count += 1;
        break;
    }
    if (((double)this->count) / this->values.size() >= 0.75)
    {
        this->rehash();
    }
}

void dict::del(string code)
{
    int ind = this->format(code);
    for (int i = ind; i < this->values.size(); i += 7)
    {
        if (this->values[i]->code == code)
        {
            unispec *x = this->values[i];
            this->values[i] = nullptr;
            delete x;
            return;
        }
    }
}

unispec *dict::find(string code)
{
    int ind = this->format(code);
    for (int i = ind; i < this->values.size(); i += 7)
    {
        if (this->values[i]->code == code)
        {
            return this->values[i];
        }
    }
    return nullptr;
}

void dict::show()
{
    for (auto x : this->values)
    {
        if (x)
        {
            cout << x->code << " " << x->name << '\n';
        }
    }
}

void dict::rehash()
{
    vector<unispec *> v{this->values.size() * 2, nullptr};
    
}