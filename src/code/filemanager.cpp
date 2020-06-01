#include "filemanager.hpp"
#include "commons.hpp"
#include <fstream>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/parser.h>
#include <yaml-cpp/yaml.h>

void FileManager::eat_comment(std::ifstream &f){
	char linebuff[1024];
	char ppp;
	while (ppp = f.peek(), ppp == '\n' || ppp == '\r')
		f.get();
	if (ppp == '#')
		f.getline(linebuff, 1023);
}

void FileManager::load_file(const std::string& file){
	YAML::Node level = YAML::LoadFile(file);
	snake_direction = level["direction"].as<int>();
	ppm_name = level["ppm_file"].as<std::string>();
	growth_counter = level["growth"].as<int>();
	poison_counter = level["poison"].as<int>();
	
	ppm_name.insert(0, "src/assets/ppm/");
}

void FileManager::load_ppm(const std::string& name){

	std::ifstream f(name.c_str(), std::ios::binary);
	if (f.fail())
	{
		std::cout << "Could not open file: " << name << std::endl;
	    return;
	}
	
	// get type of file
	eat_comment(f);
	int mode = 0;
	std::string s;
	f >> s;
	if (s == "P3")
	    mode = 3;
	else if (s == "P6")
	    mode = 6;
	
	// get w
	eat_comment(f);
	f >> width;
	
	// get h
	eat_comment(f);
	f >> height;
	
	// get bits
	eat_comment(f);
	int bits = 0;
	f >> bits;
	
	// error checking
	if (mode != 3)
	{
		std::cout << "Only ascii file format is accepted" << std::endl;
	    f.close();
	    return ;
	}
	
	if (width < 1)
	{
		std::cout << "Width is too short" << std::endl;
	    f.close();
	    return ;
	}
	if (height < 1)
	{
		std::cout << "Height is too short" << std::endl;
	    f.close();
	    return ;
	}
	if (bits != 255)
	{
		std::cout << "Only 255 color is supported" << std::endl;
	    f.close();
	    return ;
	}

	color_map = new char*[width];
	for(int i = 0; i < width; ++i) {
	    color_map[i] = new char[height];
	}

	int r,g,b;
	for (int i =0; i < width; i++){
		for (int j =0; j < height; j++){
			f >> r;
			f >> g;
			f >> b;
			color_map[j][i] = static_cast<char>(RGB(r,g,b));
		}
	}

    // close file
    f.close();
}

void FileManager::process(int level, ECSDB &db){
	std::string path = level_name.at(level);
	path.insert(0, "src/assets/level/");
	load_file(path);
	load_ppm(ppm_name);
	db.Init(width, height, color_map, static_cast<DIRECTION>(snake_direction));
	std::cout << "Width : " << width << "\n";
	std::cout << "height : " << height << "\n";
	std::cout << "ppm_name : " << ppm_name << "\n";
	std::cout << "growth : " << growth_counter << "\n";
	std::cout << "poison : " << poison_counter << "\n";
	std::cout << "Direction : " << snake_direction << "\n";
}
