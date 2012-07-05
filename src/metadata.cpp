/* 
 * Metadata Class for IDA API
 *
 * Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 * Author:  Pedro Alvarez-Tabio
 * Email:   palvare3@iit.edu
 */

#include "../inc/metadata.h"

using namespace std;

Metadata::Metadata(configuration config) {
	config(config);
	client.initialize(config.path, config.member_path);
}

int Metadata::createMetadata(string filepath) {
	// TODO: I think that we don't need this method! Or what are we trying to do?

	//1- Read Config to fill the package
	Package package;
}

int Metadata::insert(string filepath) {

	// Stat the file to get file specific informations TODO: Error checking
	struct stat st;
	stat(filepath, &st);
	// Which ones do we get?
	
	vector<string> pkgList;
	// Send Metadata to ZHT
	client.insertMetadata(config.path, config.member_path, pkgList, filepath, config.codingId, config.k, config.m, config.bufsize);
}

int Metadata::remove(string remoteFilepath) {

	// TODO
	// Remove metadata from ZHT
	client.removeMetadata(remoteFilepath);
}

int Metadata::get(string remoteFilepath) {

	// Retrieve metadata from ZHT
	string metadata = client.getMetadata(remoteFilepath);

}

chunksLocations * getLocations(int number, std::string filepath){
	//TODO
	
	/* Description:
	This function takes an int (the number of Chunks I want to retrieve for downloading or uploading) and a string (the original filepath of the file I want to up/down-load)
	
	It returns a chunksLocations, which is a structure that stores in vectors the location of the chunks. The key in vectors are the same as the "number" of the chunk). 
	
	Those locations should be obtained by encoding the filepath and the number. For example, if we have 5 chunks (k=3,m=2) and a filepath: foo, Let's say the filehash is pfjgle. Then the function should return the locations of pfjgle.0, pfjgle.1, pfjgle.2,pfjgle.3, pfjgle.4. (They all need to be hashed and queried to ZHT)
	
	*/
	
	chunksLocations * locations = (chunksLocations *) malloc(sizeof(chunksLocations));
	
	//TODO
	
	
	return locations;
}
