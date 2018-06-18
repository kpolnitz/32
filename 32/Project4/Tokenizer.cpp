#include "provided.h"
#include <string>
#include <vector>
using namespace std;
//THIS CLASS IS ALL GOOD
class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    string separateThem;
};

TokenizerImpl::TokenizerImpl(string separators):separateThem(separators)
{
    
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    vector<string>tokens;
                                                 //something is wrong with this
    int i=0,j=0;
    char start = s[0];
    int sindex = 0;
    string sub;
    while(i < s.size())
    {
        char current = s[i];
        while(j < separateThem.size())
        {
            if (s[i] == separateThem[j]) {
                sub = s.substr(sindex,i-sindex);
                if (sub != "")
                    tokens.push_back(sub);
                
                start = s[i+1];
                sindex = i+1;
                
                break;
            
               
            }
            j++;
        }
        j=0;
        i++;
    }
    
    sub = s.substr(sindex,i-sindex);
    if (sub != "")
        tokens.push_back(sub);
    return tokens;
    //return vector<string>();  // This compiles, but may not be correct
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
