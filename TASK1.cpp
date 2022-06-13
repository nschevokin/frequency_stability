// TASK1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

void read_data(vector <double> *y)
{
    double num = 0;
    uint32_t M = 0;
    ifstream input_file("PHASE.dat");
    while (!input_file.eof())
    {
        input_file >> num;
        M++;
    }
    input_file.close();
    M--;
    ifstream read_file("PHASE.dat");
    for (uint16_t i = 0; i < M; i++)
    {
        double cnt = 0;
        read_file >> cnt;
        y->push_back(cnt);
    }
    read_file.close();

}

void struct_data(vector <double> y, double *data,uint16_t offs)
{
    for (int i = 0; i < 100; i++)
    {
        data[i] = y[i + offs];
    }
}

void calc_adam(double* data, double* A, double* APh, uint16_t m, uint16_t t)
{
    uint16_t M=100;
    double first = 1 / (6 * pow(m, 2) * pow(t, 2) * (M - 3 * m + 1));
    double sum = 0;
    for (uint16_t j = 1; j <= (M - 3 * m + 1); j++) {
        long double sum_pod = 0;
        for (uint16_t i = j; i < (j + m - 1); i++) {
            sum_pod += data[i + 2 * m] - 2 * data[i + m] + data[i];
        }
        sum += pow(sum_pod, 2);
    }
    *A = first * sum;

    int N = M + 1;
    first = 1 / (6 * pow(t, 2) * (N - 3 * m));
    sum = 0;
    for (int i = 1; i < (M - 3 * m); i++) {
        sum += pow(data[i + 3 * m] - 3 * data[i + 2 * m] + 3 * data[i + m] - data[i], 2);
    }
    *APh= first * sum;
}

void calc_theo(double* data, double* T, uint16_t m, uint16_t t)
{
    uint16_t N = 100;
    double first = 1 / ((N - m) * pow((m * t), 2));
    double sum = 0;
    for (int i = 1; i < N - m; i++)
    {
        for (int sigm = 0; sigm < ((m / 2) - 1); sigm++)
        {
            sum += (1.0 / (((float)m / 2) - sigm) * pow((data[i] - data[i - sigm + (m / 2)]) + (data[i + m] - data[i + sigm + (m / 2)]), 2));
        }
    }
    *T= first * sum;
}

FILE* gp[3];
FILE* output[3];
int main()
{
    gp[0] = _popen("gnuplot -persist", "w");
    gp[1] = _popen("gnuplot -persist", "w");
    gp[2] = _popen("gnuplot -persist", "w");
    fopen_s(&output[0],"Adhamar.dat", "w");
    fopen_s(&output[1], "AdhamarPh.dat", "w");
    fopen_s(&output[2], "Theo.dat", "w");
    double A[10] = { 0 };
    double APh[10] = { 0 };
    double T[10] = { 0 };
    vector <double> y;
    double data[10][100] = { 0 };
    uint16_t ma,mt,ta,tt;

    read_data(&y);

    for (int i = 0; i < 10; i++)
    {
        struct_data(y, data[i], 1+i*100);
    }

    cout << "m(Adhamar) = ";
    cin >> ma;
    cout << "t(Adhamar) = ";
    cin >> ta;
    cout << "m(Theo) = ";
    cin >> mt;
    cout << "t(Theo) = ";
    cin >> tt;

    for (int i = 0; i < 10; i++)
    {
        calc_adam(data[i], A + i, APh + i, ma, ta);
        calc_theo(data[i], T + i, mt, tt);
    }
    for (int i = 0; i < 10; i++)
    {
        fprintf_s(output[0], "%i\t%f\n",i+1,A[i]);
        fprintf_s(output[1], "%i\t%f\n", i+1, APh[i]);
        fprintf_s(output[2], "%i\t%f\n", i+1, T[i]);
    }
    fprintf(gp[0], "plot './Adhamar.dat' with linespoints \n");
    fprintf(gp[1], "plot './AdhamarPh.dat' with linespoints \n");
    fprintf(gp[2], "plot './Theo.dat' with linespoints \n");

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

