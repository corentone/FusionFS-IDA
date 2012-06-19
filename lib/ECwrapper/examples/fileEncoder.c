/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 * Author:  Pedro Alvarez-Tabio
 * Email:   palvare3@iit.edu
 *
 * File Encoder Example for Erasure-Coding Libraries
 */

#include <ecwrapper.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[]) {

	//INPUTS: Filename to Encode, # data blocks (n), # parity blocks (m), size of buffer (in B)
	char * filename = argv[1];
	char filenameDest[260];	
	int n = atoi(argv[2]);
	int m = atoi(argv[3]);
	int bufsize = atoi(argv[4]);

	FILE *source;
	FILE *destination[n+m];
	FILE *destinationMeta;

	/* Initialize Ec Functions and Context */
	ecFunctions ec;
    ecContext context;

	ec_init_Gibraltar(&ec); //If Gibraltar
	//ec_init_JerasureRS(&ec); //if Jerasure Reed Solomon
	
	int rc = ec->init(n, m, &context);
	if (rc) {
		printf("Error:  %i\n", rc);
		exit(EXIT_FAILURE);
	}

	/* Allocate/define the appropriate number of buffers */
	void *buffers;
	ec->alloc(&buffers, bufsize, &bufsize, context);

	/* Open source file and destination files */
	source = fopen(filename, "rb");
	if(!source){
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	int j;
	
	for (j = 0; j < n + m; j++) {
		sprintf(filenameDest, "./%s.%d", filename, j);
	    	destination[j] = fopen(filenameDest, "wb");
		if(!destination[j]){
			printf("ERROR: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
			}
	}

	/* Encode N*BUFSIZE bytes at a time then repeat until EOF */
	int bytesRead;
	while(!feof(source)){
		//1-read		
		bytesRead = fread(buffers,sizeof(unsigned char), bufsize*n, source);

		if(bytesRead < bufsize * n){//Padding(with 0s) if necessary
			memset((unsigned char *) buffers + bytesRead, 0, bufsize*n - bytesRead);
		}
		
		//2-encode
    		ec->generate(buffers, bufsize, context);

		//3-Write
		for (j = 0; j < n + m; j++) {
    			fwrite((unsigned char *)buffers + j*bufsize, sizeof(unsigned char), bufsize, destination[j]);
    		}
	}

	/* Writing the metaData */
	sprintf(filenameDest, "./%s.meta", filename);
    	destinationMeta = fopen(filenameDest, "w");
	if(!destinationMeta){
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	//Filename
	fprintf(destinationMeta,"%s\n",filename);
	//FileSize
	fprintf(destinationMeta,"%ld\n",ftell(source));
	//Time of Encoding
	time_t rawtime;
	time ( &rawtime );
  	fprintf (destinationMeta,"%s", ctime (&rawtime) );
	//Parameters
	fprintf(destinationMeta,"%i %i\n",n,m);
	//Type of encoding
	//TODO
	//Buffer size
	fprintf(destinationMeta,"%i\n",bufsize);

	/* Close files */
	fclose(source);
	for (j = 0; j < n + m; j++) {
		fclose(destination[j]);
	}

	/* Free allocated memory and destroy Context */
	ec->free(buffers, context);
    	ec->destroy(context);
	
	return EXIT_SUCCESS;
}
