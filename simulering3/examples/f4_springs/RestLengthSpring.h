
using namespace std;

class RestLengthSpring:public Demo
{
public:
    PhysicsHandler *handler;
    MyVector mSpringEnd = MyVector(6, 8, 0);
    Ball *mBall;
    float mSpringConstant = 8.0;
    float mSpringRestLength = 1.0;
    RestLengthSpring()
    {
        handler = new PhysicsHandler();
        mBall = new EulerBall(MyVector(5, 8, 0));
        handler->addBall(mBall);
        handler->G = 0;
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
            MyVector springDir = (mBall->getPosition() - mSpringEnd);
            float springExtension = springDir.length();
            springDir.normalize();
            MyVector springForce = springDir * (springExtension - mSpringRestLength) * - mSpringConstant;
            mBall->addForce(springForce);
            handler->updatePhysics();
        }
        if(draw->keyTyped('+'))
            mSpringConstant *= 2;
        if(draw->keyTyped('-'))
            mSpringConstant *= 0.5;
        
        handler->drawPhysics(draw);
        draw->drawLine(mBall->getPosition().toPoint(), mSpringEnd.toPoint(), WHITE, 0.05);
    
        ostringstream os;
        os<<"Ks="<<mSpringConstant<< " Kl="<<mSpringRestLength;
        draw->drawText(mSpringEnd.toPoint(), os.str());
    
    }
    
    const virtual string getName()
    {
        return "Rest-length spring demo";
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