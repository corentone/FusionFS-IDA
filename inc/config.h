#ifndef FF_CONFIG_H
#define FF_CONFIG_H

#include <string>

// Struct for the config file
typedef struct {
	std::string path;
	std::string member_path;
	std::string cacheDirectory;
	int codingId;
	int k;
	int m;
	int bufsize;
} configuration;

#endif /*FF_CONFIG_H*/
