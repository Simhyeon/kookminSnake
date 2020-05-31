#include "filemanager.hpp"
#include <fstream>

void FileManager::eat_comment(std::ifstream &f){
	char linebuff[1024];
	char ppp;
	while (ppp = f.peek(), ppp == '\n' || ppp == '\r')
		f.get();
	if (ppp == '#')
		f.getline(linebuff, 1023);
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
