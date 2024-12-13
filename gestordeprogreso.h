#include "keyState.h"
#include<iostream>
#include<fstream>
#include<filesystem>
namespace fs = std::filesystem;
#pragma once
//#define SAVEFILE_URL = "./progress.json"

struct ProgressState {
	char key;
	int timesPressed;
};

class ProgressController
{
	std::ofstream progressFile;
	ProgressState progressState[4]{
		'W', 0,
		'A', 0,
		'S', 0,
		'D', 0,
	};
public:
	ProgressController();
	void bufferProgress(KeyState progress[4]);
	void saveProgress(KeyState progress[4]);
};

