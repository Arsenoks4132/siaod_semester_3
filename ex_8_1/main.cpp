#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct let
{
    char lt;
    int cnt;
    let(char lt, int cnt)
    {
        this->lt = lt;
        this->cnt = cnt;
    }
};

bool compare_lets(const let *pr1, const let *pr2)
{
    return pr1->cnt > pr2->cnt;
}

void rec(int st, int fn, int sm[], map<char, string> &codes, vector<let *> counts)
{
    if (st >= fn)
    {
        return;
    }
    char r = '0';
    int ed = fn;
    for (int i = st; i <= fn; ++i)
    {
        codes[counts[i]->lt] += r;
        if (i == fn || fn - st == 1 || (sm[i + 1] - sm[st]) > (sm[fn + 1] - sm[i + 1]))
        {
            r = '1';
            ed = i;
            break;
        }
    }
    for (int i = ed + 1; i <= fn; ++i)
    {
        codes[counts[i]->lt] += r;
    }
    rec(st, ed, sm, codes, counts);
    rec(ed + 1, fn, sm, codes, counts);
}

map<char, string> make_map(string text)
{
    map<char, string> codes;
    vector<let *> counts;

    string set_text = "";
    for (int i = 0; i < text.length(); ++i)
    {
        if (count(set_text.begin(), set_text.end(), text[i]) == 0)
        {
            set_text += text[i];
            codes[text[i]] = "";
        }
    }

    for (int i = 0; i < set_text.length(); ++i)
    {
        counts.push_back(new let(set_text[i], count(text.begin(), text.end(), set_text[i])));
    }

    sort(counts.begin(), counts.end(), compare_lets);

    int sm[counts.size() + 1];
    sm[0] = 0;
    for (int i = 0; i < counts.size(); ++i)
    {
        sm[i + 1] = sm[i] + counts[i]->cnt;
    }

    int st = 0;
    int fn = counts.size() - 1;
    char r = '0';
    int ed = 0;

    rec(st, fn, sm, codes, counts);

    return codes;
}

string code(string text, map<char, string> codes)
{
    string s = "";
    for (int i = 0; i < text.length(); ++i)
    {
        s += codes[text[i]];
    }
    return s;
}

string decode(string text, map<char, string> codes)
{
    string s = "";
    string buffer = "";
    for (int i = 0; i < text.length(); ++i)
    {
        buffer += text[i];
        for (auto &[lt, code] : codes)
        {
            if (code == buffer)
            {
                s += lt;
                buffer = "";
                break;
            }
        }
    }
    return s;
}

struct haf
{
    char lt;
    char code;
    int cnt;
    haf *left;
    haf *right;
    haf(char lt, int cnt, haf *left, haf *right, char code)
    {
        this->lt = lt;
        if (left && right)
        {
            this->cnt = left->cnt + right->cnt;
        }
        else
        {
            this->cnt = cnt;
        }
        this->left = left;
        this->right = right;
        this->code = code;
    }
    char find(string code, int ind = 0)
    {
        if (!this->left && !this->right)
        {
            if (code.length() == ind)
            {
                return this->lt;
            }
            else
            {
                return '@';
            }
        }

        if (ind >= code.length())
        {
            return '@';
        }

        if (code[ind] == '0')
        {
            return this->left->find(code, ind + 1);
        }
        return this->right->find(code, ind + 1);
    }

    string get_code(char lt) {
        if (!this->left && !this->right) {
            if (this->lt == lt) {
                return string(1, this->code);
            }
            else {
                return "";
            }
        }

        string s = this->left->get_code(lt) + this->right->get_code(lt);
        if (s != "" && this->code != '@') {
            return this->code + s;
        }
        return s;
    }
};

bool compare_hafs(const haf *pr1, const haf *pr2)
{
    return pr1->cnt < pr2->cnt;
}

haf *make_haf(string text)
{
    vector<haf *> cnts;

    string set_text = "";
    for (int i = 0; i < text.length(); ++i)
    {
        if (count(set_text.begin(), set_text.end(), text[i]) == 0)
        {
            set_text += text[i];
        }
    }

    for (int i = 0; i < set_text.length(); ++i)
    {
        cnts.push_back(new haf(set_text[i], count(text.begin(), text.end(), set_text[i]), nullptr, nullptr, '@'));
    }
    haf *ptr;
    while (cnts.size() > 1)
    {
        sort(cnts.begin(), cnts.end(), compare_hafs);
        cnts[0]->code = '0';
        cnts[1]->code = '1';
        ptr = new haf('@', 0, cnts[0], cnts[1], '@');
        cnts.push_back(ptr);
        cnts.erase(cnts.begin());
        cnts.erase(cnts.begin());
    }
    ptr = cnts[0];
    return ptr;
}

string code_h(string text, haf* codes)
{
    string s = "";
    for (int i = 0; i < text.length(); ++i)
    {
        s += codes->get_code(text[i]);
    }
    return s;
}

string decode_h(string text, haf* codes)
{
    string s = "";
    string buffer = "";
    char lt = '@';
    for (int i = 0; i < text.length(); ++i)
    {
        buffer += text[i];
        lt = codes->find(buffer);
        if (lt != '@') {
            s += lt;
            buffer = "";
        }
    }
    return s;
}

int main()
{
    string s = "По-турецки говорили. Чяби, чяряби Чяряби, чяби-чяби. Мы набрали в рот воды.";
    map<char, string> codes = make_map(s);
    string coded_s = code(s, codes);
    string decoded_s = decode(coded_s, codes);
    cout << "Кодирование методом Шеннона-Фано:" << endl;
    cout << "Исходная строка:" << endl
         << "Размер в битах: " << s.length() * 8 << endl
         << s << endl
         << endl
         << "Закодированная строка:" << endl
         << "Размер в битах: " << coded_s.length() << endl
         << coded_s << endl
         << endl
         << "Раскодированная строка:" << endl
         << decoded_s << endl
         << endl
         << endl;

    s = "Данов Арсений Иванович";
    haf *codes_h = make_haf(s);
    coded_s = code_h(s, codes_h);
    decoded_s = decode_h(coded_s, codes_h);
    cout << "Кодирование методом Хаффмана:" << endl;
    cout << "Исходная строка:" << endl
         << "Размер в битах: " << s.length() * 8 << endl
         << s << endl
         << endl
         << "Закодированная строка:" << endl
         << "Размер в битах: " << coded_s.length() << endl
         << coded_s << endl
         << endl
         << "Раскодированная строка:" << endl
         << decoded_s << endl
         << endl
         << endl;
    return 0;
}