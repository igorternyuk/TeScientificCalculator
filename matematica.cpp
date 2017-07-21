#include <math.h>
#include <complex.h>
#include <vector>
#include <stdexcept>
#include "matrix.h"
double factorial(double n)
{
    if (floor(n) == 0 || floor(n) == 1) return 1;
    else return n * factorial(n - 1);
}
int signum(double value)
{
    return value >= 0 ? 1: -1;
}
double polynomLagrange(std::vector<std::pair<double, double> > pointsTable, double value)
{
    double summa = 0, num, den, omega;                       // L = w1 * y1 + w2 * y2 + ... + wn * yn
    for(unsigned int i = 0; i < pointsTable.size(); ++i)
    {
        omega = 1;
        num = 1;
        den = 1;
        for(unsigned int j = 0; j < pointsTable.size(); ++j)
        {
            if (i != j)
            {
              num *= (value - pointsTable[j].first);
              den *= pointsTable[i].first - pointsTable[j].first;
            }
        }
        omega = num / den;
        summa += omega * pointsTable[i].second;
    }
    return summa;
}
double integralTablLeftHandRect(std::vector<std::pair<double, double>> integrandTable)
{
    if(!integrandTable.empty())
    {
        int n = integrandTable.size() - 1;
        double currentStep, Integral = 0;
        for(int i = 0; i < n; ++i)
        {
           currentStep = integrandTable[i + 1].first - integrandTable[i].first;
           Integral += integrandTable[i].second * currentStep;
        }
        return Integral;
    }else return 0.0;
}
double integralTablRightHandRect(std::vector<std::pair<double, double>> integrandTable)
{
    if(!integrandTable.empty())
    {
        int n = integrandTable.size() - 1;
        double currentStep, Integral = 0;
        for(int i = 1; i <= n; ++i)
        {
           currentStep = integrandTable[i].first - integrandTable[i - 1].first;
           Integral += integrandTable[i].second * currentStep;
        }
        return Integral;
    }else return 0.0;
}
double integralTablTrapezoids(std::vector<std::pair<double, double>> integrandTable)
{
    if(!integrandTable.empty())
    {
        int n = integrandTable.size() - 1;
        double currentStep, Integral = 0;
        for(int i = 1; i <= n; ++i)
        {
           currentStep = integrandTable[i].first - integrandTable[i - 1].first;
           Integral += (integrandTable[i].second + integrandTable[i - 1].second) * currentStep;
        }
        Integral /= 2;
        return Integral;
    }else return 0.0;
}
double integralTablSimpson(std::vector<std::pair<double, double> > integrandTable)
{
    if(!integrandTable.empty())
    {
        double h1, h2; // steps
        double Integral = 0;
        int n = integrandTable.size() - 1;
        if(n % 2 != 0) throw std::runtime_error("The number of intervals must be even!");
        for(int i = 0; i <= n - 2; i += 2)
            {
                h1 = integrandTable[i + 1].first - integrandTable[i].first;
                h2 = integrandTable[i + 2].first - integrandTable[i + 1].first;
                Integral += ((h1 + h2) / (6 * h1 * h2)) *
                (h2 * (2 * h1 - h2) * integrandTable[i].second + pow(h1 + h2, 2) * integrandTable[i + 1].second +
                h1 * (2 * h2 - h1) * integrandTable[i + 2].second);
            }
        return Integral;
    }else return 0.0;

}
double integralTablPolLagr(std::vector<std::pair<double, double> > integrandTable,
                           double a, double b)
{
    if(!integrandTable.empty())
    {
        int n = integrandTable.size() - 1;
        Matrix<double> mtrX(n, n, 0.0);
        Matrix<double> mtrI(n, 1, 0.0);
        //Заполняем матрицы
        for(int i = 0; i < mtrX.getRowCount(); ++i)
        {
            mtrI.setValueAt(i, 0, (pow(b, i + 1) - pow(a, i + 1)) / (i + 1));
            for(int j = 0; j < mtrX.getColumnCount(); ++j)
            {
                mtrX.setValueAt(i, j, pow(integrandTable[j].first, i));
            }
        }
        Matrix<double> mtrInv = mtrX.inverse();
        Matrix<double> mtrA = mtrInv * mtrI;
        double Integral = 0;
        for(int i = 0; i <= n; ++i)
        {
           Integral += mtrA.getValueAt(i,0) * integrandTable[i].second;
        }
        return Integral;
    }else return 0.0;
}
std::vector<std::complex<double>> solveCubicEquation(double a, double b, double c, double d)
{
    double p = c / a - pow(b, 2) / (3 * pow(a, 2));
    double q = (2 * pow(b, 3) - 9 * a * b * c + 27 * a * a * d) / pow(3 * a, 3);
    std::complex<double> alpha, beta;
    std::complex<double> Q = pow(p / 3, 3) + pow(q / 2, 2);
    if(Q.real() >= 0)
    {
        alpha = signum(-0.5 * q + sqrt(Q.real())) * pow(fabs(-0.5 * q + sqrt(Q.real())), 1 / 3.0);
        beta = signum(-0.5 * q - sqrt(Q.real())) * pow(fabs(-0.5 * q - sqrt(Q.real())), 1 / 3.0);
    }else
    {
        std::complex<double> Zalpha = -0.5 * q + sqrt(Q);
        std::complex<double> Zbeta = -0.5 * q - sqrt(Q);
        alpha = pow(Zalpha, 1 / 3.0);
        beta = pow(Zbeta , 1 / 3.0);
    }
    std::complex<double> y1 = alpha + beta;
    std::complex<double> unit(-1,0);
    std::complex<double> j = sqrt(unit);
    std::complex<double> x1 = y1 - b / (3 * a);
    std::complex<double> x2 = -0.5 * (alpha + beta) + 0.5 * (alpha - beta) * sqrt(3.0) * j - b / (3 * a);
    std::complex<double> x3 = -0.5 * (alpha + beta) - 0.5 * (alpha - beta) * sqrt(3.0) * j - b / (3 * a);
    std::vector<std::complex<double>> roots;
    roots.push_back(x1);
    roots.push_back(x2);
    roots.push_back(x3);
    return roots;
}
std::vector<std::complex<double>> solveSquareEquation(double a, double b, double c)
{
    std::complex<double> discr(pow(b, 2) - 4 * a * c, 0.0);
    std::complex<double> x1 = (-b + sqrt(discr)) / (2 * a);
    std::complex<double> x2 = (-b - sqrt(discr)) / (2 * a);
    std::vector<std::complex<double>> roots;
    roots.push_back(x1);
    roots.push_back(x2);
    return roots;
}
double tablFuncLeftDer1(std::vector<std::pair<double, double> > pointsTable, double value)
{
    const double deltaArgValue = 0.001;
    double func = polynomLagrange(pointsTable, value);
    double funcMinusDelta = polynomLagrange(pointsTable, value - deltaArgValue);
    double funcMinusTwoDeltas = polynomLagrange(pointsTable, value - 2 * deltaArgValue);
    return (3 * func - 4 * funcMinusDelta + funcMinusTwoDeltas) / (2 * deltaArgValue);
}
double tablFuncRightDer1(std::vector<std::pair<double, double> > pointsTable, double value)
{
   const double deltaArgValue = 0.001;
   double func = polynomLagrange(pointsTable, value);
   double funcPlusDelta = polynomLagrange(pointsTable, value + deltaArgValue);
   double funcPlusTwoDeltas = polynomLagrange(pointsTable, value + 2 * deltaArgValue);
   return (-3 * func + 4 * funcPlusDelta - funcPlusTwoDeltas) / (2 * deltaArgValue);
}
double tablFuncDer1(std::vector<std::pair<double, double> > pointsTable, double value)
{
    const double deltaArgValue = 0.001;
    double funcMinusDelta = polynomLagrange(pointsTable, value - deltaArgValue);
    double funcPlusDelta = polynomLagrange(pointsTable, value + deltaArgValue);
    return (funcPlusDelta - funcMinusDelta) / (2 * deltaArgValue);
}
double tablFuncDer2(std::vector<std::pair<double, double> > pointsTable, double value)
{
    const double deltaArgValue = 0.001;
    double funcPlusDelta = polynomLagrange(pointsTable, value + deltaArgValue);
    double func= polynomLagrange(pointsTable, value);
    double funcMinusDelta = polynomLagrange(pointsTable, value - deltaArgValue);
    return (funcPlusDelta - 2 * func + funcMinusDelta) / pow(deltaArgValue, 2);
}
