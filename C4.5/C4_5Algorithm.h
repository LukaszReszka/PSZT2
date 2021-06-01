#ifndef C4_5ALGORITHM_H_INCLUDED
#define C4_5ALGORITHM_H_INCLUDED

#include "treeNode.h"
#include "dataSet.h"

#define LEAF_ID -1

class C4_5Algorithm
{
    typedef std::shared_ptr<TreeNode> shared_p;

public:
    void runAlgorithm(std::string file_name);

private:
    void ID3(DataSet &subset, shared_p node);
};

#endif // C4_5ALGORITHM_H_INCLUDED
