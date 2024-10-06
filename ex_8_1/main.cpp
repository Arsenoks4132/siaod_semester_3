#include <iostream>
#include <string>
#include <vector>

struct let
{
    char let;
    int cnt;
};

bool compare_lets(const let *pr1, const let *pr2)
{
    return pr1->cnt > pr2->cnt;
}

