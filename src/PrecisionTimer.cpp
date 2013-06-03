/**************************************************************************
 *
 *    PrecisionTimer.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *************************************************************************/

#include "PrecisionTimer.h"

PrecisionTimer::PrecisionTimer(): m_normalFPS(0.0),
				  m_slowFPS(1.0),
				  m_timeElapsed(0.0),
				  m_frameTime(0),
				  m_lastTime(0),
				  m_lastTimeInTimeElapsed(0),
				  m_perfCountFreq(0),
				  m_started(false),
				  m_startTime(0),
				  m_lastTimeElapsed(0.0),
				  m_smoothUpdates(false) {

  QueryPerformanceFrequency((LARGE_INTEGER*)&m_perfCountFreq);
  m_timeScale = 1.0 / m_perfCountFreq;
}

PrecisionTimer::PrecisionTimer(double fps) : m_normalFPS(fps),
					     m_slowFPS(1.0),
					     m_timeElapsed(0.0),
					     m_frameTime(0),
					     m_lastTime(0),
					     m_lastTimeInTimeElapsed(0),
					     m_perfCountFreq(0),
					     m_started(false),
					     m_startTime(0),
					     m_lastTimeElapsed(0.0),
					     m_smoothUpdates(false) {


  QueryPerformanceFrequency((LARGE_INTEGER*)&m_perfCountFreq);
  m_timeScale = 1.0 / m_perfCountFreq;
  m_frameTime = (LONGLONG)(m_perfCountFreq / m_normalFPS);
}

void PrecisionTimer::Start(){

  m_started = true;
  m_timeElapsed = 0.0;
  QueryPerformanceCounter((LARGE_INTEGER*)&m_lastTime);
  m_startTime = m_lastTimeInTimeElapsed = m_lastTime;
  m_nextTime = m_lastTime + m_frameTime;
}
