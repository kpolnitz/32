// Map.h

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

// Later in the course, we'll see that templates provide a much nicer
// way of enabling us to have Maps of different types.  For now, we'll
// use type aliases.

#include <string>


using KeyType = std::string;
//using KeyType = double;

using ValueType = double;
//using ValueType = std::string;



const int DEFAULT_MAX_ITEMS = 250;


/**************CAN'T WRITE TO CIN OR COUT! *************************/



class Map
{
public:
    Map();               // Create an empty map (i.e., one with no key/value pairs)
    ~Map();
    Map&operator=(const Map &mp);
    Map(const Map &mp);
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
    // capacity and is full.
    
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
    
    
    
private:
    
    // Since this structure is used only by the implementation of the
    // Map class, we'll make it private to Map.
    
    struct Pair
    {
        KeyType   m_key;
        ValueType m_value;
    };
    //Node *m_data;
    //Pair m_data[DEFAULT_MAX_ITEMS];  // the pairs in the map
    int  m_size;                     // number of pairs in the map
    
    // At any time, the elements of m_data indexed from 0 to m_size-1
    // are in use.
    
    int find(const KeyType& key) const;
    // Return index of the pair in m_data whose m_key == key if there is
    // one, else -1
    
    bool doInsertOrUpdate(const KeyType& key, const ValueType& value,
                          bool mayInsert, bool mayUpdate);
    // If the key is not present in the map and if mayInsert is true, insert
    // the pair if there is room.  If the key is present and mayUpdate is
    // true, update the pair with the given key.
    
    struct Node {
        Pair p;
        Node* next=NULL;
        Node* previous;
        
        
    };
    Node* head;
    Node* tail;
    
    
};

// Inline implementations

inline
int Map::size() const
{
    return m_size;
}

inline
bool Map::empty() const                                                                 //DONE
{
    
if (head == nullptr)
    return true;
    
    return false;
}

inline
bool Map::contains(const KeyType& key) const                                            //DONE
{
    
    Node *temp;
    temp = head;
    //iterate through the pointers and see if you can find it
    while (temp != nullptr)
    {
        if (temp->p.m_key == key)
            return true;
    
        temp=temp->next;
    }
    return false;
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

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);



#endif // MAP_INCLUDED
