using namespace std;

class BouncingBallWithCollision:public Demo
{
public:
    MyVector mPosition;
    MyVector mVelocity;
    float mMass = 0.5; //kg
    BouncingBallWithCollision()
    {
        reset();
    }
    void reset()
    {
        mPosition = MyVector(3,5,0);
        mVelocity = MyVector();
    }
    
    void update(DemoHandler* draw)
    {
        if(draw->keyTyped('r'))
            reset();
        
        float DT = 1.0 / 60;
        
        MyVector force = MyVector(0, -980/100 * mMass, 0);
       
        MyVector acceleration = force * (1.0/mMass);
        mVelocity += acceleration * DT;
        
        mPosition += mVelocity * DT;
       
        if(mVelocity.mY < 0 && mPosition.mY < 0)
            mVelocity.mY *= -1.0;
        
        
        draw->drawPoint(mPosition.toPoint(), GREEN, 0.3);
        
    }
    
    const virtual string getName()
    {
        return "Bouncing ball";
    }
    const virtual string getInfo()
    {
        return "Press r to reset";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */