
using namespace std;

class DistanceToPlane:public Demo
{
public:
    MyVector mPointinplane; // en (godtycklig bortsett från ritandet) punkt i planet
    MyVector mNormal; // planets normal
    
    DistanceToPlane()
    {
        mPointinplane = MyVector(2, 2, 0);
        mNormal = MyVector(1, 1, 1);
        mNormal.normalize();
    }
    void update(DemoHandler* draw)
    {
        MyVector mousePos = MyVector( draw->getMouseLocation() );

        
        MyVector mousePosLocal = mousePos - mPointinplane;
        float distance = mousePosLocal * mNormal;
        
        MyVector closestPointLocal = mousePosLocal - mNormal * distance;
        MyVector closestPointGlobal = closestPointLocal + mPointinplane;
        
        draw->drawPlane( mPointinplane.toPoint(), mNormal.toPoint(), GREEN, 15 );
        
        draw->drawLine(closestPointGlobal.toPoint(), mousePos.toPoint(), WHITE, 0.1);
        draw->drawPoint(mousePos.toPoint(),BLUE,0.3);
        draw->drawPoint(closestPointGlobal.toPoint(),CYAN,0.3);
        ostringstream os;
        os << "Distance: " << distance << " m.";
        draw->drawText(mousePos.toPoint(), os.str());
        
    }
    
    const virtual string getName()
    {
        return "Projects the mouse point onto a plane.";
    }
    const virtual string getInfo()
    {
        return "Change to perspective view to see the projection.";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */