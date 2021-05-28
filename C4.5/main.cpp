#include <iostream>
#include "dataSet.h"

#include <cmath>
using namespace std;

int main()
{
    DataSet dane("student-mat.csv");
    cout << dane.setEntropy;
    return 0;
}
