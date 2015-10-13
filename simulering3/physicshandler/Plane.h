#pragma once
#include "../SF_src/Demo.h"
#include "../SF_src/DemoHandler.h"
#include "../SF_src/MyVector.h"
#include <cmath>
#include <string>
#include <sstream>
#include "Drawable.h"


using namespace std;

class Plane : public Drawable
{
private:
    MyVector mPointinplane; // en (godtycklig bortsett från ritandet) punkt i planet
    MyVector mNormal; // planets normal
    
public:
   
    Plane(const MyVector Point, const MyVector Normal)
    {
        mPointinplane=Point;
        mNormal=Normal;
        mNormal.normalize();//better safe than sorry
    }
    
    virtual ~Plane(){}
    
    //Avstånd från punkt till plan
    const float distance(const MyVector pt)
    {
        MyVector p_q = MyVector(pt) - mPointinplane;
        return p_q * mNormal;
    }
    
    const MyVector getPointInPlane()
    {
        return mPointinplane;
    }
    
    const MyVector getNormal()
    {
        return mNormal;
    }
    
    virtual void draw(DemoHandler* draw, const bool drawDebug = false)
	{
        draw->drawPlane( mPointinplane.toPoint(), mNormal.toPoint(), GREEN, 15 );
        
        if(drawDebug)
            draw->drawLine(mPointinplane.toPoint(), (mPointinplane + mNormal).toPoint(),PINK);//Normalen
        
        // För att vi skall se något i x-y projektion
        MyVector lineDir= MyVector(0, 0, 1) % mNormal; //kryssprodukten av vektorn som pekar ut ur skärmen och planets normal
        lineDir.normalize();
        
        draw->drawLine((mPointinplane - lineDir * 20).toPoint(), (mPointinplane + lineDir * 20).toPoint(), GREEN);//rita ett grönt streck som representerar planet
    }
};

/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */
