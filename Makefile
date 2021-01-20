OBJS	= main.o Ipv4.o WebNode.o Net.o process.o Menu.o MenuChoice.o conio.o
SOURCE	= Sources/main.cpp Sources/Ipv4.cpp Sources/Net.cpp Sources/WebNode.cpp process/Sources/process.cpp Menu/Sources/Menu.cpp Menu/Sources/MenuChoice.cpp Menu/conio/Sources/conio.cpp
HEADER	= Headers/Ipv4.h Headers/Net.h Headers/WebNode.h process/Headers/process.h Menu/Headers/Menu.h Menu/Headers/MenuChoice.h Menu/conio/Headers/conio.h
OUT	= Spoofyst
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: Sources/main.cpp
	$(CC) $(FLAGS) Sources/main.cpp 

Ipv4.o: Sources/Ipv4.cpp
	$(CC) $(FLAGS) Sources/Ipv4.cpp 

WebNode.o: Sources/WebNode.cpp
	$(CC) $(FLAGS) Sources/WebNode.cpp 

Net.o: Sources/Net.cpp
	$(CC) $(FLAGS) Sources/Net.cpp

process.o: process/Sources/process.cpp
	$(CC) $(FLAGS) process/Sources/process.cpp 

Menu.o: Menu/Sources/Menu.cpp
	$(CC) $(FLAGS) Menu/Sources/Menu.cpp 

MenuChoice.o: Menu/Sources/MenuChoice.cpp
	$(CC) $(FLAGS) Menu/Sources/MenuChoice.cpp 

conio.o: Menu/conio/Sources/conio.cpp
	$(CC) $(FLAGS) Menu/conio/Sources/conio.cpp 


clean:
	rm -f $(OBJS) $(OUT)
