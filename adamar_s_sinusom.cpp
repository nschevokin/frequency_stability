#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

void firstH(int m,int t,int i){

    int M =1000;

    double y[M];
    for(int i =0;i<M;i++)
    {
        y[i] = sin(1 + rand() % 1000);
    }
    double first =  1 / (6*pow(m,2)*pow(t,2) * (M-3*m+1));
    double sum = 0;
    for (int j = 1 ; j <= (M-3*m+1); j++)
    {
        double sum_pod = 0;
        for(int i = j;i<=(j+m-1);i++)
        {
            sum_pod += y[i+2*m]-2*y[i+m]+y[i];
        }
        sum += pow(sum_pod,2);
    }

    double H = first*sum;
    cout <<i<<" : "<< H << endl;

    int N = M + 1;
    first = 1/(6*pow(t,2)*(N-3*m));
    sum =0;

    for (int i=1;i<=(M-3*m);i++)
    {
        sum += pow(y[i+3*m] - 3*y[i+2*m] + 3*y[i+m] - y[i],2);
    }
    double H2 = first*sum;
    cout <<i<<" : "<<  H2 << endl;


};


int main()
{
    srand(time( 0 ));
    int m,t=10;
    int M =10;
    cout << "m = ";
    cin >> m;

    float y[M];
    for(int i =0;i<M;i++)
    {
        firstH(m,t,i);
    }
}
