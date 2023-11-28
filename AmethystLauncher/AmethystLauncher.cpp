// AmethystLauncher.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "loader/loader.h"

int main() {
	modLoader* loader = new modLoader();
	loader->InjectRuntime();
}