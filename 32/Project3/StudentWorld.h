#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
class Actor;
class Nachenblaster;
class Smallgons;
class Smoregons;
class Aliens;
class Snagglegons;
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void addActor(Actor * p);
    Nachenblaster * getNBlaster() {
        return nBlaster; //getting an access error here
    }
    vector <Actor*> getVec();
    void addDestruction() {totalNumDestroyed+=1;}
    void shipProbability();
    

private:
    vector<Actor*> a;
    Nachenblaster *nBlaster;
    
    Snagglegons * sng;
    double randDouble(double par1, double par2);
    Aliens *n;
    int d; //number of aliens killed in round
    int totalNumDestroyed;
    int totalNumRemaining;
    int maxNumShips;
    int currNumShips;
    int s1,s2,s3,s;
    int count; 
};

#endif // STUDENTWORLD_H_
