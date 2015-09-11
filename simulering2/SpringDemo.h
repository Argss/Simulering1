
using namespace std;

class SpringDemo :public Demo
{
private:
	typedef float RealNumber;
	struct Spring
	{
		Ball* a;
		Ball* b;
		RealNumber constant;
		RealNumber restLength;

		void ApplyForce()
		{
			MyVector dir = a->getPosition() - b->getPosition();
			RealNumber distance = dir.length();
			dir.normalize();

			MyVector springForce = (dir * (distance - restLength)) * -constant;

			a->addForce(springForce * 0.5);
			b->addForce(-springForce * 0.5);
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
		handler->STEP = 1.0 / 100.0;
		//handler->G = 0.0;

		mBalls.push_back(new EulerBall(MyVector(5, 5, 0)));
		handler->addBall(mBalls.back());
		mBalls.push_back(new EulerBall(MyVector(5, -5, 0)));
		handler->addBall(mBalls.back());
		mBalls.push_back(new EulerBall(MyVector(-5, 5, 0)));
		handler->addBall(mBalls.back());
		mBalls.push_back(new EulerBall(MyVector(-5, -5, 0)));
		handler->addBall(mBalls.back());

		mSprings.push_back({ mBalls[0], mBalls[1], 8.0, 2 });
		mSprings.push_back({ mBalls[1], mBalls[2], 8.0, 2 });
		mSprings.push_back({ mBalls[2], mBalls[0], 8.0, 2 });
		mSprings.push_back({ mBalls[0], mBalls[3], 8.0, 2 });
		mSprings.push_back({ mBalls[2], mBalls[3], 8.0, 2 });
		mSprings.push_back({ mBalls[1], mBalls[3], 8.0, 2 });
	}

	void update(DemoHandler* draw)
	{
		if (draw->isMouseDown())
		{
			mBalls[0]->setPosition(MyVector(draw->getMouseLocation()));
			mBalls[0]->setVelocity(MyVector());
		}
			for (auto spring : mSprings)
			{
				spring.ApplyForce();
			}

			handler->updatePhysics();

		


		handler->drawPhysics(draw);

		for (auto spring : mSprings)
		{
			draw->drawLine(spring.a->getPosition().toPoint(), spring.b->getPosition().toPoint(), WHITE, 0.05);
		}

		//ostringstream os;
		//os << "Ks=" << mSpringConstant;
		//draw->drawText(mSpringEnd.toPoint(), os.str());

	}

	const virtual string getName()
	{
		return "JESPERS BRA DEMO :)";
	}
	const virtual string getInfo()
	{
		return "Figure it out idiot ;)";
	}
};
