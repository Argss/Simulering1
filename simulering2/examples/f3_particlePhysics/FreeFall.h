
using namespace std;

class FreeFall:public Demo
{
public:
    ostringstream os;
    double airResistanceFactor = 0.001;

    void fall()
    {
        double g = -10; // m/s^2
        double p = 10000;// m
        double v = 0;// m/s
        double m = 0.1;// kg
        double step = 0.01;
        
        for( int i=0; i < 40 / step; i++)
        {
            p = p + step *v;
            double F = m * g;
            F = F - airResistanceFactor * abs(v) * v;
            v = v + step * F / m;
        }
        
        os.str("");
        os << "Position: " << p << " m.  Velocity:" << v << " m/s";
    }
    void update(DemoHandler* draw)
    {
        if(draw->keyTyped('1'))
        {
                fall();
        }
       
        draw->drawText(Point(1,1,0), os.str());
    }
    
    const virtual string getName()
    {
        return "Ball falls in 40 seconds";
    }
    const virtual string getInfo()
    {
        return "Press 1 to compute free fall\nPress 2 to compute with air resistance";
    }
};


/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */