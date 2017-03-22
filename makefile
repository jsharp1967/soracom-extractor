# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.

CFLAGS=-c -Wall -std=c++11 -I. `xml2-config --cflags` `pkg-config --cflags libxml++-2.6` 
LIBS = -std=c++11 `xml2-config --libs` `pkg-config --libs libxml++-2.6` -L. -lgzstream -lz -lcurl -lwiringPi

all: soracom

soracom: main.o  functions.o command.o xr5000.o extractor.o sessionParser.o session.o uploader.o gzstream.o compressor.o animal.o animalParser.o messages.o loader.o
	$(CC) main.o functions.o command.o xr5000.o extractor.o sessionParser.o session.o uploader.o gzstream.o compressor.o animal.o animalParser.o messages.o loader.o -o soracom $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

command.o: command.cpp
	$(CC) $(CFLAGS) command.cpp

messages.o: messages.cpp
	$(CC) $(CFLAGS) messages.cpp

functions.o: functions.cpp
	$(CC) $(CFLAGS) functions.cpp

xr5000.o: xr5000.cpp
	$(CC) $(CFLAGS) xr5000.cpp

extractor.o: extractor.cpp
	$(CC) $(CFLAGS) extractor.cpp

sessionParser.o: sessionParser.cpp
	$(CC) $(CFLAGS) sessionParser.cpp

session.o: session.cpp
	$(CC) $(CFLAGS) session.cpp

uploader.o: uploader.cpp
	$(CC) $(CFLAGS) uploader.cpp
	
gzstream.o: gzstream.cpp
	$(CC) $(CFLAGS) gzstream.cpp
	
compressor.o: compressor.cpp
	$(CC) $(CFLAGS) compressor.cpp

animal.o: animal.cpp
	$(CC) $(CFLAGS) animal.cpp

animalParser.o: animalParser.cpp
	$(CC) $(CFLAGS) animalParser.cpp
	
loader.o: loader.cpp
	$(CC) $(CFLAGS) loader.cpp
clean:
	rm -rf *.o soracom
install:
	cp soracom /home/pi/
