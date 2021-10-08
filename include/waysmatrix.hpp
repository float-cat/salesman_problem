#ifndef WAYSMATRIX_HPP
#define WAYSMATRIX_HPP

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class WaysMatrix
{
 private:
    unsigned int size;
    vector<vector<unsigned int>> ways;
    void ReadFromFile(string fname);
 public:
    WaysMatrix(string fname);
    unsigned int GetSize(void);
    unsigned int GetWay(unsigned int i, unsigned int j);
};

#endif /* WAYSMATRIX_HPP */
