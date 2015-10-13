#pragma once
#include "../SF_src/DemoHandler.h"
#include "../SF_src/MyVector.h"
#include "Drawable.h"

class PhysicalEntity: public Drawable
{
public:
    //Returnerar entitetens massa
    virtual const float getMass() = 0;
    
    //returnerar entitetens globala position
    virtual MyVector getPosition() = 0;
    
    //Flyttar entiteten till angiven global position
    virtual void setPosition(const MyVector p) = 0;
    
    //Flyttar entiteten angiven sträcka
    virtual void move(const MyVector dp) = 0;
    
    //returnerar tyngdpunktens hastighet
    virtual MyVector getVelocity() = 0;
    
    //Sätter tyngdpunktens hastighet
    virtual void setVelocity(const MyVector v) = 0;
    
    //rensar alla krafter på entiteten
    virtual void clearForce() = 0;
    
    //Lägger på en kraft i tyngdpunkten
    virtual void addForce(const MyVector f) = 0;
    
    //Lägger på en kraft i angiven global punkt. Kan ge upphov till rotation på rigida kroppar
    virtual void addForce(const MyVector f, const MyVector globalPt) = 0;
    
    //uppdaterar entitetens tillstånd (default utan dämpning)
    virtual void update(float dt, float damp = 0.0) = 0;
};

/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */

