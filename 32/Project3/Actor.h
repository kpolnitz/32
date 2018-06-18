#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <vector>
class StudentWorld;
class Cabbages;
class repairGoodies;
class Turnip;
class Torpedoes;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp




class Actor:public GraphObject {
public:
    Actor(int imageID, double startX, double startY, int dir, double size, int depth);
    virtual void doSomething()=0;
    virtual ~Actor();
    virtual bool checkCollide() {return false;}
    StudentWorld * getWorld();
    void setWorld(StudentWorld*world);
    bool isItAlive();
    void die();
    int getHitPts() {return m_hitPoints;};
    void setHitPts(int pts) {m_hitPoints = pts;}
    int getID() {return m_ID;}
    virtual bool didTheyCollide(Actor * p1, Actor * p2);
    void getDamaged(int ID);
    void setOwnership(int ID) {belongsTo = ID;}
    double euclidean_dist(double x1,double y1,double x2,double y2);
    int ownership() {return belongsTo;}
    bool isItAlien();
    bool enemyOfAlien(Actor *p);
    bool enemyOfNachenblaster(Actor *p);
private:
    StudentWorld * m_world;
    bool m_alive;
    repairGoodies * rg;
    Torpedoes *tor;
    int m_hitPoints;
    int m_ID;
    int belongsTo;
    
    
};

class Star:public Actor{
public:
    Star(int imageID, double startX, double startY, int dir, double size, int depth);
    virtual void doSomething();
    virtual ~Star();
    //virtual bool addAnother();
private:
    
    
    
};

class Nachenblaster:public Actor {
public:
    Nachenblaster();
    virtual ~Nachenblaster();
    virtual void doSomething();
    //Cabbages
    //IID_NACHENBLASTER
    //x = 0, y = 128
    //dir = 0
    //depth = 0
    //50 hit points
    //30 cabbage energy points
    //colliding with a ship destroys the ship
    //if hit points are 0, set to dead
    int getCabbagePts() {return m_cabbagePoints;};
    void fireCabbage() {m_cabbagePoints-=5;};
   
    int getTCount() {return tCount;}
    void addTorpedoes(int howMuch);
    virtual bool checkCollide();
private:
    
    int m_cabbagePoints;
    Cabbages *d;
    int tCount;
    
   
    
    
};


class Projectiles:public Actor {
public:
    Projectiles(int imageID, double startX, double startY, int dir, double size, int depth = 0, int belongsTo = 0);
    virtual ~Projectiles();
    virtual void doSomething();
    int getDir(){return m_dir;};
    

private:
    int m_dir;
    
};



class Cabbages:public Projectiles {
    
public:
    Cabbages(int imageID, double startX, double startY, int dir, double size, int depth, int belongsTo);
   

    virtual void doSomething();
    virtual ~Cabbages();
    
private:
    
    
};

class Aliens:public Actor {
public:
    Aliens(int imageID, double startX, double startY, int dir , double size , int depth, int fp, double speed):
    Actor(imageID, startX, startY, dir, size, depth), m_speed(speed), m_fp(fp),fpath(randInt(1, 3))
    {
    };
    int getSpeed() {return m_speed;}
    void setSpeed(int speed) {m_speed=speed;}
    int getFP() {return m_fp;};
    void doSomething();
    virtual bool checkCollide();
    ~Aliens() {};
    void moveInPath(int fpath);
    void setfPath(int path) {fpath = path;}
    
private:
    double m_speed;
    int m_fp; //flight plan
    int fpath; //direction
    Projectiles *t;
};

class Smallgons:public Aliens {
public:
    Smallgons();

    /*
     1. A Smallgon object must have an image ID of IID_SMALLGON.
     2. A Smallgon must always start at the proper location as passed into its constructor.
     3. A Smallgon has a direction of 0.
     4. A Smallgon has a size of 1.5.
     5. A Smallgon has a depth of 1.
     6. A Smallgon starts with exactly 5 * (1 + (current_level_number – 1) * .1) hit
     points.
     7. A Smallgon starts with a flight plan of length 0.
     8. A Smallgon starts with a travel speed of 2.0.
     */
   
    ~Smallgons() {};
  
private:
    
    
    
    
};
class Smoregons: public Aliens {
public:
    Smoregons():Aliens(IID_SMOREGON, VIEW_HEIGHT-1, randInt(0,255), 0, 1.5, 1,0,2)
    {
       
    };
    ~Smoregons() {};
    
private:
    
    
};

class Snagglegons: public Aliens{
public:
    Snagglegons():Aliens(IID_SNAGGLEGON, VIEW_HEIGHT-1, randInt(0, 255), 0, 1.5, 1,255,1.75) //change flight plan
    {
        setfPath(3);
    };
    ~Snagglegons() {};

private:
    
};

class Torpedoes:public Projectiles {
public:
    Torpedoes(double startX, double startY, int dir, int belongsTo):Projectiles(IID_TORPEDO,startX,startY,dir,0.5,1,belongsTo) {};
    ~Torpedoes() {};
    virtual void doSomething();
private:
    int m_Torpedoes;
    
};

class Turnip:public Projectiles {
public:
    Turnip(double startX,double startY):Projectiles(IID_TURNIP, startX,startY,0,.5,1,IID_SMOREGON) {};
    ~Turnip() {};
private:
   
    
    
};


class Explosions:public Actor {
public:
    //in same position as the alien ship that was just destroyed
    Explosions(double startX, double startY):
    Actor(IID_EXPLOSION, startX, startY, 0, 1.0,0),m_NumTicks(4)
    {};
    void doSomething();
    ~Explosions() {};
private:
    int m_NumTicks;
};

class Goodies: public Actor {
public:
    Goodies(int imageID, double startX = 0, double startY = 0, int dir = 0, double size = 1.0, int depth = 0):
    Actor(imageID, startX, startY, dir, size,depth)
    {};
    void doSomething();
    virtual void reward()=0;
    ~Goodies() {};
private:
    
    
};

class repairGoodies: public Goodies {
public:
    //gives the nachenblaster an extra 10 points, up to a max of 50 hit points
    repairGoodies(double startX, double startY):Goodies(IID_REPAIR_GOODIE, startX,startY,0,0.5,1) {};
    ~repairGoodies() {};
    virtual void reward();
private:
    
};

class lifeGoodies: public Goodies {
public:
    lifeGoodies(double startX, double startY):Goodies(IID_LIFE_GOODIE, startX,startY,0,0.5,1) {};
    ~lifeGoodies() {};
    virtual void reward();
private:
    
  
    
};


class torpedoGoodies: public Goodies {
public:
    torpedoGoodies(double startX, double startY):Goodies(IID_TORPEDO_GOODIE, startX,startY,0,0.5,1) {};
    ~torpedoGoodies() {};
    virtual void reward();
   
private:
    
};


#endif // ACTOR_H_
