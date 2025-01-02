#include <string>
#include "gestordeprogreso.h"
using namespace std;

ProgressController::ProgressController() {
	ifstream readFile;
	readFile.open("savedKeysProgress.csv");
	if (readFile.is_open()) {
		string line;
		size_t i = 0;
		while (getline(readFile, line)) {
			int amountLoaded = stoi(line.substr(line.find(',') + 1, line.length()));
			if (amountLoaded == 0)
				continue;
			char characterLoaded = line.substr(0, line.find(','))[0];
			if (characterLoaded == this->progressState[i].key)
				this->progressState[i].timesPressed = amountLoaded;
			cout << "Char: " << characterLoaded << "\n";
			cout << "Loaded presses from drive: " << amountLoaded << ".\n";
			i++;
		}
		cout << "\n";
	}
};

//Save to memory.
void ProgressController::bufferProgress(KeyState progress[4]) {
	for (size_t i = 0; i < 4; i++) {
		this->progressState[i].timesPressed += progress[i].timesPressed;
		progress[i].timesPressed = 0;
	}
}

//Save to drive.
void ProgressController::saveProgress(KeyState progress[4]){
	progressFile.open("savedKeysProgress.csv");
	if (progressFile.is_open())	{
		cout << "\n";
		for (size_t i = 0; i < 4; i++) {
			progressFile << this->progressState[i].key << "," << this->progressState[i].timesPressed<< "\n";
			cout << "[" << progress[i].key << "]: " << this->progressState[i].timesPressed << " ";
		}
		cout << "\n";
		progressFile.close();
	}
	return;
}