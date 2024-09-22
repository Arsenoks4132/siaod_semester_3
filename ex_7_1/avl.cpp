#include "avl.h"

using namespace std;

avl::avl(double value)
{
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
}

void avl::preorder()
{
    cout << this->value << " ";
    if (this->left)
    {
        this->left->preorder();
    }
    if (this->right)
    {
        this->right->preorder();
    }
}

void avl::inorder()
{

    if (this->left)
    {
        this->left->inorder();
    }
    cout << this->value << " ";
    if (this->right)
    {
        this->right->inorder();
    }
}

void avl::postorder()
{

    if (this->left)
    {
        this->left->postorder();
    }
    if (this->right)
    {
        this->right->postorder();
    }
    cout << this->value << " ";
}

void avl::breadth_first()
{
    queue<avl *> q;
    q.push(this);
    while (!q.empty())
    {
        avl *cur = q.front();
        q.pop();
        cout << cur->value << " ";
        if (cur->left)
        {
            q.push(cur->left);
        }
        if (cur->right)
        {
            q.push(cur->right);
        }
    }
}

double avl::leaves_sum()
{
    if (!this->left && !this->right)
    {
        return this->value;
    }
    double sum = 0;
    if (this->left)
    {
        sum += this->left->leaves_sum();
    }
    if (this->right)
    {
        sum += this->right->leaves_sum();
    }
    return sum;
}

double avl::avg()
{
    return this->sum() / this->count();
}

double avl::sum()
{
    int sum = this->value;
    if (this->left)
    {
        sum += this->left->sum();
    }
    if (this->right)
    {
        sum += this->right->sum();
    }
    return sum;
}

int avl::count()
{
    int sum = 1;
    if (this->left)
    {
        sum += this->left->count();
    }
    if (this->right)
    {
        sum += this->right->count();
    }
    return sum;
}

int avl::find_length(double value) {
    if (this->value == value) {
        return 0;
    }
    int mn = 1000;
    int x;
    if (this->left) {
        x = this->left->find_length(value);
        mn = x < mn ? x : mn;
    }
    if (this->right) {
        x = this->right->find_length(value);
        mn = x < mn ? x : mn;
    }
    return mn + 1;
}

int avl::find_height() {
    if (!this->left && !this->right) {
        return 0;
    }
    int mx = -1;
    int x;
    if (this->left) {
        x = this->left->find_height();
        mx = x > mx ? x : mx;
    }
    if (this->right) {
        x = this->right->find_height();
        mx = x > mx ? x : mx;
    }
    return mx + 1;
}


void avl::show_tree(avl* root) {
    cout << string((root->find_length(this->value)) * 4, ' ') << this->value << '\n';
    if (this->left) {
        this->left->show_tree(root);
    }
    if (this->right) {
        this->right->show_tree(root);
    }
}