#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <stdexcept>



class Options {
public:
	Options(std::string name="options.txt");
	std::string get(std::string name); //Gets an option
	void set(std::string name, std::string set) {settings[name] = set;} //Sets an option to something, or creates a new one
	void reset(); //Default settings file
	void save(); //Saves the settings to a file
	void debugOut(); //lists all settings
	void load(std::string name);
	static Options& instance() {
		static Options INSTANCE;
		return INSTANCE;
	}
private:
	std::string fileName;
	std::unordered_map<std::string,std::string> settings;
	std::unordered_map<std::string,std::string> defaultSettings;
	void fillDefault();
};

#endif

