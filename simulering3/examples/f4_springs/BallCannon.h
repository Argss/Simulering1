using namespace std;

class BallCannon:public Demo
{
public:
    PhysicsHandler *handler;
    
    BallCannon()
    {
        handler = new PhysicsHandler();
        reset();
    }
    void reset()
    {
        handler->removeAll();
        handler->ELASTICITY = 0.9;
        handler->DAMPING = 0.0;
        handler->addPlane(new Plane(MyVector(5, 0, 0),MyVector(0, 1, 0)));
        handler->addPlane(new Plane(MyVector(1, 0, 0),MyVector(1, 1, 0)));
        handler->addPlane(new Plane(MyVector(9, 0, 0),MyVector(-1, 1, 0)));
        
        
    }
    
    void update(DemoHandler* draw)
    {
        handler->updatePhysics();
        handler->handleCollisions();
        handler->drawPhysics(draw);
        if(draw->isMouseDown())
            handler->addBall(new EulerBall(MyVector(draw->getMouseLocation())));
        
        if(draw->keyTyped('r'))
            reset();
    }
    
    const virtual string getName()
    {
        return "Ball cannon";
    }
    const virtual string getInfo()
    {
        return "Press mouse button to shoot balls (a lot of them)";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */