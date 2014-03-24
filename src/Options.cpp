#include "Options.h"

using namespace std;

Options::Options(string name) {
	load(name);
	fillDefault();
}

string Options::get(string name) {
    if(settings.find(name)!=settings.end())
        return settings[name];
    else if(defaultSettings.find(name)!=defaultSettings.end())
        return defaultSettings[name];
    else
        throw runtime_error("Could not find option!");
        return "NULL";
}

void Options::load(string name) {
    ifstream file;
	fileName = name;
	file.open(name.c_str(), ifstream::in); //Opens file

	if(!file.good()) { //does it exist?
		file.close(); //Closes it so we don't mess with creating a new options file
		cerr << "Options file doesn't exist, creating it" << endl;
		reset();
		file.open(name.c_str()); //Opens file
	}

	string line;
	stringstream ss;
	string linePart;
	string arg;

	//Reads in all the arguments
	while(!file.eof()) {
		stringstream ss;
		getline(file, line);
		ss << line.c_str();
		//Option
		getline(ss, linePart, '=');
		linePart.erase( remove_if( linePart.begin(), linePart.end(), ::isspace ), linePart.end() ); //Removes spaces
		//Argument
		getline(ss, arg);
		arg.erase( remove_if( arg.begin(), arg.end(), ::isspace ), arg.end() ); //removes spaces
		if(linePart.size() >= 1)
			settings[linePart]=arg;
	}
	file.close();
}

void Options::fillDefault() {
    defaultSettings["w"]="forward";
    defaultSettings["a"]="left";
    defaultSettings["s"]="back";
    defaultSettings["d"]="right";
    defaultSettings["error_image"]="assets/debug/error.png";
    defaultSettings["screen_width"]="640";
    defaultSettings["screen_height"]="480";
    defaultSettings["screen_bbp"]="32";
    defaultSettings["verbose"]="false";
    defaultSettings["maxFPS"]="60";
    defaultSettings["pixels_per_meter"]="32";
    defaultSettings["physics_debug"]="false";
}

void Options::save() {
	ofstream file;
	file.open(fileName.c_str());
	for (unordered_map<string,string>::iterator it=settings.begin(); it!=settings.end(); ++it)
    	file << it->first << "=" << it->second << endl;
	file.close();
}


void Options::debugOut() {
	for (unordered_map<string,string>::iterator it=settings.begin(); it!=settings.end(); ++it)
    	cout << it->first << "=" << it->second << endl;
}

void Options::reset() {
	ofstream file;
	file.open(fileName.c_str());
	if(!file.is_open())
		cout << "Failed to open file for writting" << endl;
    for (unordered_map<string,string>::iterator it=defaultSettings.begin(); it!=defaultSettings.end(); ++it)
    	file << it->first << "=" << it->second << endl;
	file.close();
	file.close();
}
