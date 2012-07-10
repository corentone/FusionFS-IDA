/* 
 * Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 * Author: Pedro Alvarez-Tabio
 * Email: palvare3@iit.edu
 *
 * Information Dispersal Algorithm based FusionFS API
 */

#include <iostream>
#include <fstream>
#include <string>
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
	config.member_path = "members";
	
	// Read the config file for k, m, codingId and bufsize
	ifstream infile;
	infile.open(configPath.c_str());
	string line;

	while(!infile.eof()) {
		getline(infile, line);
		vector<string> tokens = split(line, '=');
		string key = tokens[0];
		string value = tokens[1];
		
		// Really dirty, I accept suggestions
		if (strcmp(key.c_str(), "k") == 0) {
			config.k = atoi(value.c_str());
		} else if (strcmp(key.c_str(), "m") == 0) {
			config.m = atoi(value.c_str());
		}	else if (strcmp(key.c_str(), "codingId") == 0) {
			config.codingId = atoi(value.c_str());
		} else if (strcmp(key.c_str(), "bufsize") == 0) {
			config.bufsize = atoi(value.c_str());
		}
	}
	
	meta = new Metadata(config);
	infile.close();
}

int idaAPI::insert(string filepath) {
	// First, insert metadata
	meta->insert(filepath);
	
	// Then, data insertion
}

int idaAPI::remove(string filepath) {
	//TODO
	
	// Last, remove metadata
	meta->remove(filepath);
}

int idaAPI::get(string filepath) {
	
	meta->get(filepath);
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
