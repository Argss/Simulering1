
using namespace std;

class ProjectPointOnArbitraryLine:public Demo
{
public:
    MyVector mLinePoint1 = MyVector(3,8,0);
    MyVector mLinePoint2 = MyVector(9,6,0);

    void update(DemoHandler* draw)
    {
        MyVector mousePos = MyVector( draw->getMouseLocation() );
        MyVector lineDir = mLinePoint2 - mLinePoint1;
        lineDir.normalize();
        
        MyVector mousePosLocal = mousePos - mLinePoint1;
        float projection =lineDir * mousePosLocal;
        MyVector projectionLocal = lineDir * projection;
        MyVector projectionGlobal = projectionLocal + mLinePoint1;
        
        draw->drawLine(mLinePoint1.toPoint(),mLinePoint2.toPoint(), WHITE, 0.1);
        draw->drawPoint(mousePos.toPoint(),BLUE,0.2);
        
        if(projection < 0)//projektionen är till vänster om segmentet
            draw->drawPoint(projectionGlobal.toPoint(),RED,0.2);
        else if(projection > (mLinePoint2-mLinePoint1).length())//projektionen är till höger om segmentet
            draw->drawPoint(projectionGlobal.toPoint(),PINK,0.2);
        else //projektionen är på segmentet
            draw->drawPoint(projectionGlobal.toPoint(),GREEN,0.2);
    }
    
    const virtual string getName()
    {
        return "Projection of mouse position on a line defined by to arbitrary points";
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