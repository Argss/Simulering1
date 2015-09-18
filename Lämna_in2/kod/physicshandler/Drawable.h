#pragma once
#include "../SF_src/DemoHandler.h"
//basklass för allt som skall ritas.
class Drawable
{
public:
    //Anropas vid ritning. Har en debug-flagga som indikerar om extra debuginformation skall ritas
    virtual void draw(DemoHandler* draw, const bool drawDebug = false) = 0;
};

/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */