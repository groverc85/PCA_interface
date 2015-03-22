#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <limits.h>
#include <iomanip>
#include <float.h>
#include "eigen.h"
#include "config.h"

using namespace std;
class test
{
public:
    int test_image(string filename);
private:
    std::vector<double> read_pgm(std::ifstream& file);
    std::vector< std::vector<double> > read_training_data() ;
    int recognize(Matrix X, Matrix B, Matrix U, Matrix W) ;
};

#endif // TEST_H
