#pragma once

#include "../../SF_src/Demo.h"
#include "../../SF_src/DemoHandler.h"
#include "../../SF_src/MyVector.h"
#include <cmath>
#include <string>
#include <sstream>
#include "Ball.h"


class EulerBall : public Ball
{
private:
	MyVector mVelocity;//hastigheten lagras explicit för Eulerbollar (till skillnad från Verlet)
public:
    
    EulerBall(const MyVector pos,const MyVector velocity = MyVector(),const float Mass = 0.2,const float Radius = 0.3, const Color c= MAGENTA) : Ball(Mass, Radius, c)
	{
        mPos = pos;
        setVelocity(velocity);
    }
    //Förflyttning kan göras på ett rättfram sätt (till skillnad från Verlet)
    virtual void move(const MyVector dPos)
    {
        mPos += dPos;
    }
    // Hastigheten returneras
    virtual MyVector getVelocity()
    {
        return MyVector(mVelocity);
    }
    // Hastigheten sätts rätt och slätt (till skillnad från Verlet)
    virtual void setVelocity(const MyVector newV)
    {
        mVelocity = newV;
    }
    virtual void update(float dt, float damp = 0.0)
	{
        mPos += getVelocity() * dt;
        mVelocity += getForce() * getInvMass() * dt; // Lägg till förändring för att få den nya hastighetet
        mVelocity *= (1-damp);
	}
};

/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */

