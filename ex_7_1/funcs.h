#ifndef __FUNCS__H
#define __FUNCS__H

#include "avl.h"

int height(avl *p);

int bfactor(avl *p);

void fixheight(avl *p);

avl *rotateright(avl *p);

avl *rotateleft(avl *q);

avl *balance(avl *p);

avl *insert(avl *p, double k);

#endif