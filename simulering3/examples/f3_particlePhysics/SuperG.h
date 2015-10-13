
using namespace std;

class SuperG:public Demo
{
public:
    PhysicsHandler *handler;
    int mSubSteps;
    SuperG()
    {
        handler = new PhysicsHandler();
        handler->G = 1000;
        handler->DEBUGDRAW = true;
        setSubSteps(10);
    }
    void reset()
    {
        handler->removeAll();
        handler->addPlane(new Plane(MyVector(1, 0, 0), MyVector(0, 1, 0)));
        handler->addBall(new EulerBall(MyVector(5, 6, 0)));
    }
    
    void setSubSteps(int steps)
    {
        mSubSteps = steps;
        handler->STEP = 1.0/ (60 * steps);
        reset();
    }
    void update(DemoHandler* draw)
    {
        if(draw->keyTyped('a'))
            setSubSteps(1);
        if(draw->keyTyped('s'))
            setSubSteps(10);
        if(draw->keyTyped('d'))
            setSubSteps(100);
        
        for(int i=0; i<mSubSteps; i++)
        {
            handler->updatePhysics();
            handler->handleCollisions();
        }
       
        handler->drawPhysics(draw);
    }
    
    const virtual string getName()
    {
        return "Big g and small steps";
    }
    const virtual string getInfo()
    {
        return "Press a to have dt=1/60 s.\n press s to have dt=1/600 s. \n press d to have dt=1/3000 s.";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */