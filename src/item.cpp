#include "item.hpp"
#include "commons.hpp"

Item::Item(): timestamp(Util::get_time()){}
Item::Item(Position pos): timestamp(Util::get_time()), pos(pos) {}
