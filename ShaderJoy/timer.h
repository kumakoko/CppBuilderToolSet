// $Id: timer.h,v 1.8 2004/08/31 16:37:22 toolshed Exp $

#pragma once

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

#include <cstdint>

/**
 * Timer class.  Keeps track of elapsed time.
 * Can also be used as a stopwatch.
 */
class C_Timer {
 public:
  /**
   * default constructor, resets timer
   */
  C_Timer();

  /**
   * update the timer, must be called each frame
   *
   * Must be called each frame to tell the timer that a frame has passed.
   */
  void Update();
  /**
   * reset the timer to time 0
   */
  void Reset();

  /**
   * timer modulus
   * @param interval the interval in seconds to mod the time by
   * @param startTime an offset time to start the modulus at
   * @return 0 if the interval has passed, or the amount of time that actually
   * passed ( < interval )
   *
   * Takes interval (in seconds) and checks (interval % time).
   * So, for example, if you want an animation to go off every .5 seconds you
   * would do this:\n if (TimeMod(0.5f) == 0) { //Do animation ...\n Parameter
   * startTime defaults to NULL which is fine for most applications.
   */
  double TimeMod(const double& interval, double startTime = 0.0);

  /**
   * Get the time since the clock was started.
   * @return time since time 0 (last Reset()) in seconds
   */
  double GetTime() const;
  /**
   * Get the time elapsed in the last frame.
   * @return time since last frame (last Update()) in seconds
   */
  double GetElapsed();
  /**
   * Get the current low level clock tick number.
   * @return current clock tick
   */
  int GetTick() const;
  /**
   * Calculate frames per second
   * @return calculated frames per second
   *
   * GetFPS caches return value until next update.
   */
  double GetFPS() const;
  /**
   * Get the current frame count.
   * @return number of frames since time 0 (last Reset())
   */
  int GetFrameCount() const;

  static bool paused;

 private:
  std::int64_t startTick;  ///< performance ticker at time 0 (last Reset())
  std::int64_t lastTick;   ///< performance ticker last frame (last Update())
  std::int64_t frequency;  ///< ticks per second of the clock
  std::int64_t elapsed;    ///< elapsed ticks since last frame (last Update())
  bool elapsedCached;      ///< true if elapsed has been cached
  double elapsedCache;     ///< cached elapsed value
  std::int64_t time;       ///< total elapsed ticks since time 0 (last Reset())
  int frameCount;          ///< number of frames since time 0 (last Reset())
};
