/**
 * @file string.cpp
 *
 * @author 육심현
 *
 */

#include "string.hpp"
#include <map>

const std::map<std::string, const char> char_map = std::map<std::string, const char>{
	{"empty", '`'},{"head", '@'},{"tail", '#'},{"wall", '*'},{"iwall",'H'},{"growth",'P'},{"poison",'X'},{"gate",'O'}
};
