#include <iostream>
#include <vector>
#include "matrix.h"
/*
class eigen
{
public:
    std::pair<std::vector<double>, Matrix> eigensystem(Matrix *m);
    Matrix identity_matrix(int dimension);
    std::pair<std::vector<double>, Matrix>sort_by_eigenvalues(std::pair<std::vector<double>, Matrix> system);
};
*/
Matrix identity_matrix(int dimension);
std::pair<std::vector<double>, Matrix> eigensystem(Matrix *m);
std::pair<std::vector<double>, Matrix>sort_by_eigenvalues(std::pair<std::vector<double>, Matrix> system);
