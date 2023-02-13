
CC = g++

CFLAGS = -Wall -g

LIBS = -lsfml-window -lsfml-graphics -lsfml-system

SRCS = main.cpp simulation.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = Huffman_Compression

.PHONY: depend clean

all:	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: 
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
