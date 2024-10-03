#include <iostream>
#include <vector>

using namespace std;

void add_space(string &text, int count)
{
    int ln = text.length();
    if (ln == 0)
    {
        return;
    }
    if (ln == 1)
    {
        text += string(count, ' ');
        return;
    }
    if (text[ln - 1] == ' ')
    {
        if (count == 2 && text[ln - 2] != ' ')
        {
            text += " ";
        }
    }
    else
    {
        text += string(count, ' ');
    }
}

string replace(string text)
{
    string new_str = "";
    string end = "!?.\n";
    string between = ",;:-\"()/\\ «»—[]";
    for (int i = 0; i < text.length(); ++i)
    {
        if (end.find(text[i]) != string::npos)
        {
            add_space(new_str, 2);
        }
        else if (between.find(text[i]) != string::npos)
        {
            add_space(new_str, 1);
        }
        else
        {
            new_str += text[i];
        }
    }
    return new_str;
}

vector<int> prefix_function(string s)
{
    int n = s.length();
    vector<int> p(n, 0);
    for (int i = 1; i < n; ++i)
    {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0)
        {
            cur = p[cur - 1];
        }
        if (s[i] == s[cur])
        {
            p[i] = cur + 1;
        }
    }
    return p;
}

int prefix_function_cnt(string s)
{
    int n = s.length();
    vector<int> p(n, 0);
    int cnt = 2;
    for (int i = 1; i < n; ++i)
    {
        ++cnt;
        int cur = p[i - 1];
        ++cnt;
        while (s[i] != s[cur] && cur > 0)
        {
            cur = p[cur - 1];
            ++cnt;
        }
        ++cnt;
        if (s[i] == s[cur])
        {
            p[i] = cur + 1;
            ++cnt;
        }
        ++cnt;
    }
    cnt += 2;
    return cnt;
}

int kmp_search(string s, string find)
{
    int ind = -1;
    int ln = find.length();
    s = find + "@" + s;
    int n = s.length();
    vector<int> p(n, 0);
    for (int i = 1; i < n; ++i)
    {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0)
        {
            cur = p[cur - 1];
        }
        if (s[i] == s[cur])
        {
            p[i] = cur + 1;
        }
        if (p[i] == ln)
        {
            return (i - 2 * ln);
        }
    }
    return -1;
}

int kmp_search_cnt(string s, string find)
{
    int ln = find.length();
    s = find + "@" + s;
    int n = s.length();
    vector<int> p(n, 0);
    int cnt = 4;
    for (int i = 1; i < n; ++i)
    {
        ++cnt;
        int cur = p[i - 1];
        ++cnt;
        while (s[i] != s[cur] && cur > 0)
        {
            cur = p[cur - 1];
            ++cnt;
        }
        ++cnt;
        if (s[i] == s[cur])
        {
            p[i] = cur + 1;
            ++cnt;
        }
        ++cnt;
        if (p[i] == ln)
        {
            ++cnt;
            return cnt;
        }
    }
    ++cnt;
    return cnt;
}

void show(vector<int> v)
{
    cout << "[ ";
    if (v.size() > 0)
    {
        cout << v[0];
    }
    for (int i = 1; i < v.size(); ++i)
    {
        cout << ", " << v[i];
    }
    cout << " ]";
}

int main()
{
    string text = "Once upon a time, in a small village, there lived a young girl named Clara; she often wondered about the mysteries of the world around her: \"What lies beyond the mountains?\" she would ask herself, gazing at the towering peaks that seemed to touch the sky. Every day, she explored the fields, her curious spirit leading her to discover hidden wonders: colorful flowers, fluttering butterflies, and sparkling streams; but despite all her adventures, she felt a longing, an urge to know more—was there something magical waiting for her? One evening, as the sun dipped below the horizon";

    cout << endl
         << "Исходный текст:\n" << text << endl
         << "Измененный текст:\n" << replace(text) << endl;

    cout << endl
         << endl;
    string ne_text = "I want to fly in the space. It is my dream!";
    int ind = kmp_search(ne_text, "space");
    cout << endl
         << "Исходный текст:\n" << ne_text << endl
         << "Найденный индекс: " << ind;

    return 0;
}
