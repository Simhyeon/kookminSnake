#include "renderer.hpp"
#include <iostream>

void Renderer::process(ECSDB & ecsdb){
	int width = ecsdb.get_measure().first;
	int height = ecsdb.get_measure().first;
	auto snake_map = ecsdb.get_snake_map();
	for (int i =0; i< width; i++){
		for (int j =0; j< height; j++){
			std::cout << snake_map[j][i] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "Length : " << ecsdb.get_snake().size() << "\n";
	std::cout << "Growth needed : " << ecsdb.get_growth_counter() << "/" << ecsdb.get_growth_qual() << "\n";
	std::cout << "Poison needed : " << ecsdb.get_poison_counter() << "/" << ecsdb.get_poison_qual() << "\n";
}
