#ifndef UTILS_H
#define UTILS_H

namespace dungeon {

// Template function
template <typename T>
T clampValue(const T& value, const T& min, const T& max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

} // namespace dungeon

#endif
