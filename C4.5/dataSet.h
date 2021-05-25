#ifndef DATASET_H_INCLUDED
#define DATASET_H_INCLUDED

#include <vector>
#include <string>

#define N_ATTRIBUTES 32
#define ALCOHOL_CONSUMP_ATTR 31

class DataSet
{
public:
    DataSet(void){}
    DataSet(std::string file_name) {loadData(file_name);}
    void loadData (std::string file_name);

//private:
    std::vector<std::vector <std::string>> data;
    std::vector<std::vector <std::string>> attributeVales;
    double entropy = 0.0;

    void clearDataSet (void);
    double calculateEntropy (std::vector<std::string> &alcohol_consum_tab);
};
#endif // DATASET_H_INCLUDED
