#include "dataSet.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

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
    setEntropy = calculateEntropy(data[ALCOHOL_CONSUMP_ATTR]);
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

double DataSet::calculateEntropy (std::vector<std::string> &alcohol_consum_tab)
{
    double entr = 0;
    for (auto i: attributeVales[ALCOHOL_CONSUMP_ATTR])
    {
        int class_numb = std::count(alcohol_consum_tab.begin(), alcohol_consum_tab.end(), i);
        double class_freq = (double) class_numb/alcohol_consum_tab.size();
        entr -= class_freq*std::log(class_freq);
    }
    return entr;
}

double DataSet::calculateInfGain(int attr_index)
{
    std::vector<std::vector <std::string>> subsets_alco_consum;
    int subsets_numb = attributeVales[attr_index].size();
    subsets_alco_consum.resize(subsets_numb);
    for (int i = 0; i < data[attr_index].size(); ++i)
        for (int j = 0; j < subsets_numb; ++j)
            if(data[attr_index][i] == attributeVales[attr_index][j])
            {
                subsets_alco_consum[j].push_back(data[ALCOHOL_CONSUMP_ATTR][i]);
                break;
            }
    double result = setEntropy;
    for (auto s: subsets_alco_consum)
        result -= ((double) calculateEntropy(s)*s.size()/data[attr_index].size());
    return result;
}
