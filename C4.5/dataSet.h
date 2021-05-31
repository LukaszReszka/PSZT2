#ifndef DATASET_H_INCLUDED
#define DATASET_H_INCLUDED

#include <vector>
#include <string>
#include <memory>

#define N_ATTRIBUTES 32

class DataSet
{
    typedef std::shared_ptr<std::string> shared_p;

public:
    DataSet(void){}
    DataSet(std::string file_name) {loadData(file_name);}
    DataSet(std::vector<std::vector<shared_p>> &set_data) {loadData(set_data);}
    void loadData (std::string file_name);
    void loadData (std::vector<std::vector<shared_p>> &set_data);
    int maxInfGainAttribute(void);
    void getSubSets(int attr_index, std::vector<DataSet> &subsets);

private:
    std::vector<std::vector <shared_p>> data;
    std::vector<std::vector <shared_p>> attributeVales;
    double setEntropy = 0.0;
    int ALCOHOL_CONSUMP_ATTR;

    double calculateEntropy (std::vector<shared_p> &alcohol_consum_tab);
    double calculateInfGain(int attr_index);
};
#endif // DATASET_H_INCLUDED
