#include "BaseClassesFunctions.h"
#include "ErrorLogging.h"

#include <string>

namespace Tests { void PrintErrorLogToFile(std::string &&); }

namespace BasicMath {

	Line::Line(float A, float B) : a(A), b(B) {}

	float Point::getPosX() const { return x; }
				 
	float Point::getPosY() const { return y; }

	const float* Point::getPosXPtr() const { return &x; }
	const float* Point::getPosYPtr() const { return &y; }

	void Point::setPosX(float newX) { x = newX; }
	void Point::setPosY(float newY) { y = newY; }

	Point::Point() : x(0), y(0) {}

	Point::Point(float X, float Y) : x(X), y(Y) {}

	float TwoPoints::getPosX() const { LOG_ERROR("Using getPosX() on TwoPoint object!"); return 0; }
	float TwoPoints::getPosY() const { LOG_ERROR("Using getPosY() on TwoPoint object!"); return 0; }

	const float* TwoPoints::getPosXPtr() const { LOG_ERROR("Using getPosXPtr() on TwoPoint object!"); return nullptr; }
	const float* TwoPoints::getPosYPtr() const { LOG_ERROR("Using getPosYPtr() on TwoPoint object!"); return nullptr; }

	float TwoPoints::getPosX1() const { return Point::getPosX(); }
	float TwoPoints::getPosY1() const { return Point::getPosY(); }
	float TwoPoints::getPosX2() const { return x2; }
	float TwoPoints::getPosY2() const { return y2; }
	
	const float* TwoPoints::getPosX1Ptr() const { return Point::getPosXPtr(); }
	const float* TwoPoints::getPosY1Ptr() const { return Point::getPosYPtr(); }
	const float* TwoPoints::getPosX2Ptr() const { return &x2; }
	const float* TwoPoints::getPosY2Ptr() const { return &y2; }

	void TwoPoints::setPosX1(float newX1) { setPosX(newX1); }
	void TwoPoints::setPosY1(float newY1) { setPosY(newY1); }
	void TwoPoints::setPosX2(float newX2) { x2 = newX2; }
	void TwoPoints::setPosY2(float newY2) { y2 = newY2; }

	TwoPoints::TwoPoints() : Point(), x2(0), y2(0) {};
	TwoPoints::TwoPoints(float X1, float Y1, float X2, float Y2)
		: Point(X1, Y1), x2(X2), y2(Y2) {};


	Timer::Timer()
	{
		using namespace std::literals::chrono_literals;
		start = std::chrono::high_resolution_clock::now();
	}

	Timer::Timer(float* ptr) : Timer()
	{
		m_ptr = ptr;
	}

	Timer::~Timer()
	{
		using namespace std::literals::chrono_literals;
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		float ms = duration.count() * 1000.0f;
		if (m_ptr)
		{
			*m_ptr = ms;
		}
		else
		{
			Tests::PrintErrorLogToFile("It took " + std::to_string(ms) + " ms");
		}
	}

}