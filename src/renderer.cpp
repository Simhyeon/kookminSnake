#include "renderer.hpp"
#include <iostream>

void Renderer::process(ECSDB & ecsdb){
	int width = ecsdb.get_measure().first;
	int height = ecsdb.get_measure().first;
	for (int i =0; i< width; i++){
		for (int j =0; j< height; j++){
			std::cout << ecsdb.snake_map[j][i] << "";
		}
		std::cout << "\n";
	}
	std::cout << "Length : " << ecsdb.get_snake().size() << "\n";
	std::cout << "Last direction : " << static_cast<int>(ecsdb.last_direction) << "\n";
}
