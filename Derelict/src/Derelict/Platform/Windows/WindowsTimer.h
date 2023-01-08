#pragma once

#include "../../Core/Timer.h"

#include <windows.h>

namespace Derelict {
	class WindowsTimer : public Timer
	{
	public:
		WindowsTimer();
		virtual ~WindowsTimer() {}

		virtual float GetSeconds() const override;
		virtual float GetMilliseconds() const override;

		float GameTime() const override;
		float DeltaTime() const override;
		float TotalTime() const override;

		virtual void Reset() override;
		virtual void Start() override;
		virtual void Stop() override;
		virtual void Tick() override;

	private:
		double m_SecondsPerCount;
		double m_DeltaTime;
		int64_t m_BaseTime;
		int64_t m_PausedTime;
		int64_t m_StopTime;
		int64_t m_CurrTime;
		int64_t m_PrevTime;
		bool m_Stopped;
	};
}

