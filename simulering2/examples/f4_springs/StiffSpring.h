
using namespace std;

class StiffSpring:public Demo
{
public:
    PhysicsHandler *handler;
    MyVector mSpringEnd = MyVector(6, 8, 0);
    Ball *mBall;
    float mSpringConstant = 100.0;
    StiffSpring()
    {
        handler = new PhysicsHandler();
        mBall = new EulerBall(MyVector(5, 8, 0));
        handler->addBall(mBall);
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
            MyVector springForce = (mBall->getPosition() - mSpringEnd) * - mSpringConstant;
            mBall->addForce(springForce);
            handler->updatePhysics();
        }

        
        handler->drawPhysics(draw);
        draw->drawLine(mBall->getPosition().toPoint(), mSpringEnd.toPoint(), WHITE, 0.05);
    
        ostringstream os;
        os<<"Ks="<<mSpringConstant;
        draw->drawText(mSpringEnd.toPoint(), os.str());
    
    }
    
    const virtual string getName()
    {
        return "Stiff spring demo";
    }
    const virtual string getInfo()
    {
        return "Click to move the ball. Press + to double spring stiffness.\nPress - to half spring stiffness";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */