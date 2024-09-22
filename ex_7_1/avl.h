#ifndef __AVL__H
#define __AVL__H

#include <iostream>
#include <queue>

struct avl
{
    double value;
    avl *left;
    avl *right;
    int height;

    avl(double value);
    void preorder();
    void inorder();
    void postorder();
    void breadth_first();
    double leaves_sum();
    double avg();
    int find_length(double value);
    int find_height();
    void show_tree(avl* root);

private:
    int count();
    double sum();
};

#endif