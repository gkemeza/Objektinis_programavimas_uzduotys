#include <chrono>
using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::time_point;

class Timer {
  using hrClock = high_resolution_clock;

private:
  time_point<hrClock> start;

public:
  Timer() : start{hrClock::now()} {}
  void reset() { start = hrClock::now(); }
  double elapsed() const {
    return duration<double>(hrClock::now() - start).count();
  }
};
