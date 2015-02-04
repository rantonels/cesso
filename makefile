OBJS = cesso.cpp 

OBJ_NAME = cesso

SDLIBS = -lSDL2 -lSDL2_image

all : $(OBJS) 
	g++ $(OBJS) -w $(SDLIBS) -o $(OBJ_NAME)
