#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// DIRT CONSTANTS
const GraphObject::Direction DIRT_DIR = GraphObject::right;
const int DIRT_DEPTH = 3;
const double DIRT_SIZE = 0.25;

// PLAYER CONSTANTS

const GraphObject::Direction PLAYER_DIR = GraphObject::right;
const int PLAYER_DEPTH = 0;
const double PLAYER_SIZE = 1.0;
const int PLAYER_START_X = 30;
const int PLAYER_START_Y = 60;
const int PLAYER_HITPOINTS = 10;
const int PLAYER_START_WATER = 5;
const int PLAYER_START_SONAR = 1;
const int PLAYER_START_NUGGETS = 0;

// BOULDER COSNTANTS
const GraphObject::Direction BOULDER_DIR = GraphObject::down;
const int BOULDER_DEPTH = 1;
const double BOULDER_SIZE = 1.0;

// OIL BARREL CONSTANTS
const GraphObject::Direction OIL_BARREL_DIR = GraphObject::right;
const int OIL_BARREL_DEPTH = 2;
const float OIL_BARREL_SIZE = 1.0;

// SQUIRT CONSTANTS
const int SQUIRT_DEPTH = 1;
const float SQUIRT_SIZE = 1.0;

// GOLD NUGGET CONSTANTS
const GraphObject::Direction GOLD_NUGGET_DIR = GraphObject::right;
const int GOLD_NUGGET_DEPTH = 2;
const float GOLD_NUGGET_SIZE = 1.0;

// SONAR KIT CONSTANTS
const GraphObject::Direction SONAR_KIT_DIR = GraphObject::right;
const int SONAR_KIT_DEPTH = 2;
const float SONAR_KIT_SIZE = 1.0;

// WATER POOL CONSTANTS
const GraphObject::Direction WATER_POOL_DIR = GraphObject::right;
const int WATER_POOL_DEPTH = 2;
const float WATER_POOL_SIZE = 1.0;

/*
 * Class for all Actors.
 * Actors extend GraphObject and are basically every object in the game that does something
 */
class Actor : public GraphObject{
public:
    // Basic constructor for an Actor
    Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, StudentWorld* world, int hitpoints);
    // Simple destructor for Actor
    ~Actor();
    /*
     * Every actor should be able to do something and most do something significant.
     * The only exception is Dirt whose sole purpose is to be destroyed but it is still considered an actor
     * since being destroyed is still considered doing something.
     */
    virtual void doSomething() = 0;
    // Return a pointer to the Student World object that this Actor belongs to.
    // useful because methods from the StudentWorld are eneded in some Actor functions.
    StudentWorld* getWorld();

    // move something x steps forward
    bool moveForward();
    bool isValidPosition(int x, int y);

    // check if actor is alive
    bool isAlive() const;
    // set the actor to dead
    void setDead();
    void reduceHitpoints(int hp);

private:
    // store the Student World that the Actor belongs to.
    StudentWorld* m_world;
    // TODO phase out alive
    bool alive;
    int m_hitpoints;
    // make sure the actor is going to a valid palce

};



/* Dirt just gets destroyed by the Frackman when he steps on it */
class Dirt : public Actor{
public:
    Dirt(int x, int y, StudentWorld* world);
    ~Dirt();
    void doSomething();
private:
};

// Boulders fall on people
class Boulder : public Actor {
public:
    Boulder(StudentWorld* world,int x, int y);

    virtual void doSomething();
};

// Squirts are things that you shoot at protesters
class Squirt : public Actor {
public:
    Squirt(StudentWorld* world, int x, int y, Direction dir);
    virtual void doSomething();

private:
    // store starting points so the distance to it's current spot can be measured
    int start_x;
    int start_y;
};

/* Any object that can be 'picked-up' by the FrackMan
 * These objects have to deal with things that are within a certain radius
 * they also have activations potentially
 */
class Pickup : public Actor{
public:
    // Basic constructor for a Pickup
    Pickup(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, StudentWorld* world, int hitpoitns);
    virtual void doSomething() = 0;
};

// the thing we are trying to pick up
class OilBarrel : public Pickup{
public:
    OilBarrel(StudentWorld* world, int x, int y);

    virtual void doSomething();
};

// used to bribe protesters
class GoldNugget : public Pickup{
public:
    GoldNugget(StudentWorld* world, int x , int y);

    virtual void doSomething();
};

// used to reveal shit
class SonarKit : public Pickup {
public:
    SonarKit(StudentWorld* world, int x, int y);

    virtual void doSomething();
};

// used to refill squirts
class WaterPool : public Pickup {
public:
    WaterPool(StudentWorld* world, int x, int y);

    virtual void doSomething();
};

/*
 * All Persons can be annoyed
 */
class Person : public Actor {
public:
    // Basic constructor for a Pickup
    Person(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, StudentWorld* world, int hitpoints);

    virtual void doSomething() = 0;
};

/*
 * A FrackMan is controlled by the user
 * Takes in user input then does something every turn
 */
class FrackMan : public Person {
public:
    // Basic constructor
    FrackMan(StudentWorld* world);
    ~FrackMan();
    void doSomething();
    // Pick up a sonar kit.
    void addSonar(int a);

    virtual void addGold(int a);
    // Pick up water.
    void addWater(int a);

    // Get amount of gold
     int getGold() const;

    // Get amount of sonar charges
     int getSonar() const;

    // Get amount of water
     int getWater() const;

private:
     int m_gold;
     int m_sonar;
     int m_water;
};


/*
 * A Protester is a bot
 * There are hardcore and regular protestors
 * They have almost everything in common except the way they seek the Frackman
 *
class Protester : public Person {
public:
    // Basic constructor
    Protester(StudentWorld* world);
}; */


// A position has an x and y value
// the Euclidean Distance between two values can be calculated
// you can check if two objects are within radius.
class Position {
public:
    Position(int x, int y);
    // gets the euclidean distance between two positions
    static float getDistance(Position pos1, Position pos2);

};

#endif // ACTOR_H_
