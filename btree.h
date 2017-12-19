#include <cstdlib>
#include <vector>

namespace bt {

struct bt_node_entry{
  bt_node *ptr;
  int key;
  int value;
};



struct bt_node{
  bool is_leaf;
  vector<bt_node_entry> entries;
};

class btree {
  public:
  bool search_key(int key, int &value);
  bool insert_key(int key, int value);
  bool delete_key(int key);

  private:
  int degree;
  bt_node *root;
};

} //namespace bt
