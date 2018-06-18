#include "provided.h"
//#include "rightHash.h"
#include "MyHash.h"
#include <string>
#include <map>
#include <set>
//THIS CLASS IS ALL GOOD 
using namespace std;
//you want a vector of maps, with the top being the most recent key for things
//if not found in the map and it is a letter, make it a question mark

class TranslatorImpl
{
public:
    TranslatorImpl():popTrue(0),pushTrue(0){
        map<char,char> df;
        initmap(df);
        defMap = df;
        curr = &defMap;
        //vm.push_back(df);
        //curr = &(vm.back());
        
    }
    ~TranslatorImpl(){
        
        
        
    }
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    //use a map
    //MyHash<string,map<string,string>> h;
    map<char,char> defMap;
    map<char,char> o;
    set<char>codes;
    map<char,char> * curr;
    vector<map<char,char>> vm;
    int popTrue;
    int pushTrue;
    void initmap(map<char,char>& def){
       char lbet = 'a';
        while (lbet <= 'z')
        {
            def[lbet] = '?';
            lbet++;
            
        }
        
        
        
    }
};

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    map<char,char>::iterator it1;
    char start = 'a';
    while (start <= 'z'){
        
        it1 = curr->find(start);
        o[start] = it1->second;
        
        start++;
    }
    if(ciphertext.size() != plaintext.size())
        return false;
    //see if it either contains a nonletter
    int k = 0;
    while (k < ciphertext.size())
    {
        map<char,char>::iterator it;
        set<char>::iterator it5;
        it = o.find(tolower(ciphertext[k]));
        it5 = codes.find(tolower(plaintext[k]));
       if( it != o.end())
        {
            //if it's in there and it's a different letter you wanna map to
            if(it5 != codes.end())
                return false;
            if (it->second != tolower(plaintext[k]) && it->second != '?')
                return false;
            else {
             o[tolower(ciphertext[k])] = tolower(plaintext[k]);
              
            }
            k++;
            continue;
        }
        
        k++;
    }
    codes.clear();
    char s = 'a';
    while (s <= 'z')
    {
        map<char,char>::iterator i3;
        i3 = o.find(s);
        if(i3->second != '?')
            codes.insert(i3->second);
        s++;
        
    }
    vm.push_back(o);
    curr = &vm.back();
    o.clear();
    pushTrue++;
    return true;  // This compiles, but may not be correct
}

bool TranslatorImpl::popMapping()
{
    if (popTrue >= pushTrue)
        return false;
    //otherwise take off first map
    vm.pop_back();
    if(vm.empty())
        curr = &defMap;
    else
        curr = &(vm.back());
    
    
    popTrue++;
    return true;  // This compiles, but may not be correct
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    //check in depth
    string translation;
    map<char,char>::const_iterator it;
    for (int i = 0; i < ciphertext.size(); i++)
    {
       const char d = ciphertext[i];
       it = curr->find(tolower(d));
       if (it != curr->end())
       {
        if (islower(ciphertext[i]))
          translation += it->second;
        else {
            char u = it->second;
            translation += toupper(u);
        }
       }
        
       else if(isalpha(ciphertext[i]))
           translation += '?';
       else
           translation += ciphertext[i];
           
         
        
    }
    
    return translation; // This compiles, but may not be correct
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
