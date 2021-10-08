#ifndef SALESMAN_CPP
#define SALESMAN_CPP

#include "salesman.hpp"

Salesman::Salesman(string fname)
{
    if((ways = new WaysMatrix(fname)) == NULL)
        throw "Alloc memory error!";
    /* Инвертируем число 0, т.к. у нас
        беззнаковое целое, то получим
        максимальное возможное число */
    bestdistance = ~0;
}

Salesman::~Salesman(void)
{
    /* Очищаем память из-под матрицы расстояний */
    if(ways != NULL)
        delete ways;
}

unsigned int Salesman::CalcAllDistance(vector<unsigned int>& way)
{
    unsigned int result = 0;
    /* Складываем все расстояния между точками пути */
    for(auto it = way.begin(); it != way.end()-1; it++)
        result += ways->GetWay(*it, *(it+1));
    return result;
}

vector<unsigned int>& Salesman::CalcNPComplete(void)
{
    unsigned int tmp;
    Combinator combinator(ways->GetSize());
    do
    {
        auto& way = combinator.GetArray();
        tmp = CalcAllDistance(way);
        if(bestdistance > tmp)
        {
            bestdistance = tmp;
            bestway = way;
        }
    }
    while(combinator.NextWay());
    return bestway;
}

#endif /* SALESMAN_CPP */
