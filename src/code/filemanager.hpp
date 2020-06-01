#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "commons.hpp"
#include "ecsdb.hpp"
#include <map>
#include <iostream>

class FileManager{
private:
	void eat_comment(std::ifstream &f);
	void load_file(const std::string& file);
	void load_ppm(const std::string& ppm);
	void update_db(ECSDB &db);

	std::string ppm_name;
	int width, height;
	int growth_counter, poison_counter;
	char** color_map;
	int snake_direction;

	const std::map<int, std::string> level_name = {
		{1, "1.yml"},
		{2, "2.yml"},
		{3, "3.yml"},
		{4, "4.yml"},
		{5, "5.yml"}
	};

public:
	void process(int level, ECSDB &db);
};

#endif
