#include "C4_5Algorithm.h"

void C4_5Algorithm::runAlgorithm(std::string file_name)
{
    DataSet set_data(file_name);
    shared_p root = std::make_shared<TreeNode>(std::make_shared<std::string>("-1"));
    ID3(set_data, root);
    //ciąg dalszy nastąpi...
}

void C4_5Algorithm::ID3(DataSet &subset, shared_p node)
{
    std::shared_ptr<std::string> alco_consum_level;
    if (subset.areAllYSame(alco_consum_level) || subset.lackOfXiAttributes(alco_consum_level))
    {
        node->chosen_attr_id = LEAF_ID;
        node->attr_values.push_back(alco_consum_level);
        return;
    }

    int d = subset.maxInfGainAttribute();                    //choosing attribute that maximalise InfoGain
    int init_id = subset.getRealIndex(d);
    node->chosen_attr_id = init_id;
    subset.getAttributeValues(d, node->attr_values);
    std::vector <DataSet> children_sets;
    subset.getSubSets(d, children_sets);                     //dividing set into subsets by chosen attribute
    for (int i = 0; i<children_sets.size(); ++i)             //creating subtrees recursively
    {
        node->children.push_back(std::make_shared<TreeNode>(node, node->attr_values[i]));
        ID3(children_sets[i], node->children[i]);
    }
    subset.restoreRealIndex(d, init_id);
}
