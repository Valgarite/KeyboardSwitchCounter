#include "keyState.h"
#include<iostream>
#include<fstream>
#include<filesystem>
#include <string>
#pragma once
//#define SAVEFILE_URL = "./progress.json"
using namespace std;

struct ProgressState {
	char key;
	int timesPressed;
};

class ProgressController
{
	ofstream progressFile;
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

