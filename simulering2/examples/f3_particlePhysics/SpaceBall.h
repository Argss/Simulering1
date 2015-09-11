
using namespace std;

class SpaceBall:public Demo
{
public:
    PhysicsHandler *handler;
    EulerBall *mBall;
    SpaceBall()
    {
        handler = new PhysicsHandler();
        handler->G = 0;
        reset();
    }
    void reset()
    {
        handler->removeAll();
        mBall = new EulerBall(MyVector(5,5,0));
        handler->addBall(mBall);
    }
    void update(DemoHandler* draw)
    {
        handler->updatePhysics();
        handler->handleCollisions();//onödig
        handler->drawPhysics(draw);
        
        if(draw->keyTyped('w'))
            mBall->addForce(MyVector(0, 20, 0));
        if(draw->keyTyped('s'))
            mBall->addForce(MyVector(0, -20, 0));
        if(draw->keyTyped('a'))
            mBall->addForce(MyVector(-20, 0, 0));
        if(draw->keyTyped('d'))
            mBall->addForce(MyVector(20, 0, 0));
        
        
        if(draw->keyTyped('r'))
            reset();
    }
    
    const virtual string getName()
    {
        return "Space Ball";
    }
    const virtual string getInfo()
    {
        return "Press w, a, s, d to add force to the ball (up, left, down, right)";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */