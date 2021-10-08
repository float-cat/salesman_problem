#ifndef SALESMAN_HPP
#define SALESMAN_HPP

#include <cstddef>
#include <iostream>
#include <vector>
#include "combinator.hpp"
#include "waysmatrix.hpp"

using namespace std;

class Salesman
{
 private:
    WaysMatrix *ways;
    unsigned int bestdistance;
    vector<unsigned int> bestway;
    unsigned int CalcAllDistance(vector<unsigned int>& way);
 public:
    Salesman(string fname);
    ~Salesman(void);
    vector<unsigned int>& CalcNPComplete(void);
};

#endif /* SALESMAN_HPP */
