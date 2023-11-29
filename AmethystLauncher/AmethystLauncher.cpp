// AmethystLauncher.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "loader/Loader.h"

ModLoader loader;

int main() {
	loader.InjectRuntime();
}