
using namespace std;

class FirstSpring:public Demo
{
public:
    PhysicsHandler *handler;
    MyVector mSpringEnd = MyVector(6, 8, 0);
    Ball *mBall;
    
    FirstSpring()
    {
        handler = new PhysicsHandler();
        mBall = new EulerBall(MyVector(5, 8, 0));
        handler->addBall(mBall);
        //handler->G = 0;
    }
    
    void update(DemoHandler* draw)
    {
        if(draw->isMouseDown())
        {
            mBall->setPosition(MyVector(draw->getMouseLocation()));
            mBall->setVelocity(MyVector());
        }
        else
        {
            MyVector springForce = (mBall->getPosition() - mSpringEnd) * -1;
            mBall->addForce(springForce);
            handler->updatePhysics();
        }
        handler->drawPhysics(draw);
        draw->drawLine(mBall->getPosition().toPoint(),
                       mSpringEnd.toPoint(), WHITE, 0.05);
    }
    
    const virtual string getName()
    {
        return "First spring demo";
    }
    const virtual string getInfo()
    {
        return "Click to move the ball";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */