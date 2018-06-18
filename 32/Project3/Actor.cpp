 #include "Actor.h"
#include "StudentWorld.h"






// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth):
GraphObject(imageID, startX, startY, dir, size, depth),m_ID(imageID)
{
    m_alive = true;
}
Actor::~Actor()
{}

bool Actor::isItAlive() {
    return m_alive;
}

void Actor::die() {
    m_alive=false;
    
}

Star::Star(int imageID, double startX, double startY, int dir, double size, int depth)
:Actor(imageID, startX, startY, dir, size, depth)
{
    //cerr << "here in the constructor of star" << endl;
}

StudentWorld* Actor::getWorld() {
    return m_world;
}

void Actor::setWorld(StudentWorld *world)
{
    m_world = world;
}

double Actor::euclidean_dist(double x1,double y1,double x2,double y2){
    double dist;
    //want to do like pythagorean theorem
    dist = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    return dist;
}

bool Actor::didTheyCollide(Actor * p1, Actor * p2) {
   //calculate radius
    int r1 = p1->getRadius();
    int r2 = p2->getRadius();
    
    if(euclidean_dist(p1->getX(),p1->getY(), p2->getX(), p2->getY()) < .75 * (r1 + r2))
        return true;
    
    return false;
}

Star::~Star(){}
void Star::doSomething() {
    //move to the left until x <= 1
    //then set to dead
    if(getX() <= -1)
        die();
    
    
    moveTo(getX()-1, getY());
}

Nachenblaster::Nachenblaster():Actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0),tCount(0)
{
    
    setHitPts(50);
    m_cabbagePoints = 30;
}

Nachenblaster::~Nachenblaster(){}

void Nachenblaster::doSomething() {

//return;
    if(!isItAlive())
        return;
    checkCollide();
    if(!isItAlive())
        return;

int c;
    //StudentWorld *s;

if(getWorld()->getKey(c))
{
//hit a valid key
//if x<0 >= VIEW_WIDTH/y<0, >= VIEW_HEIGHT

 switch (c)
 {
     case KEY_PRESS_UP: {
 if(getY() >= VIEW_HEIGHT)
     return;
    moveTo(getX(), getY()+6);
 //move up
         break;
     }
     case KEY_PRESS_DOWN: {
 if(getY() <= 0)
 return;
 moveTo(getX(), getY()-6);
 //move down
 break;
     }
 case KEY_PRESS_LEFT:
     {
 if(getX() <= 0)
 return;
 moveTo(getX()-6, getY());
 //move left
 break;
     }
 case KEY_PRESS_RIGHT:
     {
 if(getX() >= VIEW_WIDTH)
 return;
 moveTo(getX()+6, getY());
 //move right
 break;
     }
     case KEY_PRESS_TAB: {
         if (getTCount() > 0) {
 Torpedoes *f = new Torpedoes(getX()+12, getY(),0,IID_NACHENBLASTER);
 addTorpedoes(-1);
 getWorld()->playSound(SOUND_TORPEDO);
         getWorld()->addActor(f);
         }
    break;
     }
 //f->moveTo(getX()+12, getY());
 //f ->setDirection(0);
 //.push_back(f);
 //added 12 pixels to the right
 //direction of 0 degrees
 
case KEY_PRESS_SPACE: {
 if(getCabbagePts() >= 5)
 {
 getWorld()->playSound(SOUND_PLAYER_SHOOT);
 fireCabbage();
 d = new Cabbages(IID_CABBAGE,getX()+12,getY(),0,.5,1,IID_NACHENBLASTER);
 getWorld()->addActor(d);
 //cabbage added 12 pixels to the right
 //starting direction of 0 degrees
 //Cabbages *p = new Cabbages;
 //p->setDirection(0);
 //p->moveTo(getX()+12,getY());
 }
 break;
     }
 }
}
   if (m_cabbagePoints < 30)
    m_cabbagePoints++;
}

void Nachenblaster::addTorpedoes(int howMuch){
    tCount += howMuch;
}

Projectiles::Projectiles(int imageID, double startX, double startY, int dir, double size, int depth,int belongsTo):
Actor(imageID, startX, startY, dir, size,depth),m_dir(dir)
{
    setOwnership(belongsTo);
};

Projectiles::~Projectiles()
{}

Cabbages::Cabbages(int imageID, double startX, double startY, int dir, double size, int depth,int belongsTo):
Projectiles(imageID, startX, startY,dir,size,depth,belongsTo)
{
    
    /*
     1. A cabbage object must have an image ID of IID_CABBAGE.
     2. A cabbage must have its x,y location specified for it – the NachenBlaster that fires
     the cabbage must pass in this x,y location when constructing a cabbage object.
     3. A cabbage has an initial direction of 0.
     4. A cabbage has a size of .5.
     5. A cabbage has a depth of 1.
     */
    
}

Cabbages::~Cabbages()
{}

void Cabbages::doSomething() {
    if(!isItAlive())
       return;
    if (getX() >= VIEW_WIDTH)
    {
        die();
        return;
    }
//see if it collided with an alien ship (Euclidian)
//if it did, damage the victim
    //die();
    moveTo(getX()+8, getY());
    setDirection(getDirection()+20);
    //check for collision
    
}

void Aliens::doSomething()
{
    if(!isItAlive())
        return;
    checkCollide();
    if(!isItAlive())
        return;

 /*
    If the player is in my line of sight, then
    Fire a turnip in the direction of the player
    Else if I still want to continue moving in the current direction
    Move one pixel in my current direction
    Decrement the number of remaining ticks to move in this direction
    Else if I want to choose a new direction
    Pick a new direction to move, and pick how many ticks to move
    in that direction.
 */

    //if it runs into a barrier, we move
    
    
    if(getY() >= VIEW_HEIGHT-1 || getY() <= 0)
    {
        if(getY() >= VIEW_HEIGHT-1)
        {
            fpath=3;
        }
        else
            fpath = 2;
        
    }
    
    if(m_fp==0)
    {
        fpath = randInt(1, 3);
        m_fp = randInt(1, 32);
    }
        //must bounce down and left
        
    moveInPath(fpath);
    m_fp--;
       //down and left
       //up and left
       //due left
    int prob = -1;
    
                    //fire turnip
                    //or torpedo
                    if(getID()==IID_SNAGGLEGON)
                    {
                        if(getWorld()->getNBlaster()->getX() < getX() && getY() - getWorld()->getNBlaster()->getY() <= 4 && getY() - getWorld()->getNBlaster()->getY() >=-4) {
                            prob = (15/getWorld()->getLevel())+10;
                            if(randInt(1,prob)==1)
                            {
                                t = new Torpedoes(getX()-14,getY(),180,IID_SNAGGLEGON);
                                getWorld()->addActor(t);
                                getWorld()->playSound(SOUND_TORPEDO);
                            }
                        }                     
                    }
                    else
                    {
                        prob = ((20/getWorld()->getLevel())+5);
                        if(getWorld()->getNBlaster()->getX() < getX() && getY() - getWorld()->getNBlaster()->getY() <= 4 && getY() - getWorld()->getNBlaster()->getY() >=-4) {
                        if (randInt(1,prob)==1)
                        {
                            
                        t = new Turnip(getX()-14,getY());
                        getWorld()->playSound(SOUND_ALIEN_SHOOT);
                        getWorld()->addActor(t);
                        
                        }
                        if (getID()==IID_SMOREGON) {
                            if (randInt(1,prob)==1)
                                {
                            //change flight plan to due left
                            fpath = 1;
                            m_fp = VIEW_WIDTH;
                            //set flight plan to length of VIEW_WIDTH
                            setSpeed(5);
                            
                                }
                        }
                        }
                    }

    if(getX() < 0)
    {
        die();
    }
  
  
}




Smallgons::Smallgons():Aliens(IID_SMALLGON, VIEW_WIDTH-1, randInt(0,255), 0, 1.5,1,0,2)
{
    
    //
    //Actor::setHitPts(newHP);
}

void Projectiles::doSomething(){
    //check for collisions
    if(getX() <= -1 || getX() >= VIEW_WIDTH)
    {
        die();
        return;
    }
        if (getID()==IID_TURNIP)
            setDirection(getDirection()+20);
        moveTo(getX()-6, getY());
}

void Torpedoes::doSomething(){
    //check for collisions
    if(getX() <= -1)
    {
        die();
        return;
    }
    if(getDir()==180)
    moveTo(getX()-8, getY());
    else
    moveTo(getX()+8, getY());
    
    
}

void Explosions::doSomething(){
    //increase size
    setSize(getSize()*1.5);
    m_NumTicks--;
    if(m_NumTicks == 0)
        die();
    //if tick is in 4th iteration, set to dead
    //die();
}
//COLLISIONS - PAGE 10
void Goodies::doSomething() {
    
    if(!isItAlive())
        return;
    if(getX() < 0 || getY() >= VIEW_HEIGHT || getY() < 0)
    {
        die();
        return;
    }
    //if it collides with nBlaster
    //DIDITCOLLIDE FUNCTION
    if(didTheyCollide(this, getWorld()->getNBlaster()))
    {
      getWorld()->playSound(SOUND_GOODIE);
      reward();
        die();
        return;
    }
    
    moveTo(getX()-.75, getY()-.75);
    //separate
    if(getX() < 0 || getY() >= VIEW_HEIGHT || getY() < 0)
    {
        die();
        return;
    }
    
    
    if(!didTheyCollide(this, getWorld()->getNBlaster()))
    {
        reward();
        getWorld()->playSound(SOUND_GOODIE);
        die();
    }
}

void lifeGoodies::reward() {
    getWorld()->incLives();
}

void repairGoodies::reward() {
    getWorld()->increaseScore(100);
    int total = 10 + getWorld()->getNBlaster()->getHitPts();
    if (total > 50)
        total = 50;
    getWorld()->getNBlaster()->setHitPts(total);
}

void torpedoGoodies::reward() {
    getWorld()->increaseScore(100);
    getWorld()->getNBlaster()->addTorpedoes(5);
    
}
    bool Nachenblaster::checkCollide() {
        if(!isItAlive())
        {
            return false;
        }
        int i = 0;
        bool didThey = false;
        while (i < (getWorld()->getVec()).size())
        {
            if(enemyOfNachenblaster(getWorld()->getVec()[i]))
            {
                if(didTheyCollide(this, getWorld()->getVec()[i])) {
                didThey = true;
                if(isItAlive())
                   
                    if (getWorld()->getVec()[i]->getID() == IID_TORPEDO)
                    {
                        if(getWorld()->getVec()[i]->ownership()==IID_NACHENBLASTER)
                            continue;
                        
                    }
                int otherID = getWorld()->getVec()[i]->getID();
                getDamaged(otherID);
                getWorld()->getVec()[i]->die();
                
          ;
                if(getWorld()->getVec()[i]->isItAlien()) //if it is an alien
                {
                    Explosions *e = new Explosions(getWorld()->getVec()[i]->getX(),getWorld()->getVec()[i]->getY());
                    getWorld()->addActor(e);
                    getWorld()->addDestruction();
                    getWorld()->playSound(SOUND_DEATH);
                    switch(otherID)
                    {
                        case IID_SMOREGON:
                        {
                            getWorld()->increaseScore(250);
                            //1/3 chance it can drop a goodie, half a chance after that it could be a repair or a torpedo
                            if(randInt(1,3)==1)
                            {
                                Goodies *rpg;
                                if(randInt(0, 1)==0)
                                    rpg = new repairGoodies(getWorld()->getVec()[i]->getX(),getWorld()->getVec()[i]->getY());
                                else
                                    rpg = new torpedoGoodies(getWorld()->getVec()[i]->getX(),getWorld()->getVec()[i]->getY());
                                getWorld()->addActor(rpg);
                                rpg->setWorld(this->getWorld());
                            }
                            break;
                        }
                        case IID_SMALLGON:
                            getWorld()->increaseScore(250);
                            break;
                        case IID_SNAGGLEGON:
                            getWorld()->increaseScore(1000);
                            if(randInt(1,6)==3)
                            {
                                lifeGoodies *lg = new lifeGoodies(getWorld()->getVec()[i]->getX(),getWorld()->getVec()[i]->getY());
                                getWorld()->addActor(lg);
                                lg->setWorld(this->getWorld());
                            }
                        
                    }
                    getWorld()->addDestruction();
                }

                    if(!isItAlive())
                    { 
                        return true;
                    }
            }
       
            }
            i++;
        }
        return didThey;
    }

    bool Aliens::checkCollide() {
        int i = 0;
        bool didThey = false;

        while (i < (getWorld()->getVec()).size())
        {
            if(getWorld()->getNBlaster()->enemyOfAlien(getWorld()->getVec()[i]))
            {
                
                if(didTheyCollide(this, getWorld()->getVec()[i]))
                {
                    didThey = true;
                    if (getWorld()->getVec()[i]->getID() == IID_TORPEDO)
                    {
                        if(getWorld()->getVec()[i]->ownership()!=IID_NACHENBLASTER)
                        {
                            i++;
                            continue;
                        }
                    }
                    getDamaged(getWorld()->getVec()[i]->getID());
                    if(getWorld()->getVec()[i]->getID() != IID_NACHENBLASTER)
                        getWorld()->getVec()[i]->die();
                    if(isItAlive())
                        getWorld()->playSound(SOUND_BLAST);
                    else
                        getWorld()->playSound(SOUND_DEATH);
                    
                }
         
            }
            if (!isItAlive())
                return true;

            i++;
        }
        
        return didThey;
    }

void Actor::getDamaged(int ID) {
    //basic switch case
    switch(ID)
    {
        case IID_CABBAGE:
            setHitPts(getHitPts()-2);
            break;
        case IID_TORPEDO:
            setHitPts(getHitPts()-8);
            
            break;
        case IID_TURNIP:
            setHitPts(getHitPts()-2);
            break;
        case IID_SMALLGON:
        case IID_SMOREGON:
            if (this->getID() == IID_NACHENBLASTER)
            {
                setHitPts((getHitPts()-5));
            }
            break;
        case IID_SNAGGLEGON:
            if (this->getID() == IID_NACHENBLASTER)
            {
                setHitPts((getHitPts()-15));
            }
            break;
        case IID_NACHENBLASTER:
        {
            setHitPts(0);
            //explosion
        }
            
    }

    if (getHitPts()<=0)
    {
        die();
        Explosions *e = new Explosions(getX(),getY());
        getWorld()->addActor(e);
        //change this implementation for or statements
        if(getID() == IID_SMALLGON ||getID() == IID_SMOREGON)
            getWorld()->increaseScore(250);
        else if (getID() == IID_SNAGGLEGON)
            getWorld()->increaseScore(1000);
        if (getID() != IID_NACHENBLASTER)
            getWorld()->addDestruction();
        return;
    }
   
}

void Aliens::moveInPath(int fpath) {
    
    switch (fpath)
    {
        case 1: //due left
            moveTo(getX()-getSpeed(), getY());
            
            break;
        case 2: //up and left
            moveTo(getX()-getSpeed(),getY()+getSpeed());
            
            break;
        case 3: //down and left
            moveTo(getX()-getSpeed(), getY()-getSpeed());
            break;
    }
}
bool Actor::isItAlien(){
    
    switch(getID()){
        case IID_SMALLGON:
        case IID_SMOREGON:
        case IID_SNAGGLEGON:
            return true;        
    }
    
    return false;
}

bool Actor::enemyOfAlien(Actor *p) {
    switch(p->getID())
    {
        case IID_CABBAGE:
        case IID_NACHENBLASTER:
        case IID_TORPEDO:
            return true;
 
    }
    
    return false;
}
bool Actor::enemyOfNachenblaster(Actor *p) {
    switch (p->getID())
    {
        case IID_STAR:
        case IID_EXPLOSION:
            return false;
  
    }
    return true;
}
