#include <iostream>
#include <fstream>
#include "../inc/idaAPI.h"

using namespace std;

idaAPI::idaAPI(){
	//TODO
	// Default config?
}

idaAPI::idaAPI(string configPath){

	//TODO
	
	// Create new Metadata configuration object
	configuration config;
	config.path = configPath;
	config.memberPath = "members";
	
	// Read the config file for k, m, codingId and bufsize
	std::ifstream file(configPath);
	std::string   line;

	while(std::getline(file, line)) {
		std::vector<std::string> tokens = split(line, '=');
		string key = tokens[0];
		string value = tokens[1];
		
		// Really dirty, I accept suggestions
		if (strcmp(key, "k") == 0) {
			config.k = atoi(value);
		} else if (strcmp(key, "m") == 0) {
			config.m = atoi(value);
		}	else if (strcmp(key, "codingId") == 0) {
			config.codingId = atoi(value);
		} else if (strcmp(key, "bufsize") == 0) {
			config.bufsize = atoi(value);
		}
	}
	
	meta = new Metadata(config);
}

int idaAPI::insert(string filepath) {
	// First, insert metadata
	meta.insert(filepath);
	
	// Then, data insertion
}

int idaAPI::remove(string filepath) {
	//TODO
	
	// Last, remove metadata
	meta.remove(filepath);
}

int idaAPI::get(string filepath) {
	
	meta.get(filepath);
	//TODO
}

// Maybe we can move these to utilities.h or something
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}
