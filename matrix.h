#ifndef MATRIX_H
#define MATRIX_H

#include <QDebug>
#include "setting.h"

using namespace std;


template <typename T, size_t W>
class Matrix
{
public:
    void set(T p, int s){
        at(s) = p;
    };
    T& at(int s){
        return store.at(s);
    };

private:
    array<T, W*W> store;
};

#endif // MATRIX_H
