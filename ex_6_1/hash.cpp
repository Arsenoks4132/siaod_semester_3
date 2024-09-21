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

int dict::format(string code, int dl)
{
    int cd = 0;
    for (int i = 0; i < code.length(); ++i)
    {
        cd += code[i];
    }
    return cd % dl;
}

void dict::insert(unispec *el)
{
    int code = this->format(el->code, this->values.size());

    int i = 0;
    int ind = code;
    while (true)
    {
        if (ind + 7 * i > this->values.size() - 1)
        {
            this->rehash();
            continue;
        }
        if (this->values[ind + 7 * i])
        {
            if (this->values[ind + 7 * i]->code == el->code)
            {
                this->values[ind + 7 * i]->name = el->name;
                this->count += 1;
                delete el;
                break;
            }
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
    int ind = this->format(code, this->values.size());
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
    int ind = this->format(code, this->values.size());
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
    bool rehashed = false;
    vector<unispec *> v;
    for (int i = 2; !rehashed; i *= 2)
    {
        v.resize(0);
        v.resize(this->values.size() * i, nullptr);
        rehashed = true;
        for (auto x : this->values)
        {
            if (x)
            {
                int code = this->format(x->code, v.size());
                if (code > v.size() - 1)
                {
                    rehashed = false;
                    break;
                }
                v[code] = x;
            }
        }
    }
    this->values = v;
}