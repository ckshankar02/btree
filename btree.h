#include <iostream>
#include <cstdlib>
#include <vector>

namespace bt {

struct bt_node_entry{
  //bt_node *ptr;
  void *ptr;
  int key;
  int value;
};

struct bt_node{
  bool is_leaf;
  std::vector<bt_node_entry *> entries;
};

class btree {
  public:
  btree();
  bt_node* get_root();
  void dump_tree(bt_node *nd);
  bool search_key(int key, int &value);
  bool insert_key(int key, int value);
  bool delete_key(int key);

  //Helper
  bt_node* insert_split(bt_node *nd, int key,
               int value, bool &need_split);

  private:
  int degree;
  bt_node *root;
};

} //namespace bt
