#pragma once

#include <cstdint>

namespace Derelict {
	class Timer
	{
	public:
		virtual ~Timer() {};

		virtual float GetSeconds() const = 0;
		virtual float GetMilliseconds() const = 0;

		virtual float DeltaTime() const = 0;
		virtual float TotalTime() const = 0;

		virtual void Reset() = 0;
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual void Tick() = 0;

		static Timer* Create();
	};

}

