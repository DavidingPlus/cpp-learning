#include <iostream>
using namespace std;
#include "10_BinaryTree.h"

/*
       1
   3         2
4    6    8
    7        0
*/
namespace test
{
    BinaryTree<int> sample()
    {
        BinaryTree<int> tree(1);
        tree.getroot().insert(3, Left);
        // left
        auto leftNode = tree.getroot().left;
        leftNode->insert(4, Left);
        leftNode->insert(6, Right);
        auto leftNode2 = leftNode->right;
        leftNode2->insert(7, Left);
        // right
        tree.getroot().insert(2, Right);
        auto rightNode = tree.getroot().right;
        rightNode->insert(8, Left);
        auto rightNode2 = rightNode->left;
        rightNode2->insert(0, Right);

        return tree;
    }
}

int main()
{
    auto tree = test::sample();

    tree.printTree(pre); // 1 3 4 6 7 2 8 0
    cout << endl;
    tree.printTree(in); // 4 3 7 6 1 8 0 2
    cout << endl;
    tree.printTree(post); // 4 7 6 3 0 8 2 1

    return 0;
}
