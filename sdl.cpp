//#include <windows.h>
//#include <SWI-Prolog.h>
#include <SWI-cpp.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

SDL_Window* gWindow = NULL;
SDL_Surface* gSurface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int START_TIME = 0;

struct pair
{
	SDL_Surface* s;
	SDL_Texture* t;
};
typedef struct pair pair;

pair* gpair=NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//Clear screen
				SDL_RenderClear( gRenderer );
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

PREDICATE (exit,0){
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	SDL_Quit();
	IMG_Quit();
	return true;
	//PL_succeed;
}
//static foreign_t pl_exit(){c_exit();PL_succeed;}
PREDICATE (sdl_start,2) {
	SDL_Event e;
	int count=0;
	bool quit=false;
	term_t a0=PL_new_term_ref(),a1=PL_new_term_ref(),a2=PL_new_term_ref(),prev=a1;
	term_t goal = PL_new_term_ref();
	term_t exception=PL_new_term_ref();
	PL_put_atom_chars(exception,"error: update function failure");
	int start=SDL_GetTicks();
	int dt=start,t0=dt,t1;
	int timer=50;
	int total=0;
	module_t m = PL_new_module(PL_new_atom("user"));
	!PL_get_integer(A1, &timer);
	a1=A2;/*
	//PL_unify(a1,A2);
	PlTermv av(2);
	av[0]=A2;
	PlTerm a_;*/
	//av[1]=PlTermv(a2);
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//printf("%d,%d\n",e,&e);
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if( e.type == SDL_KEYDOWN )
            {
				int key=e.key.keysym.sym ;
				char c=key;
				//printf("key;%d;%c\n",key,c);
				if(PL_put_integer(a0, key)&&PL_cons_functor(goal, PL_new_functor(PL_new_atom("keyDown"), 1), a0)&&PL_call(goal,m))
					0;
			}
			else if( e.type == SDL_MOUSEBUTTONUP )
            {
				int key=e.key.keysym.sym;
				char c=key;
				//printf("key;%d;%c\n",key,c);
				if(PL_put_integer(a0, key)&&PL_cons_functor(goal, PL_new_functor(PL_new_atom("mouseUp"), 1), a0)&&PL_call(goal,m))
					0;
			}
		}
		t1=SDL_GetTicks();
		dt=t1-t0; t0=t1;
		total+=dt;
		if(total>timer) {
			printf("update;%d,%d\n",timer,total);
			total=0;
			/*
			PlCall("update",av);
			av[0]=av[1];
			//av[1]=a_;//PL_new_term_ref();
			PlQuery q("update", av);*/
			//q.next_solution();
			if(!(PL_cons_functor(goal, PL_new_functor(PL_new_atom("update"), 2), a1,a2)&&PL_call(goal,m))) {
				printf("error: 'update' predicate not found\n");
				PL_raise_exception(exception);
				PL_fail;
			}
			count++;
			a1=a2;
			a2=PL_new_term_ref();
			//break;
		}
		//if(count>5000)quit=true;
		SDL_Delay(1);
	}/*
	q.next_solution();*/
	//SDL_Delay(1);
	//PL_cons_functor(goal, PL_new_functor(PL_new_atom("update"), 3), a0,a0,a0)&&PL_call(goal,NULL)||printf("error\n");
	PL_succeed;
} 
/*

static foreign_t eventIterator(term_t to){
	SDL_Event e;
	bool quit=false;
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			printf("%d,%d\n",e,&e);
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
	}
	PL_succeed;
}
*/
PREDICATE (init,0) {
	init();
	PL_succeed;
}
PREDICATE (loadImage,2) {
	char *s;
	PL_get_chars(A1,&s,CVT_STRING)||printf("error\n");
	SDL_Surface* loadedSurface = IMG_Load( s );
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
	if( newTexture == NULL )
		printf( "Unable to create texture from %s! SDL Error: %s\n", s, SDL_GetError() );
	SDL_FreeSurface( loadedSurface );
	if( loadedSurface == NULL )	{
		printf( "Unable to load image %s! SDL Error: %s\n", s, SDL_GetError() );
		PL_fail;
	}
	pair *p1=new pair;
	gpair=p1;
	p1->s=loadedSurface;
	p1->t=newTexture;
	void *p=p1;
	printf("p;%d;\n",p);
	printf("l;%d;%d\n",loadedSurface,newTexture);
	term_t a=PL_new_term_ref();
	PL_put_pointer(a, p);
	return PL_unify(A2, a);
}
PREDICATE (drawImage,3) {
	void *p;
	pair *p1;
	int i,x,y;
	SDL_Surface* s;
	SDL_Texture* t;
	!PL_get_pointer(A1,&p);
	p1=(pair*)p;
	s=p1->s;
	t=p1->t;
	printf("p;%d;\n",p);
	printf("d;%d;%d;\n",s,t);/**/
	!PL_get_integer(A2,&x)&&PL_get_integer(A3,&y);
	//
	SDL_Rect renderQuad = { x, y, s->w, s->h };
	SDL_RenderCopy( gRenderer, t, NULL, &renderQuad );
	PL_succeed;
}
PREDICATE (clear,0) {
	//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );PL_succeed;
}
PREDICATE (refresh,0) {
	//SDL_UpdateWindowSurface( gWindow );
	SDL_RenderPresent( gRenderer );PL_succeed;
}

