// Map.h

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

using KeyType = int;
using ValueType = double;

class Map
{
  public:
    Map();               // Create an empty map (i.e., one with no key/value pairs).

    bool empty() const;  // Return true if the map is empty, otherwise false.

    int size() const;    // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that either the key is already in the map, or the map has a fixed
      // capacity and is full.

    bool update(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that the key is not already in the map and the map has a fixed
      // capacity and is full).

    bool erase(const KeyType& key);
      // If key is equal to a key currently in the map, remove the key/value
      // pair with that key from the map and return true.  Otherwise, make
      // no change to the map and return false.
     
    bool contains(const KeyType& key) const;
      // Return true if key is equal to a key currently in the map, otherwise
      // false.
     
    bool get(const KeyType& key, ValueType& value) const;
      // If key is equal to a key currently in the map, set value to the
      // value in the map that that key maps to and return true.  Otherwise,
      // make no change to the value parameter of this function and return
      // false.
     
    bool get(int i, KeyType& key, ValueType& value) const;
      // If 0 <= i < size(), copy into the key and value parameters the
      // key and value of one of the key/value pairs in the map and return
      // true.  Otherwise, leave the key and value parameters unchanged and
      // return false.

    void swap(Map& other);
      // Exchange the contents of this map with the other one.

      // Housekeeping functions
    ~Map();
    Map(const Map& other);
    Map& operator=(const Map& rhs);

  private:
      // Representation:
      //   a circular doubly-linked list with a dummy node.
      //   m_head points to the dummy node.
      //   m_head->m_prev->m_next == m_head and m_head->m_next->m_prev == m_head
      //   m_size == 0  iff  m_head->m_next == m_head->m_prev == m_head
      //   If m_size > 0
      //       m_head->next points to the node at position 0.
      //       m_head->prev points to the node at position m_size-1.
      //   Nodes are in no particular order.

    struct Node
    {
        KeyType   m_key;
        ValueType m_value;
        Node*     m_next;
        Node*     m_prev;
    };

    Node* m_head;
    int   m_size;

    Node* find(const KeyType& key) const;
      // Return pointer to Node whose m_key == key if there is one, else m_head

    bool doInsertOrUpdate(const KeyType& key, const ValueType& value,
                          bool mayInsert, bool mayUpdate);
      // If the key is not present in the map and if mayInsert is true, insert
      // the pair if there is room.  If the key is present and mayUpdate is
      // true, update the pair with the given key.
};

// Declarations of non-member functions

bool combine(const Map& m1, const Map& m2, Map& result); 
      // If a key/value pair occurs in m1 or m2 or both, then it will occur in
      // result upon return from this function.  Return true unless m1 and m2
      // have a pair with the same key but different values; neither such pair
      // will occur in result upon return.

void subtract(const Map& m1, const Map& m2, Map& result); 
      // Upon return, result contains those pairs in m1 whose keys don't
      // appear in m2.

// Inline implementations

inline
int Map::size() const
{
    return m_size;
}

inline
bool Map::empty() const
{
    return size() == 0;
}

inline
bool Map::contains(const KeyType& key) const
{
    return find(key) != m_head;
}

inline
bool Map::insert(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, true /* insert */, false /* no update */);
}

inline
bool Map::update(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, false /* no insert */, true /* update */);
}

inline
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, true /* insert */, true /* update */);
}

#endif // MAP_INCLUDED
