#include "C4_5Algorithm.h"

void C4_5Algorithm::runAlgorithm(std::string training_set_file, std::string pruning_set_file)
{
    DataSet training_set(training_set_file);
    root = std::make_shared<TreeNode>(std::make_shared<std::string>("-1"));
    ID3(training_set, root);
    DataSet pruning_set(pruning_set_file);
    predictOnPruningSet(pruning_set, root);
    pruneTree(root);
}

void C4_5Algorithm::ID3(DataSet &subset, shared_p node)
{
    shared_p_s alco_consum_level;
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

void C4_5Algorithm::predictOnPruningSet(DataSet &subset, shared_p root)
{
    std::vector<shared_p_s> record;
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

            int index;                                                                  //choosing to which node proceed next
            for (index = 0; index < current_node->attr_values.size(); ++index)
                if(*current_node->attr_values[index] == *record[current_node->chosen_attr_id])
                    break;

            if (index == current_node->attr_values.size())                  //if value of one of record's attributes doesn't match with any values of that attributed stored in tree
            {
                if(!isdigit((*record[current_node->chosen_attr_id])[0]))
                    index = 0;
                else
                {
                    int record_val = atoi((*record[current_node->chosen_attr_id]).c_str());
                    int best_difference = 100;
                    for (int j = 0; j<current_node->attr_values.size(); ++j)
                    {
                        int current_value = atoi((*current_node->attr_values[j]).c_str());
                        int current_difference = abs(current_value - record_val);
                        if (current_difference < best_difference)
                        {
                            index = j;
                            best_difference = current_difference;
                        }
                    }
                }
            }

            current_node = current_node->children[index];           //proceeding to another node
        }

        auto res = current_node->data_for_pruning.find(record[record.size()-1]);
        if (res == current_node->data_for_pruning.end())
                current_node->data_for_pruning[record[record.size()-1]] = 0;
            else
                ++current_node->data_for_pruning[record[record.size()-1]];
    }
}

void C4_5Algorithm::pruneTree (shared_p node)
{   //predicting error rates, using formula: (total_errors+0.5*leaf_numbers)/total_predicton_number
    if (node->chosen_attr_id == LEAF_ID) return;

    for (auto child: node->children)
        pruneTree(child);

    for (auto c: node->children)
        if(c->chosen_attr_id != LEAF_ID)
            return;

    umap classes_in_subtree;
    int current_good_predictions = 0;
    int total_predictions = 0;

    for (auto n: node->children)
    {
        shared_p_s predicted_class = n->attr_values[0];
        for (auto m: n->data_for_pruning)
        {
            total_predictions += m.second;
            if(*predicted_class == *m.first)
                current_good_predictions += m.second;
        }

        auto s = classes_in_subtree.find(predicted_class);
        if (s == classes_in_subtree.end())
            classes_in_subtree[predicted_class] = 0;
        else
            classes_in_subtree[predicted_class]++;
    }

    //current error rate
    double current_e_r = (double) (total_predictions - current_good_predictions + (0.5*node->children.size()))/total_predictions;

    //finding most frequent classes
    auto f = std::max_element(classes_in_subtree.begin(), classes_in_subtree.end(),
    [](const std::pair<shared_p_s, int> &p1, const std::pair<shared_p_s, int> &p2)
    {return p1.second < p2.second;});       //lambda expression

    shared_p_s chosen_class;
    double prune_e_r = -1.0;
    for(auto c: classes_in_subtree)
        if(c.second == f->second)
        {
            double error_rate = (double) (total_predictions - node->data_for_pruning[c.first] + 0.5)/total_predictions;
            if (prune_e_r == -1.0 || error_rate < prune_e_r)
            {
                prune_e_r = error_rate;
                chosen_class = c.first;
            }
        }

    if(prune_e_r <= current_e_r)         //pruning tree
    {
        node->chosen_attr_id = LEAF_ID;
        node->children.clear();
        node->attr_values.clear();
        node->attr_values.push_back(chosen_class);
    }
}

void C4_5Algorithm::showTree (shared_p &node, int m)
{
    for (int j = 0; j < m; ++j)
        std::cout << "=";
    std::cout<<node->chosen_attr_id << std::endl;
    if (node->chosen_attr_id == -1) return;
    int new_m = ++m;
    for (int i = 0; i< node->children.size(); ++i)
            showTree(node->children[i], new_m);
}

void C4_5Algorithm::showTree (void)
{
   showTree(root, 0);
}

std::string C4_5Algorithm::predictAlcoholConsum(std::vector<shared_p_s> &record)
{
    shared_p current_node = root;
    while (current_node->chosen_attr_id != LEAF_ID)
    {
        int index = 0;                                                           //choosing to which node proceed next
        for (index = 0; index < current_node->attr_values.size(); ++index)
            if(*current_node->attr_values[index] == *record[current_node->chosen_attr_id])
                break;

        if (index == current_node->attr_values.size())                  //if value of one of record's attributes doesn't match with any values of that attributed stored in tree
        {
            if(!isdigit((*record[current_node->chosen_attr_id])[0]))
                index = 0;
            else
            {
                int record_val = atoi((*record[current_node->chosen_attr_id]).c_str());
                int best_difference = 100;
                for (int j = 0; j<current_node->attr_values.size(); ++j)
                {
                    int current_value = atoi((*current_node->attr_values[j]).c_str());
                    int current_difference = abs(current_value - record_val);
                    if (current_difference < best_difference)
                    {
                        index = j;
                        best_difference = current_difference;
                    }
                }
            }
        }

        current_node = current_node->children[index];           //proceeding to another node
    }
    return *current_node->attr_values[0];
}
