#include "filemanager.hpp"
#include "commons.hpp"
#include <fstream>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/parser.h>
#include <yaml-cpp/yaml.h>

// ppm 파일은 헤더에서 주석이 아무때나 나올 수 있는데 
// 해당 주석은 읽어들인뒤 사용하지 않고 버린다.
void FileManager::eat_comment(std::ifstream &f){
	char linebuff[1024];
	char ppp;
	while (ppp = f.peek(), ppp == '\n' || ppp == '\r')
		f.get();
	if (ppp == '#')
		f.getline(linebuff, 1023);
}

// YAML 파일을 읽어들여 필요한 값을 추출한다.
// 읽어오는 정보는 다음과 같다.
// 뱀의 방향
// ppm 파일의 이름
// 성공 조건 (성장 아이템, 독 아이템)
void FileManager::load_file(const std::string& file){
	YAML::Node level = YAML::LoadFile(file);
	snake_direction = level["direction"].as<int>();
	ppm_name = level["ppm_file"].as<std::string>();
	growth_counter = level["growth"].as<int>();
	poison_counter = level["poison"].as<int>();
	gate_counter = level["gate"].as<int>();
	length = level["length"].as<int>();
	
	ppm_name.insert(0, "src/assets/ppm/");
}

// PPM 파일을 읽어서 RGB로 저장한 뒤 그에 해당하는 
// 캐릭터 변환자를 통해 캐릭터 2차 배열을 생성한다.
void FileManager::load_ppm(const std::string& name){

	std::ifstream f(name.c_str(), std::ios::binary);
	if (f.fail())
	{
		std::cerr << "Could not open file: " << name << std::endl;
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
		std::cerr << "Only ascii file format is accepted" << std::endl;
	    f.close();
	    return ;
	}
	
	if (width < 1)
	{
		std::cerr << "Width is too short" << std::endl;
	    f.close();
	    return ;
	}
	if (height < 1)
	{
		std::cerr << "Height is too short" << std::endl;
	    f.close();
	    return ;
	}
	if (bits != 255)
	{
		std::cerr << "Only 255 color is supported" << std::endl;
	    f.close();
	    return ;
	}

	color_map.clear();
	for(int i = 0; i < width; ++i) {
		color_map.push_back(std::vector<char>());
	}

	int r,g,b;
	for (int i =0; i < width; i++){
		for (int j =0; j < height; j++){
			f >> r;
			f >> g;
			f >> b;
			color_map[j].push_back(static_cast<char>(RGB(r,g,b)));
		}
	}

    // close file
    f.close();
}

// 트리거가 작동되면 db에 모든 레벨 정보를 저장한다.
void FileManager::process(int level, ECSDB &db){
	std::string path = level_name.at(level);
	path.insert(0, "src/assets/level/");
	load_file(path);
	load_ppm(ppm_name);
	db.Init(width, height, color_map, static_cast<DIRECTION>(snake_direction), growth_counter, poison_counter, gate_counter, length);
}
