#include "player/player_time.h"

namespace player {

PlayerTime::PlayerTime(uint8_t hours, uint8_t minutes, uint8_t seconds,
                       optional<uint8_t> incrementSeconds,
                       optional<uint8_t> incrementMinutes)
    : incrementMilliseconds(
          static_cast<uint32_t>(incrementSeconds.value_or(0)) * kMsPerSecond +
          static_cast<uint32_t>(incrementMinutes.value_or(0)) * kSecPerMinute *
              kMsPerSecond),
      initialMilliseconds(static_cast<uint32_t>(hours) * kMsPerHour +
                          static_cast<uint32_t>(minutes) * kMsPerMinute +
                          static_cast<uint32_t>(seconds) * kMsPerSecond),
      remainingMilliseconds(initialMilliseconds),
      cachedRemainingTime(hours, minutes, seconds, 0), isDirty(false) {}

void PlayerTime::updateCache() const {
  if (isDirty) {
    uint32_t totalMs = remainingMilliseconds;
    uint32_t totalSeconds = totalMs / kMsPerSecond;

    uint8_t h = totalSeconds / kSecPerHour;
    uint8_t m = (totalSeconds % kSecPerHour) / kSecPerMinute;
    uint8_t s = totalSeconds % kSecPerMinute;
    uint16_t ms = totalMs % kMsPerSecond;

    cachedRemainingTime = RemainingTime(h, m, s, ms);
    isDirty = false;
  }
}

void PlayerTime::decreaseByMilliseconds(const uint32_t ms) {
  ms >= remainingMilliseconds ? remainingMilliseconds = 0
                              : remainingMilliseconds -= ms;
  isDirty = true;
}

void PlayerTime::increaseBySeconds(const uint32_t seconds) {
  remainingMilliseconds += seconds * kMsPerSecond;
  isDirty = true;
}

const RemainingTime &PlayerTime::get_remaining_time() const {
  updateCache();
  return cachedRemainingTime;
}

} // namespace player
