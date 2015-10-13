
using namespace std;

class SpaceDemo : public Demo
{
public:
	PhysicsHandler *handler;
	float G = 1.0f;//Inte riktigt stämmer överens med omskalningen
	EulerBall* Earth;
	EulerBall* Moon;
	float minR = 100.0f;
	float maxR = -100.0f;

	SpaceDemo()
	{
		handler = new PhysicsHandler();
		handler->STEP = 1.0 / 60.0;
		handler->G = 0.0f;
		handler->DAMPING = 0.0f;

		scenario_default();
	}

	void scenario_default()
	{
		handler->removeAll();

		//liknade värden till verkligheten men nerskalade med en faktor ~ 10^24
		Earth = new EulerBall(MyVector(5, 5), MyVector(0, 0), 0.597f, 0.637f, BLUE);
		Moon = new EulerBall(MyVector(8, 5), MyVector(0, 0.5), 0.007f, 0.173f, GREEN);

		handler->addBall(Earth);
		handler->addBall(Moon);

	}

	void update(DemoHandler* draw)
	{
		if (draw->isMouseDown())
		{
			Earth->setPosition(MyVector(draw->getMouseLocation()));
		}

		if (draw->keyTyped('r'))
		{
			scenario_default();
		}

		if (draw->keyTyped('q'))
		{
			G = 0;
		}

		if (draw->keyTyped('w'))
		{
			G = 1;
		}

		if (draw->keyTyped('e'))
		{
			G = 8;
		}

		//F = G*(M1 * M2)/r^2
		MyVector ForceDir = (Earth->getPosition() - Moon->getPosition());
		float r = ForceDir.length();
		ForceDir.normalize();
		MyVector F = ForceDir * (G * (Earth->getMass()*Moon->getMass()) / (r*r));

		Earth->addForce(-F);
		Moon->addForce(F);

		handler->updatePhysics();
		handler->handleCollisions();

		handler->drawPhysics(draw);

		if (r > maxR)
			maxR = r;
		if (r < minR)
			minR = r;

		ostringstream os;
		os << "F=" << F.length() << "N";
		draw->drawText(Moon->getPosition().toPoint(), os.str());
		os.str("");
		os << "R=" << r << "m";
		draw->drawText((Moon->getPosition() + MyVector(0, -0.3f)).toPoint(), os.str());
		os.str("");
		os << "maxR=" << maxR << "m";
		draw->drawText((Moon->getPosition() + MyVector(0, -0.6f)).toPoint(), os.str());
		os.str("");
		os << "minR=" << minR << "m";
		draw->drawText((Moon->getPosition() + MyVector(0, -0.9f)).toPoint(), os.str());

		os.str("");
		os << "G=" << G << "Nm^2/kg^2";
		draw->drawText((Earth->getPosition() + MyVector(0, 0)).toPoint(), os.str());

	}

	const virtual string getName()
	{
		return "Space: Anton Gustavsson & Jesper Mathiason";
	}
	const virtual string getInfo()
	{
		return	"You can move the earth by dragging\n"
			"[R]eset\n"
			"G: [q] 0, [w] 1, [e] 8\n";
	}
};
