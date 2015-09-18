
using namespace std;

//used so you can change between float and double
typedef float Spring_RealNumber;
Spring_RealNumber SpringDamp;

class SpringDemo :public Demo
{
private:
	
	struct Spring
	{
		Ball* a;
		Ball* b;
		Spring_RealNumber constant;
		Spring_RealNumber restLength;

		void addForce()
		{
			//Get the vector between a and b
			MyVector dir = a->getPosition() - b->getPosition();
			Spring_RealNumber distance = dir.length();//in meters
			dir.normalize();

			//Calculate the springForce by using hooke's law
			MyVector springForce = (dir * (distance - restLength)) * -constant;

			a->addForce(springForce);
			a->addForce(-springForce * SpringDamp);// counter acting dampening force

			b->addForce(-springForce);
			b->addForce(springForce * SpringDamp);// counter acting dampening force
		}
	};
public:
	PhysicsHandler *handler;
	MyVector mSpringEnd = MyVector(6, 8, 0);
	std::vector<Ball*> mBalls;
	std::vector<Spring> mSprings;
	

	SpringDemo()
	{
		handler = new PhysicsHandler();
		handler->STEP = 1.0 / 60.0;

		scenario_default();	
	}

	void scenario_default()
	{
		handler->removeAll();

		mBalls.clear();
		mBalls.push_back(new EulerBall(MyVector(5, 5, 0)));
		handler->addBall(mBalls.back());
		mBalls.push_back(new EulerBall(MyVector(5, -5, 0)));
		handler->addBall(mBalls.back());
		mBalls.push_back(new EulerBall(MyVector(-5, 5, 0)));
		handler->addBall(mBalls.back());
		mBalls.push_back(new EulerBall(MyVector(-5, -5, 0)));
		handler->addBall(mBalls.back());

		SpringDamp = 0.5;

		mSprings.clear();
		mSprings.push_back({ mBalls[0], mBalls[1], 6.0, 2});
		mSprings.push_back({ mBalls[1], mBalls[2], 6.0, 2});
		mSprings.push_back({ mBalls[2], mBalls[0], 6.0, 2});
		mSprings.push_back({ mBalls[0], mBalls[3], 6.0, 2});
		mSprings.push_back({ mBalls[2], mBalls[3], 6.0, 2});
		mSprings.push_back({ mBalls[1], mBalls[3], 6.0, 2});

		addFloorAndWalls();
	}

	void scenario_three()
	{
		handler->removeAll();

		mBalls.clear();
		mBalls.push_back(new EulerBall(MyVector(5, 5, 0)));
		handler->addBall(mBalls.back());
		mBalls.push_back(new EulerBall(MyVector(5, -5, 0)));
		handler->addBall(mBalls.back());

		mBalls.push_back(new EulerBall(MyVector(-5, 5, 0)));
		handler->addBall(mBalls.back());

		SpringDamp = 0.5;

		mSprings.clear();
		mSprings.push_back({ mBalls[0], mBalls[1], 3.0, 2});
		mSprings.push_back({ mBalls[1], mBalls[2], 3.0, 2});
		mSprings.push_back({ mBalls[2], mBalls[0], 3.0, 2});

		addFloorAndWalls();
	}

	void scenario_insane()
	{
		handler->removeAll();

		mBalls.clear();

		for (int i = 0; i < 16; ++i)
		{
			
			mBalls.push_back(new EulerBall(MyVector((rand() % 12) - 6, (rand() % 12) - 6, 0)));
			handler->addBall(mBalls.back());
		}

		SpringDamp = 0.25;

		mSprings.clear();

		for (int i = 0; i < mBalls.size(); ++i)
		{
			for (int j = i; j < mBalls.size(); ++j)
			{
				mSprings.push_back({ mBalls[i], mBalls[j], (Spring_RealNumber) ((rand() % 2) + 2), (Spring_RealNumber) ((rand() % 2) + 2) });
			}
		}

		addFloorAndWalls();
	}

	void addFloorAndWalls()
	{
		//floor
		handler->addPlane(new Plane(MyVector(0, 0), MyVector(0, 1)));

		MyVector a(-1, .3);

		a.normalize();

		handler->addPlane(new Plane(MyVector(14, 0), a));
		handler->addPlane(new Plane(MyVector(1, 0), MyVector(-a.mX, a.mY)));
	}

	void update(DemoHandler* draw)
	{
		if (draw->isMouseDown())
		{
			mBalls[0]->setPosition(MyVector(draw->getMouseLocation()));
			mBalls[0]->setVelocity(MyVector());
		}

		if (draw->keyTyped('1'))
		{
			scenario_default();
		}

		if (draw->keyTyped('2'))
		{
			scenario_three();
		}

		if (draw->keyTyped('3'))
		{
			scenario_insane();
		}

		if (draw->keyTyped('a'))
		{
			SpringDamp = 0;
		}

		if (draw->keyTyped('s'))
		{
			SpringDamp = 0.25;
		}

		if (draw->keyTyped('d'))
		{
			SpringDamp = 0.5;
		}

		for (auto spring : mSprings)
		{
			spring.addForce();
		}

		handler->updatePhysics();
		handler->handleCollisions();

		handler->drawPhysics(draw);

		for (auto spring : mSprings)
		{
			draw->drawLine(spring.a->getPosition().toPoint(), spring.b->getPosition().toPoint(), CYAN, 0.05);
		}

		ostringstream os;
		os << "SpringDamp=" << SpringDamp;
		draw->drawText(Point(5, 5, 0), os.str());

	}

	const virtual string getName()
	{
		return "Springs: Anton Gustavsson & Jesper Mathiason";
	}
	const virtual string getInfo()
	{
		return	"You can move the one of the balls with your mouse by dragging.\n"
				"Scenarios: [1] Default, [2] Three soft, [3] Insane\n"
				"SpringDamp: [a] Zero, [b] 0.25, [c] 0.5\n";
	}
};
