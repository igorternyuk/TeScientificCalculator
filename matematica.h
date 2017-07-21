#ifndef MATEMATICA_H
#define MATEMATICA_H
#include <math.h>
#include <vector>
#include <ctime>
#include <complex.h>
double factorial(double n);
int signum(double value);
double integralTablLeftHandRect(std::vector<std::pair<double, double>> integrandTable);
double integralTablRightHandRect(std::vector<std::pair<double, double>> integrandTable);
double integralTablTrapezoids(std::vector<std::pair<double, double>> integrandTable);
double integralTablSimpson(std::vector<std::pair<double, double>> integrandTable);
double integralTablPolLagr(std::vector<std::pair<double, double>> integrandTable,
                           double a, double b);
double polynomLagrange(std::vector<std::pair<double, double>> pointsTable, double value);
double tablFuncLeftDer1(std::vector<std::pair<double, double>> pointsTable, double value);
double tablFuncRightDer1(std::vector<std::pair<double, double>> pointsTable, double value);
double tablFuncDer1(std::vector<std::pair<double, double>> pointsTable, double value);
double tablFuncDer2(std::vector<std::pair<double, double>> pointsTable, double value);
std::vector<std::complex<double>> solveSquareEquation(double a, double b, double c);
std::vector<std::complex<double>> solveCubicEquation(double a, double b, double c, double d);

#endif // MATEMATICA_H
