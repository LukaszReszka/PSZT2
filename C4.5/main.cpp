#include <iostream>
#include "dataSet.h"

#include <cmath>
using namespace std;

int main()
{
    DataSet dane("student-mat.csv");
    vector <DataSet> substets;
    dane.getSubSets(27, substets);
    cout << *substets[11].data[30][0];
    return 0;
}
