//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by Fedora28_VM_MAC,
//

#include "../include/core.hpp"

int	main()
{
	int		height = 1080;
	int		width = 1920;
	Core		core(static_cast<irr::u32>(width),
					static_cast<irr::u32>(height));

	core.mainDisplay();
	return 0;
}