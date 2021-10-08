#ifndef COMBINATOR_HPP
#define COMBINATOR_HPP

#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Комбинатор для того, чтобы перебрать
    все варианты путей в матрице расстояний
    основан на алгоритме Нарайаны */
class Combinator
{
 private:
    unsigned int length;
    vector<unsigned int> array;
 public:
    Combinator(unsigned int n);
    unsigned int GetLength(void);
    vector<unsigned int>& GetArray(void);
    bool NextWay(void);
};

#endif /* COMBINATOR_HPP */
