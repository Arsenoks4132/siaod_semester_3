#include "funcs.h"

int height(avl *p)
{
    return p ? p->height : 0;
}

int bfactor(avl *p)
{
    return height(p->right) - height(p->left);
}

void fixheight(avl *p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

avl *rotateright(avl *p) // правый поворот вокруг p
{
    avl *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

avl *rotateleft(avl *q) // левый поворот вокруг q
{
    avl *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

avl *balance(avl *p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

avl *insert(avl *p, double k) // вставка ключа k в дерево с корнем p
{
    if (!p)
        return new avl(k);
    if (k < p->value)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}