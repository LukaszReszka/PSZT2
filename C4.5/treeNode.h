#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED
#include <memory>
#include <vector>

struct TreeNode
{
    typedef std::weak_ptr<TreeNode> weak_p_n;
    typedef std::shared_ptr<std::string> shared_p_s;
    typedef std::shared_ptr<TreeNode> shared_p_n;

    TreeNode(shared_p_s chosen_value): parent_val(chosen_value) {}
    TreeNode(weak_p_n parent, shared_p_s chosen_value): parent_p(parent), parent_val(chosen_value) {}

    int chosen_attr_id;
    weak_p_n parent_p;
    shared_p_s parent_val;
    std::vector<shared_p_s> attr_values;
    std::vector<shared_p_n> children;
};

#endif // TREENODE_H_INCLUDED
