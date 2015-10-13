#pragma once

#include "../SF_src/Demo.h"
#include "../SF_src/DemoHandler.h"
#include "../SF_src/MyVector.h"
#include "Constants.h"
#include <cmath>
#include <string>
#include <sstream>
#include "Plane.h"
#include "particlePhysics/Ball.h"
#include "particlePhysics/EulerBall.h"


class PhysicsHandler{
private:
    Plane *mPlane;
    Ball *mBall;
    
public:
    float G = 10.0; // m/s2
    float ELASTICITY = 0.5; //Elasticitetskoefficient
    float STEP = 1.0/60;//tidssteget som används vid integrering. Denna måste vara fix i Verlet
    float DAMPING = 0.01; // the damping constant to remove energy from the system
    bool  DEBUGDRAW = false;//flaggar om debuginfo (hastigheter och normaler) skall ritas

    PhysicsHandler(){}
    
    virtual void removeAll()
    {
        if(mPlane != NULL)
            delete mPlane;
        
        if(mBall != NULL)
            delete mBall;
        
        mPlane = NULL;
        mBall = NULL;
    }
    
    virtual void addBall(Ball* newBall)
    {
        if( mBall != NULL)
            delete mBall;
        mBall = newBall;
    }
    
    virtual void addPlane(Plane* newPlane)
    {
        if(mPlane != NULL)
            delete mPlane;
        mPlane = newPlane;
    }
    
    void updatePhysics()
    {
        if(mBall == NULL)
            return;
        
        mBall->addForce(MyVector(0, -G * mBall->getMass(),0));
        
        mBall->update(STEP, DAMPING); //uppdatera tillståndet
        
        mBall->clearForce();
        
    }
    
    
    void handleCollisions()
    {
        if(mPlane == NULL || mBall == NULL)
            return;
        
        MyVector n = mPlane->getNormal();
        
        
        
        float vrel  = mBall->getVelocity() * n;
        float depth = mBall->getRadius() - mPlane->distance(mBall->getPosition());
        if(depth > 0)
        {
            mBall->move( n * depth); //flytta ut från planet
            if(vrel < 0)
                mBall->setVelocity( mBall->getVelocity() - n * vrel * (1 + ELASTICITY));
        }
    }
    
    virtual void drawPhysics(DemoHandler* draw)
    {
        if(mPlane != NULL)
            mPlane->draw(draw, DEBUGDRAW);
        
        if(mBall != NULL)
            mBall->draw(draw , DEBUGDRAW);
    }
    
};
/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */
