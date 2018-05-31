//
// Created by akshay on 7/2/18.
//

#ifndef ALGORITHMS_STRASSEN_MULTIPLICATION_H
#define ALGORITHMS_STRASSEN_MULTIPLICATION_H

/*
    rs = row start
    re = row end
    cs = column start
    ce = column end
    a[][] = a 2d matrix elements
*/

typedef struct _m {
    int n;
    int rs;
    int re;
    int cs;
    int ce;

    int a[100]; // N Max 10
}m;

m multiply(m m1, m m2);
void display(m);

#endif //ALGORITHMS_STRASSEN_MULTIPLICATION_H
