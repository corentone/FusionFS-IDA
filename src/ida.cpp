#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>

#include "../inc/idaAPI.h"

using namespace std;

int main(int argc, char *argv[]) {

	char *mode = argv[1];
	char *filename = argv[2]; // Maybe we'll have to change it to std::string
	
	string configFilePath = "./config";
	
	// Create idaAPI object
	idaAPI *dfs = new idaAPI(configFilePath);
	
	if (strcmp(mode, "insert") == 0) {
		// Call insert API
		dfs.insert(filename);
	} else if (strcmp(mode, "get") == 0) {
		// Call get API
		dfs.get(filename);
	} else if (strcmp(mode, "remove") == 0) {
		// Call remove API
		dfs.remove(filename);
	} else {
		// Call error
		cout << "Usage: ida [insert/get/remove] [filename]";
		return 1;
	}
	
	return 0;
}
