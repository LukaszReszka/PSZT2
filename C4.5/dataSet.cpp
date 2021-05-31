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
    data.resize(N_ATTRIBUTES);
    attributeVales.resize(N_ATTRIBUTES);
    file.open(file_name, std::ios::in);
    if (!file) exit(-1);
    getline(file, temp);
    while (getline(file, temp))
    {
        std::stringstream row(temp);
        while (getline(row, value, ','))
        {
            data[attr_numb].push_back(shared_p(new std::string (value)));
            auto it = std::find_if(attributeVales[attr_numb].begin(), attributeVales[attr_numb].end(), [&](shared_p const& p)
            {return *p == value;});     //lambda expression
            if(it == attributeVales[attr_numb].end())
                attributeVales[attr_numb].push_back(shared_p(new std::string (value)));

            attr_numb = (attr_numb+1)%N_ATTRIBUTES;
        }

    }
    file.close();
    ALCOHOL_CONSUMP_ATTR = data.size()-1;
    setEntropy = calculateEntropy(data[ALCOHOL_CONSUMP_ATTR]);
}

void DataSet::loadData (std::vector<std::vector<shared_p>> &set_data)
{
    int number_of_attributes = set_data.size();
    data.resize(number_of_attributes);
    attributeVales.resize(number_of_attributes);
    for (int i = 0; i < number_of_attributes; ++i)
    {
        for(int j = 0; j < set_data[i].size(); ++j)
        {
            data[i].push_back(shared_p(set_data[i][j]));
            auto it = std::find_if(attributeVales[i].begin(), attributeVales[i].end(), [&](shared_p const& p)
            {return *p == *set_data[i][j];});     //lambda expression
            if(it == attributeVales[i].end())
                attributeVales[i].push_back(shared_p(set_data[i][j]));
        }
    }
    ALCOHOL_CONSUMP_ATTR = data.size()-1;
    setEntropy = calculateEntropy(data[ALCOHOL_CONSUMP_ATTR]);
}

double DataSet::calculateEntropy (std::vector<shared_p> &alcohol_consum_tab)
{
    double entr = 0.0;
    for (auto i: attributeVales[ALCOHOL_CONSUMP_ATTR])
    {
        int class_numb = std::count_if(alcohol_consum_tab.begin(), alcohol_consum_tab.end(),
        [&](shared_p const& p){return *p == *i;});  //lambda expression
        if (class_numb)
        {
            double class_freq = (double) class_numb/alcohol_consum_tab.size();
            entr -= class_freq*std::log(class_freq);
        }
    }
    return entr;
}

double DataSet::calculateInfGain(int attr_index)
{
    std::vector<std::vector <shared_p>> subsets_alco_consum;
    int subsets_numb = attributeVales[attr_index].size();
    subsets_alco_consum.resize(subsets_numb);
    for (int i = 0; i < data[attr_index].size(); ++i)
        for (int j = 0; j < subsets_numb; ++j)
            if(*data[attr_index][i] == *attributeVales[attr_index][j])
            {
                subsets_alco_consum[j].push_back(shared_p(data[ALCOHOL_CONSUMP_ATTR][i]));
                break;
            }
    double result = setEntropy;
    for (auto s: subsets_alco_consum)
        result -= ((double) calculateEntropy(s)*s.size()/data[attr_index].size());
    return result;
}

int DataSet::maxInfGainAttribute(void)
{
    int chosen_attr = -1;
    double currentInfGain = 0;
    for (int i = 0; i < data.size()-1; ++i)
    {
        double InfGain = calculateInfGain(i);
        if (InfGain == InfGain && InfGain > currentInfGain)
        {
            currentInfGain = InfGain;
            chosen_attr = i;
        }
    }
    return chosen_attr;
}


void DataSet::getSubSets(int attr_index, std::vector<DataSet> &subsets)
{
    int subsets_numb = attributeVales[attr_index].size();
    subsets.resize(subsets_numb);
    std::vector<std::vector<std::vector <shared_p>>> subsets_data;
    subsets_data.resize(subsets_numb);
    for (int s = 0; s < subsets_numb; ++s)
        subsets_data[s].resize(data.size()-1);

    for (int record_index = 0; record_index < data[attr_index].size(); ++record_index)
        for (int subset_index = 0; subset_index < subsets_numb; ++subset_index)
           if(*data[attr_index][record_index] == *attributeVales[attr_index][subset_index])
            {
                int subset_rec_attr_index = 0;
                for (int record_attr_index = 0;  record_attr_index < data.size(); ++record_attr_index)
                {
                    subsets_data[subset_index][subset_rec_attr_index].push_back(shared_p(data[record_attr_index][record_index]));
                    if (record_attr_index == attr_index) record_attr_index++;   //excluding one attribute
                    subset_rec_attr_index++;
                }
                break;
            }

    for (int i = 0; i < subsets_numb; ++i)
        subsets[i].loadData(subsets_data[i]);
}
