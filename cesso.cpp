#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <unistd.h>

const char * helpstring = 
	"-h	print usage\n"
	"-F	fullscreen mode\n";

const int SCW = 320;
const int SCH = 240;

bool FSCREEN = false;
const int DISPLAY = 0;

const int FPS = 30;
const float SPF = 1.000/FPS;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Surface* img_bg = NULL;
SDL_Surface* img_ts = NULL;
SDL_Surface* img_fn = NULL;

SDL_Texture* tx_bg = NULL;
SDL_Texture* tx_ts = NULL;
SDL_Texture* tx_fn = NULL;

SDL_Event event;


const int CELLSIZE = 30;
SDL_Rect tsetcells[12];
SDL_Rect boardcells[64];

void parse_options(int argc, char ** argv)
{
	int c;
	opterr=0;
	while ((c = getopt(argc,argv,"Fh")) != -1)
	{
		switch(c)
		{
			case 'F':
				std::cout << "setting fullscreen\n";
				FSCREEN = true;				
				break;
			case 'h':
				std::cout << helpstring;
				exit(0);
				break;
			case '?':		
			default:
				std::cerr << "unrecognized option." << std::endl;
				std::cerr << helpstring;
				exit(1);
				break;
		}
	}
}

int init_gui()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow( "Cesso" , 
			SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 
			SCW, SCH, 
			SDL_WINDOW_SHOWN | (FSCREEN*SDL_WINDOW_FULLSCREEN_DESKTOP) );



	if (window == NULL)
	{
		std::cerr << "Error creating main window: " << SDL_GetError() << std::endl;
		return 1;
	};
	
	renderer = SDL_CreateRenderer(window, -1, 0);	

	if (renderer == NULL)
	{
		std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
		return 1;
	};

	if (FSCREEN)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
		SDL_RenderSetLogicalSize(renderer, SCW, SCH);
	}

	for(int i=0; i<12; i++)
	{
		tsetcells[i] = {CELLSIZE*(i%4),CELLSIZE*(i/4),CELLSIZE,CELLSIZE};
	}

	for(int i=0; i<64; i++)
	{
		boardcells[i] = {CELLSIZE*(i%8),CELLSIZE*(i/8),CELLSIZE,CELLSIZE};
	}


	
	return 0;
}

int quit_gui()
{
	SDL_Quit();
	return 0;
}


int load_pictures()
{
	img_bg = IMG_Load("img/bg.png");
	if (img_bg == NULL)
	{
		std::cerr << "error loading image img/bg.png" << std::endl;
		return 1;
	}	

	img_ts = IMG_Load("img/alpha_tileset.png");
	if (img_ts == NULL)
	{
		std::cerr << "error loading image img/alpha_tileset.png" << std::endl;
		return 1;
	}	

	img_fn = IMG_Load("img/font8x8.png");
	if (img_fn == NULL)
	{
		std::cerr << "error loading image img/font8x8.png" << std::endl;
		return 1;
	}	

	tx_bg = SDL_CreateTextureFromSurface(renderer,img_bg);	
	tx_ts = SDL_CreateTextureFromSurface(renderer,img_ts);
	tx_fn = SDL_CreateTextureFromSurface(renderer,img_fn);

	return 0;
}

void handle_events()
{
	while( SDL_PollEvent( &event ) ) {
		if (event.type == SDL_QUIT)
		{
			quit_gui();
			exit(0);
		}

	}
}




void draw_piece(char x, char y, char pid)
{

	SDL_RenderCopy(renderer, tx_ts, &tsetcells[pid] , &boardcells[8*y+x]);

}

void display()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, tx_bg, NULL, NULL);

	for(int i=0; i<12; i++)
		draw_piece(i%8,i/8,i);

	SDL_RenderPresent(renderer);
}


void loop()
{
	handle_events();
	display();
	SDL_Delay(SPF);

	
}


int main(int argc, char **argv)
{
	parse_options(argc,argv);

	int guiinitstat = init_gui();

	if (guiinitstat > 0)
	{
		std::cerr << "there was a fatal error during initialization." << std:: endl;
		return guiinitstat;
	}

	if (load_pictures() > 0)
	{
		std::cerr << "there was a fatal error in resource loading." << std::endl;
		return 1;
	}

	
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tx_bg, NULL, NULL);
	SDL_Rect tmprect = {0,0,120,90};
	SDL_RenderCopy(renderer, tx_ts, NULL, &tmprect);
	tmprect = {0,0,128,128};
	SDL_RenderCopy(renderer, tx_fn, NULL, &tmprect);

	while(true)
	{
		loop();
	};
	



	quit_gui();
	return 0;
}
