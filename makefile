OBJS = cesso.cpp 

OBJ_NAME = cesso

SDLIBS = -lSDL2_image

SDLFLAGS = $(shell sdl2-config --cflags --libs)

all : $(OBJS) 
	g++ $(SDLFLAGS)  $(OBJS) -w -o $(OBJ_NAME) $(SDLIBS)
