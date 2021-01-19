OBJS	= Sources/main.o Sources/Ipv4.o Sources/Net.o Sources/WebNode.o process/Sources/process.o Menu/Sources/Menu.o Menu/Sources/MenuChoices.o Menu/conio/Sources/conio.o
SOURCE	= Sources/main.cpp Sources/Ipv4.cpp Sources/Net.cpp Sources/WebNode.cpp process/Sources/process.cpp Menu/Sources/Menu.cpp Menu/Sources/MenuChoices.cpp Menu/conio/Sources/conio.cpp
HEADER	= Headers/Ipv4.h Headers/Net.h Headers/WebNode.h process/Headers/process.h Menu/Headers/Menu.h Menu/Headers/MenuChoices.h Menu/conio/Headers/conio.h
OUT	= Spoofyst
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Sources/main.o: Sources/main.cpp
	$(CC) $(FLAGS) Sources/main.cpp 

Sources/Ipv4.o: Sources/Ipv4.cpp
	$(CC) $(FLAGS) Sources/Ipv4.cpp 

Sources/Net.o: Sources/Net.cpp
	$(CC) $(FLAGS) Sources/Net.cpp 

Sources/WebNode.o: Sources/WebNode.cpp
	$(CC) $(FLAGS) Sources/WebNode.cpp 

process/Sources/process.o: process/Sources/process.cpp
	$(CC) $(FLAGS) process/Sources/process.cpp 

Menu/Sources/Menu.o: Menu/Sources/Menu.cpp
	$(CC) $(FLAGS) Menu/Sources/Menu.cpp 

Menu/Sources/MenuChoices.o: Menu/Sources/MenuChoices.cpp
	$(CC) $(FLAGS) Menu/Sources/MenuChoices.cpp 

Menu/conio/Sources/conio.o: Menu/conio/Sources/conio.cpp
	$(CC) $(FLAGS) Menu/conio/Sources/conio.cpp 


clean:
	rm -f $(OBJS) $(OUT)
