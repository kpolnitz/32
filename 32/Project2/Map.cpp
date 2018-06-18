// Map.cpp

#include "Map.h"


/********************************MAKE SURE TO COMMENT!!********************************/
/**************CAN'T WRITE TO CIN OR COUT! *************************/

Map::Map()
: m_size(0)
{
    //delete data underneath, and then iterate through and set everything to null
    head = NULL;
    tail= NULL;
    
    
    //Pair p; --- accounted for in the Map Class
}

Map::~Map(){                                                                                //DONE
  //When a Map is destroyed, the nodes in the linked list must be deallocated.
  //delete and point to null
    Node *u = head; //we will use this to go through and delete things in the array
    
    while(u != NULL)
    {
        //head and tail will ultimately lose their values underneath
        Node *nextu = u->next;
        delete u;
        u = nextu;
        head=u; //make sure everything is set to null, no leaks
        
    }
    tail=u;
    
   
}

Map::Map(const Map &mp){                                                                    //DONE
    //When a brand new Map is created as a copy of an existing Map, enough new nodes must be allocated to
    //hold a duplicate of the original list.
    //we want to take the data from mp and make a new map
    //retrive the value, put it in the map
    //Maps can access each others privates
    int y = 0;
    KeyType k;
    ValueType v;        //we want to add things, start at null
    head=NULL;
    tail=NULL;
    m_size=0; //initialize or it will be random
    while (y < mp.size())
    {
        
        mp.get(y,k,v); //retrieve values and put it into this map
        insert(k, v);
        
        y++;
        
    }
    
    
}

