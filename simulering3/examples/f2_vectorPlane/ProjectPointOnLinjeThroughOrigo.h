
using namespace std;

class ProjectPointOnLinjeThroughOrigo:public Demo
{
public:
    MyVector mLineDir;
    
    ProjectPointOnLinjeThroughOrigo()
    {
        mLineDir = MyVector(1,2,0);
        mLineDir.normalize();
    }
    
    void update(DemoHandler* draw)
    {
        MyVector mousePos = MyVector(draw->getMouseLocation());
        
        MyVector projection = mLineDir * (mLineDir * mousePos);
        
        draw->drawLine(Point(0,0,0), (mLineDir * 20).toPoint(), WHITE, 0.1);
       
        draw->drawPoint(mousePos.toPoint(), BLUE, 0.2);
        draw->drawPoint(projection.toPoint(), GREEN, 0.2);
    }
    
    const virtual string getName()
    {
        return "Projection of mouse position on a line through origo";
    }
    const virtual string getInfo()
    {
        return "Move mouse to see the projection (green) of the mouse position (blue) onto the white line.";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */