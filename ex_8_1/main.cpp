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
    let (char lt, int cnt) {
        this->lt = lt;
        this->cnt = cnt;
    }
};

bool compare_lets(const let *pr1, const let *pr2)
{
    return pr1->cnt > pr2->cnt;
}

map<char, string> make_map(string text)
{
    map<char, string> codes;
    vector<let*> counts;

    string set_text = "";
    for (int i = 0; i < text.length(); ++i) {
        if (count(set_text.begin(), set_text.end(), text[i]) == 0) {
            set_text += text[i];
        }
    }

    for (int i = 0; i < set_text.length(); ++i) {
        counts.push_back(new let(set_text[i], count(text.begin(), text.end(), set_text[i])));
    }

    sort(counts.begin(), counts.end(), compare_lets);

    

    return codes;
}

int main() {
    string s = "abcccccadddaagg";
    make_map(s);
    return 0;
}