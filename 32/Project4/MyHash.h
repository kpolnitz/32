// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
//based on a resizable open hash table
#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED


template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5):numBuckets(100),m_assoc(0){
        /*
         
         The constructor must initialize your hash table, setting the size of its initial dynamic
         array to 100 buckets. The user specifies the maximum load factor of the hash table by
         passing it into the constructor, and the default maximum load factor must be 0.5 if no
         parameter is passed in. This method must run in O(B) time where B is the number of
         buckets in the table. If the user passes in a zero or negative value for the maximum load
         factor, you must use a maximum load factor value of 0.5. If the user passes in a load
         factor greater than 2, then you must use 2.0 for the maximum load factor.
         Maps anything
         */
         m_buckets = new Node * [numBuckets];
        int i = 0;
        while (i < numBuckets)
        {
            m_buckets[i] = nullptr;
            i++;
        }
        if (maxLoadFactor > 2.0)
            max_load_factor=2;
        if(maxLoadFactor <= 0)
            max_load_factor=0.5;
        else
            max_load_factor = maxLoadFactor;
        
    }
    ~MyHash(){
        cleanUp(m_buckets);                                                      //d
    }
     void reset(){
        /*
         Your hash table’s reset() method must free all of the memory associated with the current
         hash table, then allocate a new empty hash table of the default size of 100 buckets. The
         maximum load factor is unchanged. This method must run in O(B) time where B is the
         number of buckets in the table to be reset.
         */
        
        cleanUp(m_buckets);
        m_buckets = new Node * [numBuckets];
        numBuckets = 100;
        newHash();
    }
    
    void associate(const KeyType& key, const ValueType& value){                             //d
        //associates a key with a value
        //if key is already in hash table, it will be replaced
        //if doing this exceeds maximum load factor
        unsigned int hash(const KeyType&k);
        int bucket = getBucket(key);
        if (getLoadFactor() > max_load_factor)
            newHash();
        if(isItInHash(key)){
            //add another value
            ValueType * update = find(key);
            *update = value;
        }
        else {
            
            Node * n = new Node;
            n->key = key;
            n->val = value;
            //check to see if it is in the beginning of the bucket, if not, traverse the linked list
          if  ( m_buckets[bucket] == nullptr)
          {
              m_buckets[bucket] = n;
              //then put it there
              
          }
          else {
              Node *start = m_buckets[bucket];
              while (start->next != nullptr)
              {
                  start=start->next;
                  
                    //loop through
              }
              start->next = n;
              
          }
            m_assoc++;

           //create it
            
            
        }
        //int o = hash(key);
        //int index = getKey(o);
        //Node *start = m_buckets[index];
        /*
        while (start != nullptr)    //check
        {
            if (start->key==key)
            {
                //replace the current value with the new value
                start->val=value;
                return;
            }
            if (start->next == nullptr)
                break;
        }
        if (start != nullptr) {
        Node * add = new Node;    //check this implementation
        start->next = add;
        start=start->next;
        }
        start->val = value;
        start->key = key;
        m_assoc++;
         */
        //add new association
        //recompute proper locations if doing this
        //runs O(1) if number of buckets does not change
        //runs O(B) time otherwise
    }
    int getNumItems() const{                                                                //d
                //returns number of associations
        
        return m_assoc;
    }
    double getLoadFactor() const{                                                           //d
        //formula 1+(L/2)
        double numB = numBuckets * 1.0;
        //otherwise you'll get integer division
        double LF = (m_assoc/numB);
        return LF ; //more correct now
    }
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const{
        
        unsigned int b = getBucket(key);
    
        Node *start = m_buckets[b];
        ValueType * v;
        while(start != nullptr)          //we could probably make this into a helper fuction
        {                                                                                   //d
            
            if(start->key == key)
            {
                v = &(start->val);
                return v;
            }
            
            start=start->next;
        }
       
        return nullptr;
    }
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
      
    }
    
    // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
    
private:
    bool isItInHash(const KeyType& k) {
       //use the find function
        if (find(k) == nullptr)
            return false;
        return true;
    }
    //maybe an add to node function
    //every bucket needs a space for a linked list
    void newHash() {
        
        numBuckets*=2;
        Node ** temp = m_buckets;
        m_buckets = new Node * [numBuckets];

            transferHash(temp);
        delete [] temp;
 
        int i = 0;
        while (i < numBuckets)
        {
            m_buckets[i] = nullptr;
            
        }
       
    }
    
    int getBucket(const KeyType& key) const
    {
        unsigned int hash(const KeyType&k);
        int m = hash(key) % numBuckets;
        
        return m;
        
    }
    //int t_size;
    //double load_factor;
    double max_load_factor;
    int m_assoc;
    int numBuckets;
    int h_size;
    //don't we need linked list implementation?
    //next should be null until dynamicall allocated/visited
    struct Node{
        Node* next;
        KeyType key;
        ValueType val;
    };
    Node** m_buckets;
    void cleanUp(Node **p){
     
        int i = 0;
       while( i < numBuckets)
        {
            Node* cur = m_buckets[i];
            while (cur != nullptr)
            {
                Node *prev = cur;
                cur = cur->next;
                delete prev;
            }
            i++;
        }
    }

    //general function for cleaning up a hash table, need for destructor and for regular function
    unsigned int getKey(int& unconverted) const
    {
            //something like this
            return unconverted % numBuckets;
  
    }
    void transferHash(Node ** o) {
        int oldSize = numBuckets/2;
        int i = 0;
        Node * el;
        while ( i < oldSize)
        {
            
            //int z = getkey(hash(o[i]->key));
            //n[z] = o[i];
            if (o[i] == nullptr){
            m_buckets[i] = nullptr;
                i++;
             continue;
            }
            
            else {
                //copy that entire bucket to the new bucket
                el = o[i];
                while (el != nullptr)
                {
                    //put all of it in the new hash
                    associate(el->key,el->val);
                    el=el->next;
                    
                }
                
                
            }
            i++;
        }
    }
};

#endif // MYHASH_INCLUDED
