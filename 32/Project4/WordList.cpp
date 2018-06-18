//#include "rightHash.h"
#include "MyHash.h"
#include "provided.h"
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
//CHECK FOR CASE SENSITIVITY
class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    string lowerEverything (string l) const {
        string o = l;
        for (int z = 0; z < l.size(); z++)
        {
            o[z] = tolower(l[z]);
            
        }
        return o;
    }
 MyHash <string,vector<string>> h;
    char start = '0';
    string makeAPattern(string word) const {                                //TEST
    //make a 2d array
    string pattern;
    char mapped[26];
    char replacements[26];
    char start = '0';
    int i = 0;
    int j = 0;
    
    while (i < word.size())
    {
      bool found = false;
      while (j < i)
      {
          if (mapped[j] == word[i])
          {
            //use the mapping with that index
              mapped[i] = word[i];
              replacements[i] = replacements[j];
              pattern += replacements[i];
              found = true;
              break;
              
          }
          
          j++;
      } j = 0;
       if (!found)
       {
           mapped[i]=word[i];
           replacements[i] = start;
           pattern += replacements[i];
           start++;
       }
        
        
        i++;
    }
        

    return pattern;
}
    bool isGoodCandidate(string word, string currTrans) const
    {
        //checks if it is a good translation
        //go to the right translation
        //then look at the real words for the real translations
        for (int i = 0; i < word.size(); i++)
        {
            if (currTrans[i] == '?')
                continue;
            if (word[i] != currTrans[i])
                return false;
        }
        return true;
    }
};



bool WordListImpl::loadWordList(string filename)
{
    //a pattern should have a vector of words with the same patttern
    //check to see if you can find the word in the hash
    //if not, you would insert it
    h.reset();
    string s;
    string pattern;
    ifstream ifs(filename);
    
    if(ifs){
        string line;
        //to get every line
        
        
        while (getline(ifs,line)) //be false when eof is called
        {

            bool validWord = true;
            int i = 0;
           if(contains(line))
               continue;
            while (i < line.size())
                   {
                       //cerr << "Looking at " << line[i] << endl;
                       if (!isalpha(line[i]) && line[i] != '\'') {
                           validWord = false;
                           break;
                       }
                       i++;
                       
                   }
            if (validWord)
            {
                vector <string> passIn;

                //unsigned int hash(const string& k);
                //int k = hash(line);
                pattern = makeAPattern(lowerEverything(line));

                cerr << "Let me know! It's " << line << endl;
                vector <string> * temp = h.find(pattern);
              if (temp != NULL)
              {
                temp->push_back(lowerEverything(line));
                h.associate(pattern,*temp);
              }
              else
              {
                passIn.push_back(lowerEverything(line));
                h.associate(pattern, passIn);
              }
               
            }
        }
        
        return true;
    }
    return false;  // This compiles, but may not be correct
}

bool WordListImpl::contains(string word) const
{
    unsigned int hash(const string& k);
    string thepatt;
    thepatt = makeAPattern(word);
    if (h.find(thepatt) != NULL)
    {
        const vector <string> * it = h.find(thepatt);
        //look through the vector
        int i = 0;
        while (i < it->size())
        {
            if ((*it)[i] == word)
                return true;
            i++;
        }
        
    }
    return false; // This compiles, but may not be correct
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string>candidates;
    //this is gonna return the words with the same pattern that are consistent;
    if (cipherWord.size() != currTranslation.size())
        return candidates;
    //check for valid string
    //check for valid candidates
    string patt = makeAPattern(lowerEverything(cipherWord));
    const vector <string> *lookthru = h.find(patt);

    if (lookthru == NULL)
        return candidates;
    int i = 0;
    while (i != lookthru->size())
    {
        cerr << "Looking at " << (*lookthru)[i] << endl;
     if (isGoodCandidate((*lookthru)[i],currTranslation))
         candidates.push_back((*lookthru)[i]);
    //it->next;
        i++;
    }
    return candidates;  // This compiles, but may not be correct

}


//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
    return m_impl->findCandidates(cipherWord, currTranslation);
}
