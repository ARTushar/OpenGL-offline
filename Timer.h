//
// Created by tushar on 3/16/21.
//

#include <chrono>

#ifndef INC_1605070_TIMER_H
#define INC_1605070_TIMER_H

#endif //INC_1605070_TIMER_H

class Timer
{
    int timeLimit = 2000;
    std::chrono::time_point<std::chrono::system_clock> startTime, currentTime;

public:
    Timer() = default;

    explicit Timer(const int &timeLimit)
    {
      this->timeLimit = timeLimit;
    }

    void startTimer()
    {
      startTime = std::chrono::high_resolution_clock::now();
    }

    int elapsedMillis()
    {
      currentTime = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    }

    bool timesUp(int time) {
      return elapsedMillis() > time;
    }

    bool timesUp()
    {
      return elapsedMillis() > timeLimit;
    }
};