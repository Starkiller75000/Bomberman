//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by Fedora28_VM_MAC,
//

#include "../include/core.hpp"
#include <iostream>
#include <X11/Xlib.h>

int main()
{
	Display* disp = XOpenDisplay(nullptr);
	Screen*  scrn = DefaultScreenOfDisplay(disp);
	int height = scrn->height;
	int width  = scrn->width;
	Core core(static_cast<irr::u32>(width), static_cast<irr::u32>(height));
	core.mainDisplay();
	return 0;
}