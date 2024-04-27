#pragma once
#include <Windows.h>
#include <iostream>
#include <string.h>
#include <vector>


using std::cout;
using std::endl;

struct MenuFeature {
	std::string title;

	virtual void update(){
		cout << title;

	}
	virtual void setValue(bool left) {

	}
};

struct MenuFeatureInt : MenuFeature {
	int value;


	void update() override {
		MenuFeature::update();
		cout << "\t: " << value;

	}
	void setValue(bool left) override {
		if (left) {
			value--;
		}
		else {
			value++;
		}
	}
};

struct MenuFeatureFloat : MenuFeature {
	float value;

	void update() override {
		MenuFeature::update();
		cout << "\t: " << value;

	}

	void setValue(bool left) override {
		if (left) {
			value--;
		}
		else {
			value++;
		}
	}
};

struct MenuFeatureBool : MenuFeature {
	bool value;

	void update() override {
		MenuFeature::update();
		cout << "\t\t: " << (value ? "true" : "false");

	}
	void setValue(bool left) override {
		value = !value;
	}
};



class ConsoleMenu {
	std::vector<MenuFeature*> features;
	int selectedIndex;
public:
	ConsoleMenu() :
		selectedIndex(0)
	{

	}


	void addFeature(MenuFeature* mPtr) {
		features.push_back(mPtr);
	}

	void moveDown() {
		selectedIndex--;
		if (selectedIndex < 0) {
			selectedIndex = features.size() - 1;
		}
	}

	void moveUp() {
		selectedIndex++;
		if (selectedIndex > features.size() - 1) {
			selectedIndex = 0;
		}
	}
	
	void printMenu() {
		system("CLS");

		for (int i = 0; i < features.size(); i++) {


			MenuFeature* mPtr = features[i];
			mPtr->update();
			if (i == selectedIndex)
				cout << "\t\t<--";
			cout << endl;
		}
	}

	void update() {


		if (GetAsyncKeyState(VK_UP)) {
			moveDown();
			printMenu();
		}

		if (GetAsyncKeyState(VK_DOWN)) {
			moveUp();
			printMenu();
		}

		if (GetAsyncKeyState(VK_LEFT)) {
			features[selectedIndex]->setValue(true);
			printMenu();
		}

		if (GetAsyncKeyState(VK_RIGHT)) {
			features[selectedIndex]->setValue(false);
			printMenu();
		}

	}

};

