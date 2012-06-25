/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Configuration class
 */

#include "../inc/config.h"

Configuration::Configuration(){
	this.loadDefaults();
}

Configuration::Configuration(string filepath){
	this.loadDefaults();
	this.parseConfigFile(filepath);

}

int Configuration::parseConfigFile(string filepath){
	//TODO
	//FileParsing for Config is going here :)
	return 0;
}

int Configuration::loadDefaults(){
	
	this.setM(2); //2 parity blocks
	this.setK(4); //4 data blocks
	this.setBufSize(1024); //1 kB buffers
	this.setECLibrary(0); //Gibraltar (GPU) EC library
	
}

/* Getters and Setters */
int Configuration::getM(){
	return this.m;
}

int Configuration::getK(){
	return this.k;
}

int Configuration::getBufSize(){
	return this.bufSize;
}
		
int Configuration::getECLibrary(){
	return this.ECLibrary;
}

int setM(int m){
	this.m = m;
	return 0;
}
int setK(int k){
	this.k = k;
	return 0;
}

int setBufSize(int bufsize){
	this.bufSize = bufsize;
	return 0;
}
int setECLibrary(int lib){
	this.ECLibrary = lib;
	return 0;
}

