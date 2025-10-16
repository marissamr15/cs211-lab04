/*mapll.h*/

/**
  * @brief implementation of std::map using a linked-list
  *
  * Our implementation of std::map. Note that since map
  * is templated, there is no separate .cpp file --- the code
  * must also be placed in the .h file.
  * 
  * For simplicity, we implement map using a linked-list,
  * not a balanced search tree.
  * 
  * @note << YOUR NAME? >>
  *
  * @note Initial template by Prof. Joe Hummel
  * @note Northwestern University
 */

#pragma once

#include <utility>  // std::pair, make_pair()


//
// class map:
//
template<typename KeyT, typename ValueT>
class map {
private:
  //
  // Implementing map as a linked-list of nodes, so 
  // here's the definition of one node:
  //
  struct NODE {
    std::pair<KeyT, ValueT> KV_pair;
    NODE*                   Next;

    NODE(KeyT key, ValueT value)
      : KV_pair(std::make_pair(key, value)), Next(nullptr)
    { }
  };

  //
  // data members:
  //
  NODE*   Root;  // pointer to first node in linked-list
  size_t  Size;  // # of nodes in the linked-list

public:
  // 
  // constructor:
  //
  map()
    : Root(nullptr), Size(0)
  { }

  //
  // destructor:
  //
  ~map()
  {
    NODE* cur = this->Root;
    while(cur != nullptr){
      NODE* temp = cur;
      cur = cur->Next;
      delete temp;
    }
  }

  //
  // size:
  //
  size_t size() {
    return this->Size;
  }

  //
  // []:
  //
  ValueT& operator[](KeyT key)
  {
    //
    // first we search to see if the given key is
    // already in the list, and if so, we return
    // the VALUE as a reference (C++ handles the 
    // reference part, we just return the value):
    //
    NODE* cur = this->Root;

    while (cur != nullptr) {
      if (cur->KV_pair.first == key) {  // found it!
        return cur->KV_pair.second;     // return value:
      }

      cur = cur->Next;
    }

    //
    // not found, we have to insert at the 
    // front of the list and return the VALUE
    // as a reference (C++ handles the reference
    // part, we just return the value):
    //
    NODE* newNode = new NODE(key, ValueT() /*default value*/);

    // link existing nodes after the new node:
    newNode->Next = this->Root;

    // now point Root to new node so it's first:
    this->Root = newNode;

    // update size, we have one more node:
    this->Size++;

    // return new node's value:
    return newNode->KV_pair.second;
  }

  //
  // erase:
  //
  int erase(KeyT key)
  {
    //
    // First we search to see if key appears in the list.
    // We search using two pointers, where prev is the 
    // node PREVIOUS to cur so that if we find the key,
    // we can update the previous node to unlink cur:
    //
    NODE* prev = nullptr;
    NODE* cur = this->Root;

    while (cur != nullptr) {

      if (key == cur->KV_pair.first) // found it:
        break;

      prev = cur;  // not found, advance prev and cur:
      cur = cur->Next;
    }

    //
    // at this point the loop is over, either we found it
    // or we searched the entire list. Which is it?
    //
    if (cur == nullptr) { // didn't find key:
      return 0;  // 0 => no nodes were deleted
    }
    else {
      //
      // unlink cur from the list, free the memory, and
      // return 1 denoting we have deleted one node:
      //
      // BEWARE: what if prev is nullptr?
      //

      // TODO:
      if (prev == nullptr) { // means we r at root, so make next one root
        this->Root = cur->Next;
      }
      else {
        prev->Next = cur->Next;
      }
      delete cur;
      this->Size--;

      return 1;  // change this to 1 when you have it working
    }
  }


private:
  //
  // class iterator:
  // 
  // An iterator is an object that points to a NODE in
  // the linked-list. The ptr is nullptr when we have 
  // iterated through all the nodes and reached the end
  // of the list. 
  // 
  // Iterators are used as "safe" pointers, and allow 
  // users to (1) iterate through the map using foreach,
  // and (2) safely search a map without inserting pairs.
  //
  class iterator {
  private:
    NODE* Ptr;

  public:
    //
    // constructor:
    //
    iterator(NODE* ptr)
      : Ptr(ptr)
    { }

    //
    // are two iterators == ?
    //
    bool operator==(iterator other)
    {
      if (this->Ptr == other.Ptr)
        return true;
      else
        return false;
    }

    //
    // are two iterators != ?
    //
    bool operator!=(iterator other)
    {
      if (this->Ptr == other.Ptr)
        return false;
      else
        return true;
    }

    //
    // advance the iterator to the next NODE in 
    // the list
    //
    void operator++()
    {
      if (this->Ptr == nullptr)
        ;  // do nothing, we're at the end of the LL
      else {
        //
        // advance to the next node!
        //
        this->Ptr = this->Ptr->Next;
      }
    }

    //
    // follow the iterator's pointer and
    // return the (Key, Value) pair it's
    // pointing to:
    //
    std::pair<KeyT, ValueT> operator*()
    {
      std::pair<KeyT, ValueT> defaultvalues;

      if (this->Ptr == nullptr)
        return defaultvalues;
      else
        return this->Ptr->KV_pair;
    }

    //
    // return a pointer to a (Key, Value) pair so
    // the -> operator can follow the pointer and
    // provide access to first or second in the
    // pair
    //
    std::pair<KeyT, ValueT>* operator->()
    {
      if (this->Ptr == nullptr)
        return nullptr;
      else
        return &(this->Ptr->KV_pair);
    }
  };


  //
  // Functions that work with iterators, allowing
  // users to foreach through the map, as well as
  // safely search the map without inserting pairs:
  //
public:
  //
  // begin:
  // 
  // return an iterator to the first node in the list:
  //
  iterator begin()
  {
    return iterator(this->Root);
  }

  //
  // end:
  // 
  // return an iterator denoting the end of iteration:
  //
  iterator end()
  {
    return iterator(nullptr);
  }

  //
  // find()
  // 
  // Search the map for pair containing the key, and if found
  // return an iterator to this element in the map. Otherwise
  // return the end of the iteration space.
  //
  iterator find(KeyT key)
  {
    //
    // Search for node that contains key:
    //
    NODE* cur = this->Root;

    while (cur != nullptr) {
      //
      // if we find it, return an iterator pointing to this node in LL:
      if (cur->KV_pair.first == key) {
        return iterator(cur);
      }

      // else keep searching:
      cur = cur->Next;
    }

    //
    // if get here, not found, so return iterator to end:
    //
    return end();
  }

};
