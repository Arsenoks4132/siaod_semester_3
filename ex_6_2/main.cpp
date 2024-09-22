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

int kmp_search(string s, string find)
{
    int x = 0;
    int ln = find.length();
    s = find + "@" + s;
    int n = s.length();
    vector<int> p(n, 0);
    for (int i = 1; i < n; ++i)
    {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0)
        {
            ++x;
            cur = p[cur - 1];
        }
        if (s[i] == s[cur])
        {
            ++x;
            p[i] = cur + 1;
        }
        if (p[i] == ln)
        {
            ++x;
            return x;
        }
    }
    return x;
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
    // string text = "it. is. a \"new\" text: i, need? to listen it";
    // string text = "Once upon a time, in a small village, there lived a young girl named Clara; she often wondered about the mysteries of the world around her: \"What lies beyond the mountains?\" she would ask herself, gazing at the towering peaks that seemed to touch the sky. Every day, she explored the fields, her curious spirit leading her to discover hidden wonders: colorful flowers, fluttering butterflies, and sparkling streams; but despite all her adventures, she felt a longing, an urge to know more—was there something magical waiting for her? One evening, as the sun dipped below the horizon, painting the sky with hues of orange and purple, Clara encountered an old, wise man sitting beneath an ancient tree. With a twinkle in his eye, he said, \"You seek adventure, don\'t you?\" Surprised, she nodded eagerly; indeed, she yearned for excitement! He continued, \"To find what you seek, you must follow your heart; it will guide you to places you\'ve only dreamed of!\" Feeling a thrill of anticipation, Clara asked, \"Where should I begin?\" The man smiled knowingly and replied, \"Look to the stars; they hold the secrets of the universe!\" Inspired, she rushed home that night, filled with questions and dreams—could she really uncover the secrets of the cosmos? The very idea sent shivers down her spine; she decided that tomorrow would be the first day of her grand journey—a journey filled with exploration, learning, and perhaps magic! As she lay in bed, her mind danced with possibilities:\"What if I meet magical creatures? Or discover hidden treasures?\" The stars twinkled brightly outside her window, as if they were whispering to her, encouraging her\" adventurous spirit; with a heart full of hope, Clara fell asleep, ready to embrace whatever awaited her with open arms.";
    // cout << "Исходный текст: " << endl
    //      << text;
    // string ne = replace(text);
    // cout << endl
    //      << "Обработанный текст: " << endl
    //      << ne << endl;

    string ne_text = "xqjznbvwmotysgflraucpkehdi";

    cout << endl
         << "Исходный текст:" << endl
         << ne_text.length() << endl
         << ":" << endl;
    // auto v = prefix_function(ne_text);
    // show(v);

    // cout << kmp_search("i want to eat", "eat");

    return 0;
}
