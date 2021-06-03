#ifndef C4_5ALGORITHM_H_INCLUDED
#define C4_5ALGORITHM_H_INCLUDED

#include <cstdlib>
#include <cctype>

#include "treeNode.h"
#include "dataSet.h"
#include "algorithm"

#define LEAF_ID -1

class C4_5Algorithm
{
    typedef std::shared_ptr<std::string> shared_p_s;
    typedef std::unordered_map<shared_p_s, int> umap;
    typedef std::shared_ptr<TreeNode> shared_p;

public:
    void runAlgorithm(std::string training_set_file, std::string pruning_set_file);

//private:
    shared_p root;
    void ID3(DataSet &subset, shared_p node);
    void predictOnPruningSet(DataSet &subset, shared_p root);
    void pruneTree (shared_p node);
};

#endif // C4_5ALGORITHM_H_INCLUDED
