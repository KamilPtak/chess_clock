#pragma once

#include "../utils/optional.h"
#include <stdint.h>

// Player time management - tracks remaining time and increments
namespace player {

struct RemainingTime {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
  uint16_t milliseconds;

  explicit RemainingTime(uint8_t h = 0, uint8_t m = 0, uint8_t s = 0,
                         uint16_t ms = 0)
      : hours(h), minutes(m), seconds(s), milliseconds(ms) {}
};

class PlayerTime {
public:
  PlayerTime(uint8_t hours, uint8_t minutes, uint8_t seconds,
             optional<uint8_t> incrementSeconds,
             optional<uint8_t> incrementMinutes);

  uint32_t getInitialMilliseconds() const { return initialMilliseconds; }
  uint32_t getRemainingMilliseconds() const { return remainingMilliseconds; }
  uint32_t getIncrementMilliseconds() const { return incrementMilliseconds; }
  uint32_t getIncrementSeconds() const {
    return incrementMilliseconds / kMsPerSecond;
  }
  bool isExpired() const { return remainingMilliseconds == 0; }
  const RemainingTime &get_remaining_time() const;

  void decreaseByMilliseconds(uint32_t ms);
  void increaseBySeconds(uint32_t seconds);

private:
  static constexpr uint32_t kMsPerSecond = 1000u;
  static constexpr uint32_t kMsPerMinute = 60u * kMsPerSecond;
  static constexpr uint32_t kMsPerHour = 60u * kMsPerMinute;

  static constexpr uint_fast32_t kSecPerMinute = 60u;
  static constexpr uint_fast32_t kSecPerHour = 60u * kSecPerMinute;

  const uint32_t incrementMilliseconds;
  const uint32_t initialMilliseconds;
  uint32_t remainingMilliseconds;
  mutable RemainingTime cachedRemainingTime;
  mutable bool isDirty;

  void updateCache() const;
};

} // namespace player