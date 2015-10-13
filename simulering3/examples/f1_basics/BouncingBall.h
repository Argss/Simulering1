using namespace std;
class BouncingBall:public Demo
{
public:
    MyVector mPosition;
    MyVector mVelocity;
    float mMass = 0.5;
    
    BouncingBall()
    {
        reset();
    }
    void reset()
    {
        mPosition = MyVector(3, 5, 0);
        mVelocity = MyVector(0, 0, 0);
    }
    
    void update(DemoHandler* draw)
    {
        if(draw->keyTyped('r'))
            reset();
        
        float DT = 1.0 / 60;
        
        mPosition += mVelocity * DT;
        
        MyVector force = MyVector(0, -9.8 * mMass, 0);
        MyVector acceleration = force * (1.0/mMass);
        mVelocity += acceleration * DT;
        
        draw->drawPoint(mPosition.toPoint(), GREEN, 0.3);
        
    }
    
    const virtual string getName()
    {
        return "Bouncing ball (not bouncing yet)";
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