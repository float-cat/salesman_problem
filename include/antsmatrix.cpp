#ifndef ANTSMATRIX_CPP
#define ANTSMATRIX_CPP

#include "antsmatrix.hpp"

void AntsMatrix::CalcProbability(void)
{
    float summ;
    for(unsigned int i = 0; i < GetSize(); i++)
    {
        summ = 0.0f;
        /* Считаем сумму произведения феромонов на
            базовую вероятность */
        for(unsigned int j = 0; j < GetSize(); j++)
        {
            summ += pow(antsdata[i][j].pheromones, CONST_ALPHA) *
                pow(antsdata[i][j].base, CONST_BETA);
        }
        /* Подсчитываем вероятность переходов */
        for(unsigned int j = 0; j < GetSize(); j++)
        {
            if(i!=j)
            {
                antsdata[i][j].probability =
                    pow(antsdata[i][j].pheromones, CONST_ALPHA) *
                    pow(antsdata[i][j].base, CONST_BETA) /
                    summ;
            }
        }
    }
}

/* Выберет случайный путь в зависимости от
    распределения вероятностей */
unsigned int AntsMatrix::SelectRandomWay(unsigned int x)
{
    float prob = 0.0f;
    /* Получаем случайную величину от 0 до 1 */
    float r = static_cast <float> (rand()) /
        static_cast <float> (RAND_MAX);
    /* Смотрим в какую вероятность попали */
    for(unsigned int i = 0; i < GetSize(); i++)
    {
        /* Получаем следующую границу вероятности */
        prob += antsdata[x][i].probability;
        /* Если в границах вероятностей, то нашли
            случайный переход */
        if(r < prob)
            return i;
    }
    return GetSize() - 1;
}

void AntsMatrix::UpdatePheromones(void)
{
    for(auto it = antsdata.begin(); it != antsdata.end(); it++)        
        for(auto it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            /* Феромоны затухают */
            (*it2).pheromones = (1-CONST_P)*(*it2).pheromones;
            /* Если переход был выбран */
            if((*it2).uses)
            {
                /* Приращиваем феромоны */
                (*it2).pheromones += (*it2).base;
                /* Сбрасываем флаг использования перехода */
                (*it2).uses = false;
            }
        }
}

void AntsMatrix::NextIteration(void)
{
    unsigned int j;
    /* Для каждого муравья */
    for(unsigned int i = 0; i < GetSize(); i++)
    {
        /* Выбираем случайно переход, опираясь на
            массив вероятностей */
        j = SelectRandomWay(i);
        /* Помечаем выбранный переход */
        antsdata[i][j].uses = true;
    }
    /* Обновляем феромоны */
    UpdatePheromones();
    /* Пересчитываем вероятности */
    CalcProbability();
}

void AntsMatrix::ExecAllIteration(unsigned int number)
{
    /* Выполняем указанное количество итераций */
    while(number-- > 0)
        NextIteration();
}

unsigned int AntsMatrix::GetStartPosition(void)
{
    /* Инициализируем начальные данные */
    unsigned int min = GetWay(0, 1);
    unsigned int x = 0;
    for(unsigned int i = 0; i < GetSize(); i++)
        for(unsigned int j = 0; j < GetSize(); j++)
        {
            /* Если нашли меньше минимума, то новый
                минимум */
            if(i!=j && min > GetWay(i, j))
            {
                min = GetWay(i, j);
                x = i;
                selected[i] = true;
            }
            /* Так же, но только для обратного
                перехода, если путь из А в B
                отличается от пути из B в A */
            if(i!=j && min > GetWay(j, i))
            {
                min = GetWay(j, i);
                x = j;
                selected[i] = true;
            }
        }
    return x;
}

AntsMatrix::AntsMatrix(string fname)
    : WaysMatrix(fname)
{
    /* Временные переменные для формирования
        двухмерного массива данных */
    struct AntsData tmp;
    vector<struct AntsData> tmp2;
    /* Инициализируем начальный рандом от времени */
    srand(time(0));
    /* Устанавливаем начальные значения */
    for(unsigned int i = 0; i < GetSize(); i++)
    {
        antsdata.push_back(tmp2);
        for(unsigned int j = 0; j < GetSize(); j++)
        {
            tmp.probability = 0.0f;
            /* Исключаем переходы к самому себе */
            if(i!=j)
            {
                /* Начальный уровень феромонов
                    одинаковый для всех */
                tmp.pheromones = 1.0f;
                tmp.base = 1.0f / GetWay(i, j);
            }
            else
            {
                /* Инициализируем нулями переходы
                    из А в А */
                tmp.pheromones = 0.0f;
                tmp.base = 0.0f;
            }
            tmp.uses = false;
            antsdata[i].push_back(tmp);
        }
    }
    /* Считаем начальную вероятность */
    CalcProbability();
    /* Заполняем массив флагов использования */
    for(unsigned int i = 0; i < GetSize(); i++)
        selected.push_back(false);
}

vector<unsigned int>& AntsMatrix::GetGoodWay(void)
{
    unsigned int max;
    float maxpheromones;
    unsigned int pos;
    goodway.clear();
    /* Выполняем все итерации алгоритма */
    ExecAllIteration(NUMBER_OF_ITERATION);
    /* Получаем номер стартовой точки */
    pos = GetStartPosition();
    goodway.push_back(pos);
    /* Выполняем обход наиболее удачных переходов */
    for(unsigned int i = 1; i < GetSize(); i++)
    {
        maxpheromones = 0.0f;
        for(unsigned int j = 1; j < GetSize(); j++)
        {
            /* Если нашли путь с большим числом феромонов */
            if(pos!=j && !selected[j] &&
                antsdata[pos][j].pheromones > maxpheromones)
            {
                maxpheromones = antsdata[pos][j].pheromones;
                max = j;
            } 
        }
        /* Помечаем найденный путь флагом прохождения
            и добавляем точку к общему пути */
        selected[max] = true;
        goodway.push_back(max);
    }
    return goodway;
}

#endif /* ANTSMATRIX_CPP */
