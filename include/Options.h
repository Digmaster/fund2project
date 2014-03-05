#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Options {
public:
	Options(string name="options.txt");
	string get(string name); //Gets an option
	void set(string name, string set) {settings[name] = set;} //Sets an option to something, or creates a new one
	void reset(); //Default settings file
	void save(); //Saves the settings to a file
	void debugOut(); //lists all settings
	void load(string name);
	static Options& instance() {
		static Options INSTANCE;
		return INSTANCE;
	}
private:
	string fileName;
	unordered_map<string,string> settings;
	unordered_map<string,string> defaultSettings;
	void fillDefault();
};

#endif

