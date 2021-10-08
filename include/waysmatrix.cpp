#ifndef WAYSMATRIX_CPP
#define WAYSMATRIX_CPP

#include "waysmatrix.hpp"

WaysMatrix::WaysMatrix(string fname)
{
    ReadFromFile(fname);
}

void WaysMatrix::ReadFromFile(string fname)
{
    ifstream in;
    in.open(fname);
    if(!in.is_open())
        throw "File open error!";
    unsigned int tmp;
    /* Для добавления массива в массив массивов */
    vector<unsigned int> tmp2;
    size = 0;
    /* Пропускаем первый ноль */
    in >> tmp;
    if(tmp != 0)
        throw "Invalid distances matrix!";
    /* Пока не встретим ноль - считаем мощность
        2-х мерной матрицы */
    while(!in.eof())
    {
        in >> tmp;
        if(tmp == 0)
            break;
        size++;
    }
    /* Если закончился файл - у нас проблема */
    if(in.eof())
        throw "Invalid distances matrix!";
    /* Встаем в начало файла */
    in.seekg(0, ios_base::beg);
    /* Считываем двухмерную матрицу */
    for(unsigned int i = 0; i < size; i++)
    {
        ways.push_back(tmp2);
        for(unsigned int j = 0; j < size; j++)
        {
            in >> tmp;
            ways[i].push_back(tmp);
        }
    }
    in.close();
}

unsigned int WaysMatrix::GetSize(void)
{
    return size;
}

unsigned int WaysMatrix::GetWay(unsigned int i, unsigned int j)
{
    return ways[i][j];
}

#endif /* WAYSMATRIX_CPP */
