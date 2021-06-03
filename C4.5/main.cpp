#include "C4_5Algorithm.h"

using namespace std;

int main()
{
    C4_5Algorithm alg;
    alg.runAlgorithm("student-mat-train.csv", "student-mat-prune.csv");

    vector<shared_ptr<string>> record;
    DataSet data("student-mat-train.csv");
    data.getRecord(2, record);
    std::cout<<*record[31] << endl;
    cout << alg.predictAlcoholConsum(record);

//    alg.showTree();
    return 0;
}
