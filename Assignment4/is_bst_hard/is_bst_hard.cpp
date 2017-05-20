#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_single(int index, vector<int> & result, const vector<Node> & tree)
{
    if (tree[index].left != -1) {in_order_single(tree[index].left,result,tree);}
    result.push_back(tree[index].key);
    if (tree[index].right != -1) {in_order_single(tree[index].right,result,tree);}
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    vector<int> result;
    if (tree.size() == 0) {return true;}
    in_order_single(0,result,tree);
    auto i2 = std::adjacent_find(result.begin(), result.end(), std::greater_equal<int>());
    return (i2 == result.end()); 
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
