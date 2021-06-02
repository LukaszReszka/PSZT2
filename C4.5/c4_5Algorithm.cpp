#include "C4_5Algorithm.h"

void C4_5Algorithm::runAlgorithm(std::string training_set_file, std::string pruning_set_file)
{
    DataSet training_set(training_set_file);
    root = std::make_shared<TreeNode>(std::make_shared<std::string>("-1"));
    ID3(training_set, root);
    DataSet pruning_set(pruning_set_file);
    predictOnPruningSet(pruning_set, root);
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

#include <iostream>

void C4_5Algorithm::predictOnPruningSet(DataSet &subset, shared_p root)
{
    std::vector<std::shared_ptr<std::string>> record;
    for (int i = 0; subset.getRecord(i, record); ++i)
    {
        shared_p current_node = root;
        while (current_node->chosen_attr_id != LEAF_ID)
        {
            auto res = current_node->data_for_pruning.find(record[record.size()-1]);    //saving in unordered_map vital information for estimating error rates
            if (res == current_node->data_for_pruning.end())
                current_node->data_for_pruning[record[record.size()-1]] = 0;
            else
                ++current_node->data_for_pruning[record[record.size()-1]];

            int index;
            for (index = 0; index < current_node->attr_values.size(); ++index)                    //proceeding to another node
                if(*current_node->attr_values[index] == *record[current_node->chosen_attr_id])
                    break;
            current_node = current_node->children[index];
        }
        auto res = current_node->data_for_pruning.find(record[record.size()-1]);
        if (res == current_node->data_for_pruning.end())
                current_node->data_for_pruning[record[record.size()-1]] = 0;
            else
                ++current_node->data_for_pruning[record[record.size()-1]];
    }
}
