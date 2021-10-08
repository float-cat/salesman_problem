#include <cstdlib>
#include <iostream>
#include "include/salesman.hpp"
#include "include/antsmatrix.hpp"

using namespace std;

/* Список алгоритмов */
enum
{
    np_complete,
    np_partial
};

int main(int argc, char **argv)
{
    /* Отличный путь по мнению программы */
    vector<unsigned int> goodway;
    /* Для выбора алгоритма */
    unsigned int alg;
    try
    {
        /* Если только параметр имя файла, то
            по умолчанию муравьиный алгоритм */
        if(argc == 3 && string(argv[1]) == "-f")
        {
            alg = np_partial;
        }
        /* Если указан и -m, то определяем алгоритм */
        else if(argc == 5 && string(argv[1]) == "-f" &&
            string(argv[3]) == "-m" &&
            (
                string(argv[4]) == "np_complete" ||
                string(argv[4]) == "np_partial"
            ))
        {
            if(string(argv[4]) == "np_complete")
                alg = np_complete;
            else
                alg = np_partial;
        }
        /* Все остальные варианты, включая атрибут -h */
        else
        {
            cout << "USING: -f <file_name> -m <method>" <<
                endl << "Methods: np_complete - brut force, " <<
                    "np_partial - ant colony alghoritm" << endl;
            return EXIT_SUCCESS;
        }
        if(alg == np_complete)
        {
            /* Выполняем алгоритм полного перебора */
            Salesman salesman(argv[2]);
            goodway = salesman.CalcNPComplete();
        }
        else
        {
            /* Выполняем муравьиный алгоритм */
            AntsMatrix ants(argv[2]);
            goodway = ants.GetGoodWay();
        }
        /* Распечатываем массив */
        for(auto it = goodway.begin(); it != goodway.end(); it++)
            cout << (*it) << " ";
        cout << endl;
    }
    catch (const char &e)
    {
        cerr << e << endl;
        return -1;
    }
    return EXIT_SUCCESS;
}
