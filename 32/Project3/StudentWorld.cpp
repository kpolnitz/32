
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Actor.h"

using namespace std;

double StudentWorld::randDouble(double par1, double par2)
{
    //type cast?
    double r = (double)rand() / RAND_MAX;
    double ret = abs(par1 + r*(par1-par2));
    if (ret < .05 || ret > .5)
        return .1;
    return ret;
}



GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir),d(0),totalNumDestroyed(0),currNumShips(0), count(0)
{
}

int StudentWorld::init()
{


    nBlaster = new Nachenblaster;
    nBlaster->setWorld(this);
 
    int j;
    for (j = 0; j < 30; j++)
    {
    Star *s = new Star(IID_STAR,randInt(0, 255),randInt(0, 255),0,randDouble(.05, .5),3);
    s->setWorld(this);
    a.push_back(s);
    }
    
 
    //a.push_back(sg[1]);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    s1 = 60;
    maxNumShips = 4 + (.5 * getLevel());
    
    s2 = 20 + getLevel()*5;
    s3 = 5 + (getLevel()*10);
    
    s = s1 + s2 + s3;

    if (count < maxNumShips )
    {
        
        shipProbability();
        count++;
    }
    

    totalNumRemaining = 6 + (4*getLevel()) - totalNumDestroyed;

    ostringstream oss;

    //Project 3 Tings ---------------------------------
    
    //ostringstream oss;
    //don't forget the library
    //oss << "trevor";
    //oss - like a string buffer, you can dump strings into it
    oss << "Lives:  ";
    oss << getLives();
    //NOT RIGHT
    oss << "  Health:  ";
    
    oss << (nBlaster->getHitPts()*100)/50;
    oss << "%  ";
    oss << "Score:  ";
    oss << getScore();
    oss << "  Level:  ";
    oss << getLevel();
    oss << "  Cabbages:  ";
    oss << (nBlaster->getCabbagePts()*100)/30;
    oss << "%  ";
    oss << "Torpedoes:  ";
    oss << nBlaster->getTCount();
    //that will produce " ___tr"
    //I want you tuo put five characters into the string
    //oss << left << setw(5) << "tr";
    //this will move the automatic spaces to the right (will put "tr___")
    //oss << left << fill('*') << setw(5) << "tr";
    //will produce "tr***"
    string text = oss.str();
    setGameStatText(text);
    //ask  everything to do something
    //delete anything dead
    //update text
    //probably recursive
    //if player advanced
    //int i;
    //if (currNumShips < min(maxNumShips,totalNumRemaining))
    
    if (!nBlaster->isItAlive())
    {
        currNumShips = 0;
        totalNumDestroyed = 0;
        count = 0;
        return GWSTATUS_PLAYER_DIED;
    }


    nBlaster->doSomething();
    vector<Actor*>::iterator p = a.begin();
     //how many alien ships have been destroyed during the level
    
    if (!nBlaster->isItAlive())
    {
        currNumShips = 0;
        totalNumDestroyed = 0;
        count = 0;
        return GWSTATUS_PLAYER_DIED;
    }
    
    
    for (int i = 0; i < a.size();i++)
    {
    
    // if(!isDead(a[i]))
     a[i]->doSomething();
        
     if(!a[i]->isItAlive())
     {
        if (a[i]->isItAlien())
        {
            shipProbability();
    
        }
         delete *p;
         p = a.erase(p);
         continue;
     }
        p++;
        }
    
   
if(randInt(1,15) == 3)
{
  Star *t = new Star(IID_STAR, VIEW_WIDTH-1, randInt(0,255),0,randDouble(.05,.5),3);
    a.push_back(t);
}
    //some ship
    //if it reaches THAT probability
    //create one of those too
if(totalNumDestroyed == 6 + (4*getLevel()))
{
    count = 0;
    totalNumDestroyed = 0;
    playSound(SOUND_FINISHED_LEVEL);
    return GWSTATUS_FINISHED_LEVEL;
}
    
    return GWSTATUS_CONTINUE_GAME;
}

StudentWorld::~StudentWorld()
{
    //deletes the rest
    //delete nBlaster;
    
    cleanUp();
    //delete nBlaster here
}

void StudentWorld::cleanUp()
{
  
    vector<Actor*>::iterator it = a.begin();
    while (it != a.end())
    {
        
        //vector<Actor*>::iterator it3 = a.begin();
        
        if (*it != NULL)
        {
        
        delete *it;
        *it = NULL;
        it=a.erase(it);
        continue;
            
        }
        it++;
    }
    //nBlaster->setWorld(NULL);
    //if it is not equal to null delete here
    if (nBlaster != NULL)
    {
        delete nBlaster;
        nBlaster = NULL;
    }
    
}

void StudentWorld::addActor(Actor * p){
    a.push_back(p);
    
}

vector<Actor*> StudentWorld::getVec(){
    

    return a;
}

void StudentWorld::shipProbability(){
    int random = randInt(0, s);
    if (random < s1)
    {
        n = new Smallgons;
        n->setHitPts(5*(1 + ((getLevel()-1)*.1)));
    }
    else if (random < s1 + s2)
    {
        n = new Smoregons;
        n->setHitPts(5*(1 + ((getLevel()-1)*.1)));
    }
    else if (random >= s1+s2) {
        n = new Snagglegons;
        n->setHitPts(10*(1 + ((getLevel()-1)*.1)));
    }
    a.push_back(n);
    n->setWorld(this);
}

