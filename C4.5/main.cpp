#include <iostream>
#include "dataSet.h"

using namespace std;

int main()
{
    DataSet dane("student-mat.csv");
    cout << dane.calculateInfGain(19);
    return 0;
}
