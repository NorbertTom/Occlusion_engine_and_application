#pragma once
#include <iostream>
#include <chrono>

#include "SoundAPI.h"

namespace BasicMath {

	const float PI = 3.14f;

	class SOUND_API Point
	{
	public:
		virtual float getPosX() const;
		virtual float getPosY() const;
		virtual const float* getPosXPtr() const;
		virtual const float* getPosYPtr() const;

		void setPosX(float newX);
		void setPosY(float newY);

		Point();
		Point(float X, float Y);

	private:
		float x, y;
	};

	class SOUND_API TwoPoints : public Point
	{
	public:
		float getPosX1() const;
		float getPosY1() const;
		float getPosX2() const;
		float getPosY2() const;
		const float* getPosY2Ptr() const;
		const float* getPosX1Ptr() const;
		const float* getPosY1Ptr() const;
		const float* getPosX2Ptr() const;
		void setPosX1(float newX1);
		void setPosY1(float newY1);
		void setPosX2(float newX2);
		void setPosY2(float newY2);

		TwoPoints();
		TwoPoints(float X1, float Y1, float X2, float Y2);

	private:
		float getPosX() const override;
		float getPosY() const override;
		const float * getPosXPtr() const override;
		const float * getPosYPtr() const override;
		float x2, y2;
	};

	struct Line
	{
		float a, b;
		Line(float, float);
	};

	struct MovementVector
	{
		float changeX, changeY;
		MovementVector() : changeX(0), changeY(0) {};
	};

	struct Timer
	{
		float* m_ptr = nullptr;
		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::duration<double> duration;

		Timer();
		Timer(float* ptr);
		~Timer();

	};

	inline void MinMax(float & min, float & max, float a, float b)
	{
		if (a < b)
		{
			min = a;
			max = b;
		}
		else
		{
			min = b;
			max = a;
		}
	}

	inline float squaredDistance(float x1, float y1, float x2, float y2)
	{
		return powf(x2 - x1, 2) + powf(y2 - y1, 2);
	}

}