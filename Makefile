all: server

server: mongoose.o arduino-serial-lib.o
	g++ -g routes.cpp actions.cpp server.cpp ./arduino-serial/arduino-serial-lib.c ./mongoose/mongoose.o -ljsoncpp -o server

mongoose.o:
	g++ -c mongoose/mongoose.c -pthread -o mongoose/mongoose.o

arduino-serial-lib.o:
	make -C arduino-serial

clean:
	make clean -C arduino-serial
	rm mongoose/*.o
	rm server