PREDICATE (rect,4) {
	int i,i2,i3,i4;
	int b=PL_get_integer(A1,&i)&&PL_get_integer(A2,&i2)&&PL_get_integer(A3,&i3)&&PL_get_integer(A4,&i4);
	SDL_Rect fillRect = { i, i2, i3, i4 };
	//SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x22, 0xFF );
	SDL_RenderFillRect( gRenderer, &fillRect );
	//Sdprintf(b);
	return b;
}
PREDICATE (circle,4) {
	int i,i2,i3,i4;
	int b=PL_get_integer(A1,&i)&&PL_get_integer(A2,&i2)&&PL_get_integer(A3,&i3)&&PL_get_integer(A4,&i4);
	SDL_Rect fillRect = { i, i2, i3, i4 };
	SDL_RenderFillRect( gRenderer, &fillRect );
	return b;
}
PREDICATE (setRGBA,4) {
	int i,i2,i3,i4;
	int b=PL_get_integer(A1,&i)&&PL_get_integer(A2,&i2)&&PL_get_integer(A3,&i3)&&PL_get_integer(A4,&i4);
	i4=0xFF;
	SDL_SetRenderDrawColor( gRenderer, i,i2,i3, i4 );
	return b;
}
/*
static foreign_t pl_circle(term_t a){
	//circle(screen,a0,a1,a2,a3);SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
	//circlefill(screen,&a0,&a1,&a2,&a3);
	//SDL_Rect fillRect = { a0, a1,a2,a3 };
	int i,i2,i3,i4;
	//int b=PL_get_integer(a,&i)&&PL_get_integer(a2,&i2)&&PL_get_integer(a3,&i3)&&PL_get_integer(a4,&i4);
	SDL_Rect fillRect = { i, i2, i3, i4 };
	//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( gRenderer, &fillRect );
	PL_succeed;
}

*/

#define seti(i,a) do { int b=PL_get_integer(a,&i); } while (0)

PREDICATE (sdl_delay,1) {
	int i;
	seti(i,A1);
	SDL_Delay(i);
	PL_succeed;
}
PREDICATE (getTicks,1) {
	int i=SDL_GetTicks();
	return PL_unify_integer(A1,i);
}
PREDICATE (sdl_readkey,1) {
	//readkey();
	PL_succeed;
}

PREDICATE (check,2) {
	PL_succeed;
}
