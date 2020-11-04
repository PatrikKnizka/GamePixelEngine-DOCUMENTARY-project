#define OLC_PGE_APPLICATION
#include "lib/olcPixelGameEngine/olcPixelGameEngine.h"

class BreakOut : public olc::PixelGameEngine
{
public:
	BreakOut()
	{
		sAppName = "BreakOut Clone";
	}

private:
	float fbatPos = 15.0f;
	float fbatWidth = 40.0f;
	float fbatSpeed = 0.3f;

	float fballRadius = 5.0f;
	olc::vf2d vballVel = { 200.0f, -100.0f };
	olc::vf2d vBall = { 200.0f, 200.0f };



public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/*Moving bad*/
		if (GetKey(olc::Key::LEFT).bHeld) fbatPos -= fbatSpeed;
		if (GetKey(olc::Key::RIGHT).bHeld) fbatPos += fbatSpeed;
		if (fbatPos < 11.0f) fbatPos = 11.0f;
		if (fbatPos + fbatWidth > float(ScreenWidth()) - 10.0f) fbatPos = float(ScreenWidth()) - 10.0f - fbatWidth;

		/*Update ball*/
		vBall += vballVel * fElapsedTime;

		/*Area detection*/
		if (vBall.y <= 10.0f) vballVel.y *= -1.0f;
		if (vBall.x <= 10.0f) vballVel.x *= -1.0f;
		if (vBall.x >= float(ScreenWidth()) - 10.0f) vballVel.x *= -1.0f;

		/*Check ball colision with bat*/
		if (vBall.y >= (float(ScreenHeight()) - 20.0f) && (vBall.x > fbatPos) && (vBall.x < fbatPos + fbatWidth))
		{
			vballVel.y *= -1.0f;
		}


		/*Check if ball is off screen*/
		if (vBall.y > ScreenHeight())
		{
			/*Ball reset*/
			vBall = { 200.0f, 200.0f };
			/*Choose random angle to start*/
			float fAngle = (float(rand()) / float(RAND_MAX)) * 2.0f * 3.14159f;
			vballVel = { 300.0f * cos(fAngle), 300.0f * sin(fAngle) };
		}


		/*Cheat! Moving and getting ball bigger*/
		/*
		 
		if (GetMouse(0).bHeld)
		{
			vBall = { float(GetMouseX()), float(GetMouseY()) };
		}
		if (GetMouseWheel() > 0) fballRadius += 1.0f;
		if (GetMouseWheel() < 0) fballRadius -= 1.0f;
		if (fballRadius < 5.0f) fballRadius = 5.0f;
		if (fballRadius > 20.0f) fballRadius = 20.0f;

		*/


		/*Erase previous frame*/
		Clear(olc::BLACK);

		/*Draw arena*/
		DrawLine(10, 10, ScreenWidth() - 10, 10, olc::WHITE);
		DrawLine(10, 10, 10, ScreenHeight() - 10, olc::WHITE);
		DrawLine(ScreenWidth() - 10, 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::WHITE);

		/*Draw rocket*/
		FillRect(int(fbatPos), ScreenHeight() - 20, fbatWidth, 10, olc::WHITE);

		// Draw Ball
		FillCircle(vBall, fballRadius, olc::YELLOW);

		return true;
	}
};

int main()
{
	BreakOut demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();
	return 0;
}