# Author:  Corentin Debains
# Email:   cdebains@iit.edu
#


CXX=g++
CFLAGS=-Wall -Llib -Iinc -g -std=c99
CUDAINC=-I $(CUDA_INC_PATH)
CUDALIB=-L $(CUDA_LIB_PATH)
OBJECTS=data.o configuration.o metadata.o idaAPI.o

#tocheck
#.PHONY: clean ida


all:
	make ida

ida: zht ecwrapper src/ida.cpp
	$(CXX) $(CFLAGS) src/ida.cpp -o bin/fu-fs $(LFLAGS)

PORT=5000
run: zht
	lib/ZHT/bin/server_zht $(PORT) lib/ZHT/neighbor lib/ZHT/zht.cfg

###ZHT Library Compilation and import
LFLAGS+=-lzht
zht: lib/ZHT/Makefile
	cd lib/ZHT && make
	cp lib/ZHT/lib/libzht.a lib/


###Erasure Code Wrapper Library Compilation and Library Import
LFLAGS+=-lecwrapper

ecwrapper: lib/ECwrapper/Makefile
	cd lib/ECwrapper && make
	cp lib/ECwrapper/lib/ecwrapper.a lib/
###

obj:
	mkdir -p obj

obj/%.o: src/%.cpp obj
	$(CXX) $(CFLAGS) -c src/$*.c -o obj/$*.o

# A special kind of rule:  These files don't need to be remade if they're
# out of date, just destroyed.
cache:  src/gib_cuda_checksum.cu
	rm -rf cache
	mkdir cache

clean:
	rm -rf obj cache
	
mrproper: clean
	rm -f lib/*.a
