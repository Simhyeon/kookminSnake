#include "portal.hpp"
#include <chrono>

Portal::Portal(Position first, Position second): timestamp(Util::get_time()), first(first), second(second) { }
