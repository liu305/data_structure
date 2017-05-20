#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void in_order_single(int key_value, int left_index, int right_index, vector<int> & result)
  {
      if (left_index != -1) {in_order_single(key[left_index],left[left_index],right[left_index],result);}
      result.push_back(key_value);
      if (right_index != -1) {in_order_single(key[right_index],left[right_index],right[right_index],result);}
  }

  vector <int> in_order() {
    vector<int> result;
    in_order_single(key[0],left[0],right[0],result);
    return result;
  }

  void pre_order_single(int key_value, int left_index, int right_index, vector<int> & result)
  {
      result.push_back(key_value);
      if (left_index != -1) {pre_order_single(key[left_index],left[left_index],right[left_index],result);}
      if (right_index != -1) {pre_order_single(key[right_index],left[right_index],right[right_index],result);}
  }

  vector <int> pre_order() {
    vector<int> result;    
    pre_order_single(key[0],left[0],right[0],result); 
    return result;
  }

  void post_order_single(int key_value, int left_index, int right_index, vector<int> & result)
  {
      if (left_index != -1) {post_order_single(key[left_index],left[left_index],right[left_index],result);}
      if (right_index != -1) {post_order_single(key[right_index],left[right_index],right[right_index],result);}
      result.push_back(key_value);
  }

  vector <int> post_order() {
    vector<int> result;
    post_order_single(key[0],left[0],right[0],result); 
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

