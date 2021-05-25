#include <iostream>
#include "dataSet.h"

using namespace std;

int main()
{
    DataSet dane("student-mat.csv");
    cout << dane.entropy;
    return 0;
}
