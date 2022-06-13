#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    //
    int m,t;
    int M;
    cout << "m =";
    cin >> m;
    cout << "t =";
    cin >> t;
    cout << "M =";
    cin >> M;

    double y[M];
    for(int i =0;i<M;i++){
        cout << i <<"y :";
        cin >> y[i];
    }

    float first =  1 / (6*pow(m,2)*pow(t,2) * (M-3*m+1));
    float sum = 0;
    for (int j = 1 ; j <= (M-3*m+1); j++){
        float sum_pod = 0;
        for(int i = j;i<=(j+m-1);i++){
            sum_pod += y[i+2*m]-2*y[i+m]+y[i];
        }
        sum += pow(sum_pod,2);
    }

    float H = first*sum;
    cout << H << endl;

    int N = M + 1;
    first = 1/(6*pow(t,2)*(N-3*m));
    sum =0;

    for (int i=1;i<=(M-3*m);i++){
        sum += pow(y[i+3*m] - 3*y[i+2*m] + 3*y[i+m] - y[i],2);
    }

    double H2 = first*sum;
    cout << H2 << endl;
    return 0;
}
