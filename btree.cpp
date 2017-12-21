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
	bt_node *

	//Searching the bt_node for ptr for child node
  if(nd->entries[0].key > key) sidx = 0;
  else if (nd->entries[nd->entries.size()-2].key < key) 
    sidx = nd->entries.size()-1;
  else {
    while(sidx < eidx) {
      mid = (sidx+eidx)/2;
   
      if(nd->entries[mid] == key) {
        sidx = mid+1;
        break;
      }

      if(nd->entries[mid].key < key) 
       sidx = mid+1; //MONITOR
      else 
        eidx = mid-1;
    }
  }

	//Insert key & value if at leaf node
  if(nd->is_leaf) {
    bt_node_entry *tmp_ent = new bt_node_entry;
    tmp_ent->ptr = NULL;
    tmp_ent->key = key;
    tmp_ent->value = value;
    nd->entries.insert(nd->entries.begin()+sidx, tmp_ent);//MONITOR
    if(nd->entries.size() > degree) need_split = true;
    else return nd;
  } 
  else {
	  //Recursively find the leaf node
    need_split = false;
    insert_split(nd->entries[sidx].ptr, key, value, 
  }                                     need_split); //MONITOR

	//Split the child node and add an entry 
  if(need_split && !nd->is_leaf){
    bt_node_entry *tmp_ent = NULL;
    bt_node *nw_node = new bt_node;
    bt_node *tmp = nd->entries[sidx].ptr;
    int split_size = (tmp->entries.size()-1)/2;

		nw_node->is_leaf = tmp->is_leaf;
    for(int i=0;i<split_size;i++) {
      nw_node->entries.push_back(tmp->entries[i]);
    }
	  dummy = new bt_node_entry;
		dummy->key = 0
		dummy->value = 0;
		dummy->ptr = tmp;
    nw_node->entries.push_back(dummy);

    tmp->entries.erase(tmp->entries.begin(), 
                 tmp->entries.begin()+split_size);
   
    tmp_ent = new bt_node_entry;
    tmp_ent->key = tmp->entries[0].key;
    tmp_ent->value = -1;
    tmp_ent->ptr = nw_node;
    nd->entries.insert(nd->entries.begin()+sidx, tmp_ent);
		if(nd->entries.size() <= degree) need_split = false;
  }


	//If root needs to split
	if(nd == root && need_split) {
		bt_node *nw_root = new bt_node;
		bt_node *nw_node = new bt_node;
		bt_node_entry *dummy = NULL;
    int split_size = (nd->entries.size-1)/2;


    tmp->is_leaf = nd->is_leaf;

		for(int i=0;i<split_size;i++){
			nw_node->entries.push_back(nd->entries[i]);
		}

	  dummy = new bt_node_entry;
		dummy->key = 0
		dummy->value = 0;
		dummy->ptr = nd;
    nw_node->entries.push_back(dummy);

		nd->entries.erase(nd->entries.begin(),
								nd->entries.begin()+split_size);

		bt_node_entry *ent = new bt_node_entry;
		ent_1->key = nd->entries[0].key;
		ent_1->value = -1;
		ent_1->ptr = nw_node;
	
	  dummy = new bt_node_entry;
		dummy->key = 0
		dummy->value = 0;
		dummy->ptr = nd;

		nw_root.push_back(ent);
		nw_root.push_back(dummy);
		
		root = nw_root;
		need_split = false;	
		return root;
	}

	return nd;
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
    bt_node_entry *dummy = new bt_node_entry;
    dummy->key = -1;
    dummy->value = -1;
    dummy->ptr = NULL:
    tmp->entries.push_back(dummy);
    root = tmp;
    return true;
  }

  root = insert_split(root, key, value, need_split);                            
}

bool btree::delete_key(int key) {
}

};
