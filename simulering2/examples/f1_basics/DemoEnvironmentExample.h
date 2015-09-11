
using namespace std;

class DemoEnvironmentExample:public Demo
{
private:
    float mSize = 1.0;
public:
    void update(DemoHandler* draw)
    {
       if(draw->keyTyped('1'))
           mSize=1.0;
        if(draw->keyTyped('2'))
            mSize=2.0;
        if(draw->keyTyped('3'))
            mSize=3.0;
        
        draw->drawPoint(Point(1, 2, 0), GREEN, mSize * 0.2);
        draw->drawLine(Point(1, 2, 0), Point(1, 8, 0), PINK, mSize*0.1);
    }
    
    const virtual string getName()
    {
        return "First Demo";
    }
    const virtual string getInfo()
    {
        return "Click 1-3 to change size of the rod";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */