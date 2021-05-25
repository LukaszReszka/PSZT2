#ifndef DATASET_H_INCLUDED
#define DATASET_H_INCLUDED

#include <vector>
#include <string>

#define N_ATTRIBUTES 32

class DataSet
{
public:

void loadData (std::string file_name);
void clearDataSet (void);

//private:
std::vector<std::vector <std::string>> data;
std::vector<std::vector <std::string>> attributeVales;

};
#endif // DATASET_H_INCLUDED
