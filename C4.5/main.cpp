#include <iostream>
#include "C4_5Algorithm.h"

using namespace std;

void wypisz(shared_ptr<TreeNode> &node, int m = 0)
{
    for (int j = 0; j < m; ++j)
        cout << "=";
    cout<<node->chosen_attr_id << endl;
    if (node->chosen_attr_id == -1) return;
    int new_m = ++m;
    for (int i = 0; i< node->children.size(); ++i)
    {
            wypisz(node->children[i], new_m);
    }

}

int main()
{
    C4_5Algorithm alg;
    alg.runAlgorithm("student-mat-train.csv", "student-mat-prune.csv");
    shared_ptr<TreeNode> actual = alg.root;
//    wypisz(actual);
    return 0;
}
