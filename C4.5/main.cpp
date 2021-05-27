#include <iostream>
#include "dataSet.h"

#include <cmath>
using namespace std;

int main()
{
    DataSet dane("student-mat.csv");
    cout << dane.maxInfGainAttribute() << endl;
    for (int i =0; i < dane.data.size()-1; ++i)
        cout << dane.calculateInfGain(i) << endl;
    return 0;
}
