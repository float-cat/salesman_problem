#ifndef ANTSMATRIX_HPP
#define ANTSMATRIX_HPP

#include "waysmatrix.hpp"
#include <cmath>

using namespace std;

/* Константы настройки муравьиного алгоритма */
/* Коэффициент затухания феромонов */
#define CONST_P     (0.05f)
/* Коэффициент жадности алгоритма */
#define CONST_ALPHA (1.0f)
/* Коэффициент стадности алгоритма */
#define CONST_BETA  (1.0f)
/* Количество итераций алгоритма */
#define NUMBER_OF_ITERATION (50)

/* Данные для перехода */
struct AntsData
{
    float probability;
    float pheromones;
    float base;
    bool uses;
};

class AntsMatrix : WaysMatrix
{
 private:
    /* Лучший путь по мнению алгоритма */
    vector<unsigned int> goodway;
    /* Массив отмеченных точек для обхода пути */
    vector<bool> selected;
    /* Матрица данных о переходах */
    vector<vector<struct AntsData>> antsdata;
    void CalcProbability(void);
    /* Выберет случайный путь в зависимости от
        распределения вероятностей */
    unsigned int SelectRandomWay(unsigned int x);
    void UpdatePheromones(void);
    void NextIteration(void);
    void ExecAllIteration(unsigned int number);
    /* Выбирает начальную точку по матрице
        расстояний */
    unsigned int GetStartPosition(void);
 public:
    AntsMatrix(string fname);
    /* Выполняет поиск пути муравьиным алгоритмом */
    vector<unsigned int>& GetGoodWay(void);
};

#endif /* ANTSMATRIX_HPP */
