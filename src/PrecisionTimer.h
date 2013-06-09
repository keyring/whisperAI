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

inline bool PrecisionTimer::ReadyForNextFrame(){

  assert( m_normalFPS && "PrecisionTimer::ReadyForNextFrame<No FPS set in timer>" );
  QueryPerformanceCounter((LARGE_INTEGER*)&m_currentTime);

  if(m_currentTime > m_nextTime){
    m_timeElapsed = (m_curentTime - m_lastTime) * m_timeScale;
    m_lastTime = m_currentTime;

    m_nextTime = m_currentTime + m_frameTime;

    return true;
  }

  return false;
}

inline double PrecisionTimer::TimeElapsed(){

  m_lastTimeElapsed = m_timeElapsed;
  QueryPerformanceCounter((LARGE_INTEGER*)&m_currentTime);
  m_timeElapsed = (m_currentTime - m_lastTimeInTimeElapsed) * m_timeScale;
  m_lastTimeInTimeElapsed = m_currentTime;

  const double smoothness = 5.0;

  if(m_smoothUpdates){
    if(m_timeElapsed < (m_lastTimeElapsed * smoothness))
      return m_timeElapsed;
    else
      return 0.0;
  }
  else{
    return m_timeElapsed;
  }
}


#endif	/* __PRECISIONTIMER_H__ */
