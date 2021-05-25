#include <iostream>
#include "dataSet.h"

using namespace std;

int main()
{
    DataSet dane;
    dane.loadData("student-mat.csv");
    for (int i = 0; i < 32; ++i)
    {
        for (auto j: dane.attributeVales[i])
        {
            cout << j << ",";
        }
        cout << endl;
    }
    return 0;
}
