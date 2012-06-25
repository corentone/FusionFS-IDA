/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Configuration Structure and Structure Setters & Getters
 */
#ifndef IDACONFIG_H_
#define IDACONFIG_H_


#define GIBRALTAR 0
#define JERASURERS 1

Class Configuration{
	public:
		Configuration(string filepath);
		Configuration();
		
		int getM();
		int getK();
		int getBufSize();
		int getECLibrary();

		int setM(int m);
		int setK(int k);
		int setBufSize(int bufsize);
		int setECLibrary(int lib);

	private:
		int m;
		int k;
		int bufSize;
		int ECLibrary;
		
		int parseConfigFile(filepath);
		int loadDefaults();
};

#endif /*IDACONFIG_H_*/
