OBJS	= main.o Ipv4.o WebNode.o Net.o process.o Stringyst.o Menu.o MenuChoice.o conio.o Modyst.o
SOURCE	= Sources/main.cpp Sources/Ipv4.cpp Sources/Net.cpp Sources/WebNode.cpp process/Sources/process.cpp Stringyst/Sources/Stringyst.cpp Menu/Sources/Menu.cpp Menu/Sources/MenuChoice.cpp Menu/conio/Sources/conio.cpp Menu/TextModyst/Sources/Modyst.cpp
HEADER	= Headers/Ipv4.h Headers/Net.h Headers/WebNode.h process/Headers/process.h Stringyst/Headers/Stringyst.h Menu/Headers/Menu.h Menu/Headers/MenuChoice.h Menu/conio/Headers/conio.h Menu/unicommand/Headers/unicommand.h Menu/TextModyst/Headers/Modyst.h
OUT	= Bin/Spoofyst
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

Stringyst.o: Stringyst/Sources/Stringyst.cpp
	$(CC) $(FLAGS) Stringyst/Sources/Stringyst.cpp

Menu.o: Menu/Sources/Menu.cpp
	$(CC) $(FLAGS) Menu/Sources/Menu.cpp 

MenuChoice.o: Menu/Sources/MenuChoice.cpp
	$(CC) $(FLAGS) Menu/Sources/MenuChoice.cpp 

conio.o: Menu/conio/Sources/conio.cpp
	$(CC) $(FLAGS) Menu/conio/Sources/conio.cpp 

Modyst.o: Menu/TextModyst/Sources/Modyst.cpp
	$(CC) $(FLAGS) Menu/TextModyst/Sources/Modyst.cpp 

clean:
	rm -f $(OBJS) $(OUT)
