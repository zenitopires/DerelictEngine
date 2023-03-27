#include "WindowsTimer.h"

namespace Derelict {

	Timer* Timer::Create()
	{
		return new WindowsTimer();
	}

	WindowsTimer::WindowsTimer()
		: m_SecondsPerCount(0.0), m_DeltaTime(-1.0), m_BaseTime(0),
		m_PausedTime(0), m_PrevTime(0), m_CurrTime(0), m_Stopped(0)
	{
		int64_t countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_SecondsPerCount = 1.0 / static_cast<double>(countsPerSec);
	}

	float WindowsTimer::GetSeconds() const
	{
		return 0.0f;
	}

	float WindowsTimer::GetMilliseconds() const
	{
		return 0.0f;
	}

	float WindowsTimer::TotalTime() const
	{
		if (m_Stopped)
		{
			return static_cast<float>(((m_StopTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
		}
		else
		{
			return static_cast<float>(((m_CurrTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
		}
	}

	float WindowsTimer::DeltaTime() const
	{
		return static_cast<float>(m_DeltaTime);
	}

	void WindowsTimer::Reset()
	{
		int64_t currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_BaseTime = currTime;
		m_PrevTime = currTime;
		m_StopTime = 0;
		m_Stopped = false;
	}

	void WindowsTimer::Start()
	{
		int64_t startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

		if (m_Stopped)
		{
			m_PausedTime += (startTime - m_StopTime);

			m_PrevTime = startTime;
			m_StopTime = 0;
			m_Stopped = false;
		}
	}

	void WindowsTimer::Stop()
	{
		if (!m_Stopped)
		{
			int64_t currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			m_StopTime = currTime;
			m_Stopped = true;
		}
	}

	void WindowsTimer::Tick()
	{
		if (m_Stopped)
		{
			m_Stopped = 0.0f;
			return;
		}

		int64_t currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		m_CurrTime = currTime;

		// Time diff betwen this frame and previous frame
		m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

		m_PrevTime = m_CurrTime;

		if (m_DeltaTime < 0.0f)
		{
			m_DeltaTime = 0.0f;
		}
	}

}