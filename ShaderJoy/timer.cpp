// $Id: timer.cpp,v 1.8 2004/08/31 16:37:22 toolshed Exp $

/*
   DXFramework -- "The Engin Engine"
   Copyright (c) 2004, Corey Johnson, Jonathan Voigt, Nuttapong Chentanez
   Contributions by Adam Tercala, Jeremy Lee, David Yeung, Evan Leung,
   Parker Hamilton, Cory Dunham
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

      * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

      * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

      * Neither the name of the DXFramework project nor the names of its
      contributors may be used to endorse or promote products derived from this
      software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. *
 */

#include "timer.h"

#include <windows.h>

bool C_Timer::paused = false;

C_Timer::C_Timer() {
  Reset();  // reset the clock when it's created
}

void C_Timer::Update() {
  // cache invalid
  elapsedCached = false;

  // increment frame count
  ++frameCount;

  // update clock state
  QueryPerformanceCounter((LARGE_INTEGER *)&startTick);
  elapsed = startTick - lastTick;
  lastTick = startTick;

  // don't add to elapsed if paused
  if (paused) return;

  // add to elapsed
  time += elapsed;
}

void C_Timer::Reset() {
  QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);  // ticks per second
  QueryPerformanceCounter(
      (LARGE_INTEGER *)&startTick);  // where we're at now...

  lastTick = startTick;  // is where we began

  time = 0;  // reset time variables
  elapsed = 0;
  elapsedCache = 0;
  elapsedCached = false;
  frameCount = 0;
}

double C_Timer::GetFPS() const {
  return elapsed ? 1 / ((double)elapsed / frequency) : 0;
}

double C_Timer::TimeMod(const double &d_interval, double d_startTime) {
  auto startTime = static_cast<std::int64_t>(d_startTime * frequency);
  auto interval = static_cast<std::int64_t>(d_interval * frequency);

  if (startTime == NULL) {
    startTime = time;
  } else {
    startTime = time - startTime;
  }

  // If the current time % interval is smaller than the last time % interval
  // then you know that between those times the time interval passed.
  if (startTime % interval < (startTime - elapsed) % interval) {
    return 0;
  }
  return (startTime % interval) / static_cast<double>(frequency);
}

double C_Timer::GetTime() const {
  return time / static_cast<double>(frequency);
}

double C_Timer::GetElapsed() {
  if (!elapsedCached) {
    elapsedCache = elapsed / static_cast<double>(frequency);
    elapsedCached = true;
  }
  return elapsedCache;
}

int C_Timer::GetTick() const { return static_cast<int>(lastTick); }

int C_Timer::GetFrameCount() const { return frameCount; }
