
#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//can't use map, unordered map
class DecrypterImpl
{
public:
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    Translator t;
    bool allQs(string q) {
        for (int i = 0; i < q.size(); i++)
        {
            if (q[i] != '?')
                return false;
        }
        return true;
    }
    bool fullyUntranslated (vector <string> h) {
        for (int f = 0; f < h.size(); f++)
        {
            int g = 0;
            while (g < h[f].size())
            {
                if (h[f][g] == '?')
                    break;
                g++;
            }
            if (g != h[f].size())
                return false;
        }
        return true;
    }
    WordList w1;
    bool noBadWords(vector <string> o)
    {
        for (int i = 0; i < o.size(); i++)
        {
            if (!w1.contains(o[i]))
                return false;
        }
        return true;
    }
    vector<string> candidates;
    string acceptable;
    string findBiggest(vector<string> h) {
        int mostchar = 0;
        int mostpos = 0;
        int numchars;
        
        for (int l = 0; l < h.size(); l++)
        {
           
            numchars = numberUntranslated(h[l]);
            if (numchars > mostchar)
            {
                mostchar = numchars;
                mostpos = l;
            }
            
        }
        return h[mostpos];
    }
    bool strangeCharacters(string ciphertext) {
        
        int e = 0;
        int f = 0;
        //make sure the message doesn't have any strange characters
        while (e < ciphertext.size()) {
            
            if (!isalpha(ciphertext[e])) {
                
                while(f < acceptable.size()) {
                    if (ciphertext[e] == acceptable[f])
                        break;
                    f++;
                }
                if (f == acceptable.size())
                    return false;
            }
            e++;
            
        }
        return true;
    }
    string Crack (vector<string> output, string message) {
        //tokenize inside
      
        Tokenizer tn(acceptable);
       
        //we just need to put in a translation
        vector<string> WordsToCrack = tn.tokenize(message);
        vector<string> TransToCrack;
        
        for(int c = 0; c < WordsToCrack.size(); c++)
        {
            
            TransToCrack.push_back(t.getTranslation(WordsToCrack[c]));
        }
        //there should be a default to have question marks
        
        
        if (fullyUntranslated(WordsToCrack))
        {

        }
        else {
            for(int d = 0; d < WordsToCrack.size(); d++)
            {
                
                TransToCrack.push_back(WordsToCrack[d]);
            }
            
            
        }
         
//        string biggest = findBiggest(TransToCrack);
//
//        if (allQs(biggest)) {
//        for(int d = 0; d < WordsToCrack.size(); d++)
//        {
//            if(t.getTranslation(WordsToCrack[d])==biggest)
//            {
//                biggest = WordsToCrack[d];
//                break;
//            }
//        }
//        }
//        vector<string> possibleEWords = w1.findCandidates(biggest, t.getTranslation(biggest));
//        vector <string> tWords;
//
//        if (!t.pushMapping(biggest, possibleEWords.back()))
//            return "";
//        if(t.getTranslation(message) == message)
//        {
//            possibleEWords.pop_back();
//            if(!t.popMapping())
//                return "";
//            if (!t.pushMapping(biggest, possibleEWords.back()))
//                return "";
//        }
//        //retokenize
//        message = t.getTranslation(message);
//        WordsToCrack = tn.tokenize(message);
//        tWords = fullyTransWords(WordsToCrack);
        
  
        
//        if (!noBadWords(tWords))
//        {
//
//            if (!t.popMapping())
//                return "";
//            message = t.getTranslation(message);
//            return Crack(output, message);
//        }
//        else {
//            if ( tWords.size()== WordsToCrack.size())
//            {
//
//                //you found a solution
//                output.push_back(message);
//                if (!t.popMapping())
//                    return "";
//                message = t.getTranslation(message);
//                return Crack(output, message);
//                //pop most recent translation
//                //use this map to make another message
//                //Crack(output, message);
//
//            }
//
//            return Crack(output, message);
       // }


       // if (noBadWords(fullyTranslated))
       //     return Crack(output, message);

        //loop through the tokenizer list, words to crack list

        //check if any are fully translated, maybe have a vector
        
        //go through each word in the vector and see if it is a valid word
        //the moment we see one is not a valid word, we return with a popped vector list
        //if not, go onto next word in the new vector

        return "";
    }
    bool fullytranslated(string translation) {
        //checks if a word is fully transalted
        for (int z = 0; z < translation.size(); z++) {
           if (translation[z] == '?')
               return false;
        }
        return true;
    }
   
   
    int numberUntranslated(string translation) {
        int num = 0;
        int s = 0;
        //finds untranslated chars
        while (s < translation.size())
        {
            if (translation[s] == '?')
                num++;
            s++;
        }
        return num;

    }
    vector <string> fullyTransWords (vector <string> potWords) {
        vector <string> fulwords;
        for (int a = 0; a < potWords.size(); a++)
        {
            if (fullytranslated(potWords[a]))
                fulwords.push_back(potWords[a]);
   
        }
         return fulwords;
    }
};

bool DecrypterImpl::load(string filename)                                                     //d?
{
    return (w1.loadWordList(filename)); // This compiles, but may not be correct
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{    //we will break it up
    //get all the characters that are not:
    acceptable = " ,;:.!()[]{}-\"#$%^&";
    Tokenizer tn(acceptable);
    vector <string> possibleSolns;
    if (!strangeCharacters(ciphertext))
        return possibleSolns;
        
    //vector <string> wordsToCrack = tn.tokenize(ciphertext);
    //look for words with the most untranslated characters
    string ctext;
   //go through the words
    //with a candidate, proceed with translation
   ctext = Crack(possibleSolns, ciphertext);
  
    //the moment one of the fully translated words isn't in the word list, go to the next word
    //if fully translated
    //  is it a word
    //  if it is keep  going until all the words are valid words, with current map
    //      keep using other english words to crack the message
    //      if all of the words become fully translated words, pop the map and do other translations again!
    //  if not move on


    sort(possibleSolns.begin(),possibleSolns.end());
    //sort the answers alphabetically
    return possibleSolns;  // This compiles, but may not be correct
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
    return m_impl->crack(ciphertext);
}

