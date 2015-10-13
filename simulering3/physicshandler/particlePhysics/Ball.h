#pragma once


#include "../PhysicalEntity.h"
#include "../../SF_src/Demo.h"
#include "../../SF_src/DemoHandler.h"
#include "../../SF_src/MyVector.h"
#include "../Drawable.h"
#include "Particle.h"
#include <cmath>
#include <string>
#include <sstream>

class Ball: public Particle
{
private:
    float mR; // bollens radie
    Color mColor;
    
public:
    
    Ball(const float Mass,const float Radius, const Color color):Particle(Mass)
	{
        mR = Radius;
        mColor = color;
    }
    
    //behövs tydligen för att slippa varning
    virtual ~Ball(){}
    
    const float getRadius()
    {
        return mR;
    }
    
    virtual void draw(DemoHandler* draw, const bool drawDebug = false)
	{
        draw->drawPoint(getPosition().toPoint(), mColor, getRadius());
        
        if(drawDebug)
            draw->drawLine(getPosition().toPoint(), (getPosition()+getVelocity()).toPoint(), WHITE, 0.05);
    }
};

/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */