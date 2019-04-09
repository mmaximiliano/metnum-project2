#ifndef __LINEAL_H__
#define __LINEAL_H__

#include <vector>

double norma1(const std::vector<double> &v);

double norma2(const std::vector<double> &v);

std::vector<double> normalizar(const std::vector<double> &v);

double operator*(const std::vector<double> &v1, const std::vector<double> &v2);

std::vector<double> operator*(const std::vector<std::vector<double> > &M, const std::vector<double> &v);

#endif
