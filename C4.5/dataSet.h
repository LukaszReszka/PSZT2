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
    void loadData (std::string file_name);
    int maxInfGainAttribute(void);
    DataSet* getSubSets(int attr_index);

//private:
    std::vector<std::vector <shared_p>> data;
    std::vector<std::vector <shared_p>> attributeVales;
    double setEntropy = 0.0;
    int ALCOHOL_CONSUMP_ATTR;

    void clearDataSet (void);
    double calculateEntropy (std::vector<shared_p> &alcohol_consum_tab);
    double calculateInfGain(int attr_index);
};
#endif // DATASET_H_INCLUDED
