
using namespace std;

class BallAndPlane:public Demo
{
public:
    PhysicsHandler *handler;
    MyVector mPlaneNormal;
    BallAndPlane()
    {
        handler = new PhysicsHandler();
        setPlane(MyVector(0, 1, 0));
    }
    void reset()
    {
        handler->removeAll();
        handler->addPlane(new Plane(MyVector(5, 5, 0), mPlaneNormal));
        handler->addBall(new EulerBall(MyVector(5, -7, 0)));
    }
    void setPlane(MyVector n)
    {
        mPlaneNormal = n;
        mPlaneNormal.normalize();
        reset();
    }
    void update(DemoHandler* draw)
    {
        handler->updatePhysics();
        handler->handleCollisions();
        handler->drawPhysics(draw);
        
        if(draw->keyTyped('1'))
            setPlane(MyVector(-1, 2, 0));
        if(draw->keyTyped('2'))
            setPlane(MyVector(0, 1, 0));
        if(draw->keyTyped('3'))
            setPlane(MyVector(1, 2, 0));
        
        if(draw->keyTyped('r'))
            reset();
    }
    
    const virtual string getName()
    {
        return "A ball and plane demo";
    }
    const virtual string getInfo()
    {
        return "Press 1,2,3 to change the slope of the plane";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */