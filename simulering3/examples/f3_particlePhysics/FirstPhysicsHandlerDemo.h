
using namespace std;

class FirstPhysicsHandlerDemo:public Demo
{
public:
    PhysicsHandler *handler;
    FirstPhysicsHandlerDemo()
    {
        handler = new PhysicsHandler();
        handler->ELASTICITY = 0.2;
        handler->DAMPING = 0.05;
        handler->STEP = 0.001;
        reset();
    }
    void reset()
    {
        handler->removeAll();
        handler->addPlane(new Plane( MyVector(1, 0, 0), MyVector(0, 1, 0)));
        handler->addBall(new EulerBall(MyVector(5, 6, 0)));
    }
    void update(DemoHandler* draw)
    {
        handler->updatePhysics();
        handler->handleCollisions();
        handler->drawPhysics(draw);
        
        if(draw->keyTyped('1'))
            handler->ELASTICITY = 1.0;
        if(draw->keyTyped('0'))
            handler->ELASTICITY = 0.0;
        if(draw->keyTyped('9'))
            handler->ELASTICITY = 0.9;
        if(draw->keyTyped('z'))
            handler->G = 0;
        if(draw->keyTyped('x'))
            handler->G = 10;
        if(draw->keyTyped('c'))
            handler->G = 100;
        if(draw->keyTyped('v'))
            handler->G = 1000;

        if(draw->keyTyped('+'))
            handler->DEBUGDRAW = true;
        
        if(draw->keyTyped('-'))
            handler->DEBUGDRAW = false;

        if(draw->keyTyped('r'))
            reset();
    }
    
    const virtual string getName()
    {
        return "First PhysicsHandler Demo";
    }
    const virtual string getInfo()
    {
        return "Press r to reset\nPress 1,0,9 to change elasticity (1.0 0.0 0.9)\nPress z,x,c,v to change g (0 10 100 1000 m/s^2)\n Press + & - to enable/disable debug graphics";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */