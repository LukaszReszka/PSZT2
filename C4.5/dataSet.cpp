#include "dataSet.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void DataSet::loadData(std::string file_name)
{
    std::fstream file;
    std::string value, temp, loop;
    int attr_numb = 0;
    clearDataSet();
    file.open(file_name, std::ios::in);
    if (!file) exit(-1);
    getline(file, temp);
    while (getline(file, temp))
    {
        std::stringstream row(temp);
        while (getline(row, value, ','))
        {
            data[attr_numb].push_back(value);

            if(std::find(attributeVales[attr_numb].begin(), attributeVales[attr_numb].end(), value) == attributeVales[attr_numb].end())
                attributeVales[attr_numb].push_back(value);

            attr_numb = (attr_numb+1)%N_ATTRIBUTES;
        }

    }
    file.close();
}

void DataSet::clearDataSet (void)
{
    for(auto i: data)
        i.clear();
    data.clear();
    data.resize(N_ATTRIBUTES);

    for(auto j: attributeVales)
        j.clear();
    attributeVales.clear();
    attributeVales.resize(N_ATTRIBUTES);
}