Map& Map::operator=(const Map &mp)   {                                                      //DONE
    /*
     
     When an existing Map (the left-hand side) is assigned the value of another Map (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).
     */
    
    //NO MEMORY LEAKS *CHECK*
    if (&mp == this)
        return *this;
    
    Map tempArr(mp); //take and eventually switch all the values
    swap(tempArr); //you can't pass in mp because it cannot be changed
    
    
    return *this;
}
bool Map::erase(const KeyType& key)                                                         //DONE
{
    Node* current;
    int pos = find(key);
    if (pos == -1)  // not found
        return false;
    
    for(current=head; current != NULL; current=current->next)
    {
            if (current->p.m_key==key)
            {
                if(m_size == 1)    //if the only piece, just set everything to default
                {
                    delete head;
                    head=NULL;
                    tail=NULL;
                    break;
                    
                }
                if(current==head)
                {
                    head=current->next;         //delete and change the head
                    delete current;
                    break;
                }
                if(current==tail)               //delete and set the tail to previous node
                {
                    Node* temp;
                    temp=current->previous;
                    delete tail;
                    tail=NULL;
                    tail=temp;
                    tail->next=NULL;
                    break;
                    
                    
                }
                else
                {                                   //otherwise connect the previous and next node
                    
                    Node *atemp=current->previous;
                    Node *anotherTemp=current->next;
                    atemp->next=anotherTemp;
                    anotherTemp->previous=atemp;
                    delete current;
                    break;
                    
                    
                }
                
            }
    }
    
    // Move last array item to replace the one to be erased
 
    m_size--;
    
    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const                                   //DONE
{
    Node *u;
    u=head;
    int pos = find(key);
    if (pos == -1)  // not found
        return false;                           //iterate until you get to the key/value
    int k = 0;
    while (k < pos)
    {
        u=u->next;
        k++;
    }
    value = u->p.m_value;
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const                                      //DONE
{
    Node *z=head;
    if (i < 0  ||  i >= m_size)
        return false;
    int iterator=0;
    while (iterator < i)                    //same iteration, similar to above
    {
        z=z->next;
        iterator++;
    }
    key = z->p.m_key;
    value = z->p.m_value;
    return true;
}

void Map::swap(Map& other)                                                                      //DONE
{
    //all we need to truly do is switch the head and tail pointers of the linked lists
    Node *unswappedHead = head;
    Node *unswappedTail = tail;
    Node *otherHead = other.head; //refers to the map we are currently in
    Node *otherTail = other.tail; //other
    //Note to self:see my function
    
    head = otherHead;
    tail = otherTail;
    other.head=unswappedHead;
    other.tail=unswappedTail;
    // Swap elements.  Since the only elements that matter are those up to
    // m_size and other.m_size, only they have to be moved.
    
    // Swap sizes
    //swap the beginner pointers, switch sizes
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
}

int Map::find(const KeyType& key) const                                                     //DONE
{
    Node *s;
    s=head; 
    int pos=0;
    // Do a linear search through the array.
    
    while (s != NULL && (pos < m_size)) //iterator pos number of times
    {
        if(s->p.m_key == key)
            return pos;
        pos++;
        s=s->next;
    }
    return -1;
}

bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value,
                           bool mayInsert, bool mayUpdate)                                  //DONE
{
    //we want to make a box and insert the values into it
    Node *q = new Node;
    int pos = find(key);
    if (pos != -1)  // found
    {
        if (mayUpdate)
        {
            //look through and see if we can find the value to update.
            for (q = head; q != NULL; q=q->next)
            {
                if(q->p.m_key==key)
                {
                    //then set the value
                    q->p.m_value=value;
                    return mayUpdate;
                }
            }
        }
        return mayUpdate;
    }
    if (!mayInsert)  // not found, and not allowed to insert
        return false;
    if (m_size == DEFAULT_MAX_ITEMS)  // no room to insert
        return false;
    if (this->empty())
    {
        head=q;             //point everything to the one node
        tail = q;
        
    }
    q->previous=tail;               //add to tail, set last node as tail
    (q->previous)->next=q;
    q->p.m_key = key;
    q->p.m_value = value;
    q->next=NULL;
    tail=q;
    
    
    m_size++;
    return true;
}

bool combine(const Map& m1, const Map& m2, Map& result){                                        //DONE
    bool didItCombine = false;
    
  /*
   When this function returns, result must consist of pairs determined by these rules:
   
   If a key appears in exactly one of m1 and m2, then result must contain a pair consisting of that key and its corresponding value.
   If a key appears in both m1 and m2, with the same corresponding value in both, then result must contain exactly one pair with that key and value.
   When this function returns, result must contain no pairs other than those required by these rules. (You must not assume result is empty when it is passed in to this function; it might not be.)
   
   If there exists a key that appears in both m1 and m2, but with different corresponding values, then this function returns false; if there is no key like this, the function returns true. Even if the function returns false, result must be constituted as defined by the above rules.
   */
    
    Map aResult(m2);
    
    ValueType m1value;
    ValueType m2value;
    KeyType   m1key;
    didItCombine = true;
    int i;
    for (i = 0; i < m1.size(); i++)
    {
        m1.get(i,m1key,m1value);                    //take m2 as map to edit/add
        if(aResult.contains(m1key))
        {
            aResult.get(m1key, m2value);
            if(m1value!=m2value)
            {
                aResult.erase(m1key);
                didItCombine=false;
            }
            continue;
        }
        aResult.insert(m1key, m1value);
    }
    
    result.swap(aResult);                       //make result the edited node
    return didItCombine;
}

void subtract(const Map& m1, const Map& m2, Map& result){                                     //DONE
    
    /*
     
     When this function returns, result must contain one copy of all the pairs in m1 whose keys don't appear in m2; it must not contain any other pairs. (You must not assume result is empty when it is passed in to this function; it may not be.
     */
    Map tempResult(m1);
    
    ValueType m2value;
    KeyType   m2key;

    int j;
    for(j = 0; j < m2.size(); j++)
    {
        m2.get(j,m2key,m2value);                //subtract from m1 edited temp array
        if (tempResult.contains(m2key))
        {
            tempResult.erase(m2key);
        }
        
    }
    tempResult.swap(result);                    //make result the edited array
    
}







