
using namespace std;

class EmptyDemo : public Demo
{

public:
	
	EmptyDemo()
	{

	}

	void update(DemoHandler* draw)
	{
		
	}

	const virtual string getName()
	{
		return "Load our demo";
	}
	const virtual string getInfo()
	{
		return	"";
	}
};
