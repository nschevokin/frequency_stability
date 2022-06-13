#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    
    ifstream input_file("PHASE.dat");
    double num;
    int M=0;
    while (!input_file.eof())
    {
        input_file >> num;
        M++;
    }
    input_file.close();
    M--;
    ifstream read_file("PHASE.dat");
    double y[M];
    for(int i=0;i<M;i++)
    {
        read_file >> y[i];
        cout << y[i] << endl;
    }
    read_file.close();
    
    int m,t;
    
    cout << "m = ";
    cin >> m;
    cout << "t = ";
    cin >> t;
    
    double first =  1 / (6*pow(m,2)*pow(t,2) * (M-3*m+1));
    double sum = 0;
    for (int j = 1 ; j <= (M-3*m+1); j++){
        long double sum_pod = 0;
        for(int i = j;i<=(j+m-1);i++){
            sum_pod += y[i+2*m]-2*y[i+m]+y[i];
        }
        sum += pow(sum_pod,2);
    }
    
    double H = first*sum;
    cout << sqrt(H) << endl;
    
    int N = M + 1;
    first = 1/(6*pow(t,2)*(N-3*m));
    sum =0;
    
    for (int i=1;i<=(M-3*m);i++){
        sum += pow(y[i+3*m] - 3*y[i+2*m] + 3*y[i+m] - y[i],2);
    }
    
    double H2 = first*sum;
    cout << sqrt(H2) << endl;
    
    return 0;
}