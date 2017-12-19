#include "btree.h"

namespace bt{

bool btree::btree(){
  root = NULL;
}
#if 0
bt_node* btree::get_next_node(bt_node *nd, int key) {
  int mid_idx = 0, st_idx = 0, end_idx = 0;
  if(nd->kv[0].first > key) return nd->ptrs[0];

  st_idx = 0;
  end_idx = nd->keys.size()-1;

  while(st_idx < end_idx) {
    mid_idx = (st_idx + end_idx)/2;

    if(nd->keys[mid_idx] == key)
      return nd->ptrs[mid_idx+1];
 
    if(nd->keys[mid_idx] > key)
      end_idx = mid_idx-1;
    else 
      st_idx = mid_idx;
    
  }

  return nd->ptrs[st_idx];
}

bool btree::search_leaf(bt_node *nd, int key, int &value) {
  int mid_idx = 0, st_idx = 0, end_idx = 0;
  if(nd->keys.size() == 0) return false;
  if(nd->keys.size() == 1) {
    value = nd->values[0];
    return true;
  }

  st_idx = 0;
  end_idx = nd->keys.size()-1;

  while(st_idx < end_idx) {
    mid_idx = (st_idx+end_idx)/2;

    if(nd->keys[mid_idx] == key) {
      value = nd->values[mid_idx];
      return true;
    }

    if(nd->keys[mid_idx] > key) {
      end_idx = mid_idx-1;
    } else {
      st_idx = mid_idx+1;
    }
  }

  if(nd->keys[st_idx] == key) {
    value = nd->values[st_idx];
    return true;
  }
  
  return false;
}

bool btree::search_key(int key, int &value) {
  bt_node *tmp; 

  //btree empty
  if(!root) return false;

  tmp = root;
  while(!tmp->is_leaf){
    tmp = get_next_node(tmp, key);
  }

  return search_leaf(tmp, key, value);
}
#endif

bt_node* btree::insert_split(bt_node *nd, int key, 
                     int value, bool &need_split) {
  
  int mid=0, sidx=0, eidx=nd->size()-2;//TBD

  while(sidx < eidx) {
    mid = (sidx+eidx)/2;
    //TBD - Need to handle '==' case
    if(nd->entries[mid] < key) 
      sidx = mid;
    else 
      eidx = mid-1;
  }

  if(nd->is_leaf) {
    bt_node_entry *tmp_ent = new bt_node_entry;
    tmp_ent->ptr = NULL;
    tmp_ent->key = key;
    tmp_ent->value = value;
    nd->entries.insert(nd->entries.begin()+sidx+1,
                       tmp_ent);
    if(nd->entries.size() > degree) need_split = true;
    else need_split = false;
    return nd;
  }

  need_split = false;
  insert_split(nd->entries[sidx+1].ptr, key, value, 
                                      need_split);

  if(need_split){
    bt_node *tmp = new bt_node;

  }
}

bool btree::insert_key(int key, int value) {
  bt_node *tmp;
  bt_node_entry *tmp_entry;
  bool need_split = false; 

  if(!root) {
    tmp = new bt_node;
    tmp->is_leaf = true;
    tmp_entry = new bt_node_entry;
    tmp_entry->ptr = NULL;
    tmp_entry->key = key;
    tmp_entry->value = value;
    tmp->entries.push_back(tmp_entry);
    root = tmp;
    return true;
  }

  root = insert_split(root, key, value, need_split);                            
}

bool btree::delete_key(int key) {
}

};
