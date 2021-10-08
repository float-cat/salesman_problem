#ifndef COMBINATOR_CPP
#define COMBINATOR_CPP

#include "combinator.hpp"

Combinator::Combinator(unsigned int n)
{
    length = n;
    /* Инициализируем комбинтор
        последовательностью 0..n-1 */
    for(unsigned int i=0; i<n; i++)
        array.push_back(i);
}

unsigned int Combinator::GetLength(void)
{
    return length;
}

vector<unsigned int>& Combinator::GetArray(void)
{
    return array;
}

/* Основано на алгоритме Нарайаны */
bool Combinator::NextWay(void)
{
    auto it = array.end()-2;
    unsigned int tmp;
    /* Ищем наибольший i, где a[i]<a[i+1] */
    for (; it >= array.begin(); it--)
    {
        if((*it)<(*(it+1)))
            break;
    }
    /* Если дошли до конца - перестановок
        больше нет */
    if(it < array.begin())
        return false;
    auto it2 = array.end()-1;
    /* Ищем j>i такой, что a[j]>a[i] */
    while(*it >= *it2) it2--;
    /* Меняем местами a[i] и a[j] */
    tmp = *it;
    *it = *it2;
    *it2 = tmp;
    /* Переворачиваем последовательность от
        j+1 до конца */
    reverse(it+1, array.end());
    return true;
}

#endif /* COMBINATOR_CPP */
