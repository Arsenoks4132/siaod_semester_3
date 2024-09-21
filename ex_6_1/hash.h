#ifndef __HASH__H
#define __HASH__H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "unispec.h"

class dict
{
private:
    std::vector<unispec *> values;
    int count;

public:
    dict();
    void insert(unispec *el);
    void del(std::string code);
    unispec *find(std::string code);
    void show();
    int format(std::string code, int dl);
    void rehash();
};

#endif
