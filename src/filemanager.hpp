#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "commons.hpp"
#include "ecsdb.hpp"
#include <map>

#include <iostream>

class FileManager{
private:
	std::map<RGB, char> char_map;
	void eat_comment(std::ifstream &f);
public:
	// 귀찮아서 잠시 뺴둠
	int width, height;
	char** color_map;

	void load_ppm(const std::string& name);
	void load_file(ECSDB& db);

	void debug_print(){
		for (int i =0; i < width; i++){
			for (int j =0; j < height; j++){
				//if (color_map[i][j] == '@' ||color_map[i][j] == '#') {
					//std::cout << i << " " << j << "\n";
				//}
				std::cout << color_map[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
};

#endif
