#pragma once

#include "../PhysicalEntity.h"
#include "../../SF_src/Demo.h"
#include "../../SF_src/DemoHandler.h"
#include "../../SF_src/MyVector.h"
#include "../Drawable.h"
#include <cmath>
#include <string>
#include <sstream>


class Particle: public PhysicalEntity
{
private:
    MyVector mForce; // kraften som verkar på partikeln
    float mMass; // massan
    float mInvMass; // den inverterade massan lagras av effektivitetsskäl
    
protected:
    MyVector mPos; // partikelns position
 public:
    Particle(const float Mass)
	{
        setMass(Mass);
        clearForce();
    }
    
    //behövs tydligen för att slippa varning
    virtual ~Particle(){}
    
    const float getMass()
    {
        return mMass;
    }
    
    const float getInvMass()
    {
        return mInvMass;
    }
    
    void setMass(const float Mass)
    {
        mMass = Mass;
        if(mMass == 0)
            mInvMass = BIGFLOAT;
        else
            mInvMass = 1.0 / mMass; // se upp med 0-massa
    }
    
    
    virtual MyVector getPosition()
    {
        return MyVector(mPos);
    }
    
    virtual void setPosition(const MyVector newP)
    {
        mPos = newP;
    }
    
    //Flytta partikeln angiven sträcka
    virtual void move(const MyVector dp) = 0;

    
   //Hastigheten hanteras olika i subklasserna
    virtual MyVector getVelocity() = 0;
    
    virtual void setVelocity(const MyVector newV) = 0;
    
    
    //denna anropas för att nollställa kraften
    virtual void clearForce()
    {
        mForce = MyVector();
    }
    
    //denna anropas för att lägga på krafter på partikeln
    virtual void addForce(const MyVector f)
    {
        mForce += f;
    }
   
    //denna anropas för att lägga på krafter på partikeln i en specifik punkt
    virtual void addForce(const MyVector f, const MyVector pt)
    {
        addForce(f); //För partiklar spelar angreppspunkt ingen roll
    }
    
    //returnerar kraften som lagts på partikeln
    virtual MyVector getForce()
    {
        return mForce;
    }
    
    //returnerar avståndet mellan två partiklar
    const float distance(Particle* p2)
    {
        return (getPosition() - p2->getPosition() ).length();
    }
    
    //en partikel har ingen volym och kan egentligen inte ritas. Bollklassen används för att kunna rita
    virtual void draw(DemoHandler* draw, const bool drawDebug = false)
	{
        if(drawDebug)
            draw->drawPoint(getPosition().toPoint(), WHITE, 0.05f);
    }
};

/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */

