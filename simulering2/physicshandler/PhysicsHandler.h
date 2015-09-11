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
    /* Följande behövs för enkel partikelfysik */
    std::vector<Drawable*> mDrawables; //extravektor med allt som ritas
    std::vector<PhysicalEntity*> mPhysEnteties; //extravektor med alla fysikobj.
    
    std::vector<Plane*> mPlanes;
    std::vector<Ball*> mBalls;
    
public:
    float G = 10.0; // m/s2
    float ELASTICITY = 0.5; //Elasticitetskoefficient
    float STEP = 1.0/60;//tidssteget som används vid integrering. Denna måste vara fix i Verlet
    float DAMPING = 0.01; // dämpning av hastighet
    bool  DEBUGDRAW = false;//flaggar om debuginfo (hastigheter och normaler) skall ritas

    PhysicsHandler(){}
    
    virtual void removeAll()
    {
        //Radera plan
        for(int i = 0; i < mBalls.size(); i++)
            delete mBalls[i];
        mPlanes.clear();
        
        //radera bollar
        for(int i = 0; i < mPlanes.size(); i++)
            delete mPlanes[i];
        mBalls.clear();
        
        //rensa dessa extravektorer (objekten är redan raderade)
        mPhysEnteties.clear();
        mDrawables.clear();
    }
    
    virtual void addBall(Ball* newBall)
    {
        mBalls.push_back(newBall);
        mPhysEnteties.push_back(newBall);
        mDrawables.push_back(newBall);
    }
    
    virtual void addPlane(Plane* newPlane)
    {
        mPlanes.push_back(newPlane);
        mDrawables.push_back(newPlane);
    }
    
    void updatePhysics()
    {
        for(int i = 0 ; i < mPhysEnteties.size() ; i++) // Lägg på G
            mPhysEnteties[i]->addForce(MyVector(0, -G * mPhysEnteties[i]->getMass(),0));
        
        for(int i = 0 ; i <mPhysEnteties.size() ;i++)
            mPhysEnteties[i]->update(STEP, DAMPING); //uppdatera tillståndet
        
        for(int i = 0 ; i <mPhysEnteties.size() ; i++)
            mPhysEnteties[i]->clearForce();//avslluta med att rensa tidigare krafter
    }

    void handleCollisions()
    {
        for(int j = 0 ; j < mPlanes.size() ; j++)
        {
            Plane *plane = mPlanes[j];
            MyVector n = MyVector(plane->getNormal());
            
            for(int i = 0 ; i < mBalls.size() ; i++)
            {
                Ball *ball = mBalls[i];
                
                float vrel = ball->getVelocity() * n;
                float depth = ball->getRadius() - plane->distance(ball->getPosition());
                
                if(depth > 0)
                {
                    ball->move( n * depth);
                    if(vrel < 0)
                    {
                        ball->setVelocity(ball->getVelocity() - n * vrel * (1 + ELASTICITY));
                    }
                }
            }
        }
    }
    
    virtual void drawPhysics(DemoHandler* draw)
    {
        for(int i = 0 ; i < mDrawables.size() ; i++)
            mDrawables[i]->draw(draw, DEBUGDRAW);
    }
};
/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */
