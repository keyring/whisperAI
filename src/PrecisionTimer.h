/****************************************************************************
 *
 *    PrecisionTimer.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 ***************************************************************************/

#ifndef __PRECISIONTIMER_H__
#define __PRECISIONTIMER_H__

#include <windows.h>
#include <cassert>

class PrecisionTimer{

 private:
  LONGLONG m_currentTime,
    m_lastTime,
    m_lastTimeInTimeElapsed,
    m_nextTime,
    m_startTime,
    m_frameTime,
    m_perfCountFreq;

  double m_timeElapsed,
    m_lastTimeElapsed,
    m_timeScale;

  double m_normalFPS, m_slowFPS;

  bool m_started;
  bool m_smoothUpdates;

 public:
  PrecisionTimer();
  PrecisionTimer(double fps);

  void Start();
  inline bool ReadyForNextFrame();
  inline double TimeElapsed();

  double CurrentTime(){
    QueryPerformanceCounter((LARGE_INTEGER*)&m_currentTime);
    return (m_currentTime - m_startTime) * m_timeScale;
  }

  bool IsStarted() const { return m_started; }

  void SmoothUpdatesOn(){ m_smoothUpdates = true; }
  void SmoothUpdatesOff(){ m_smoothUpdates = false; }
};



#endif	/* __PRECISIONTIMER_H__ */
