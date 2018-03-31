#include "ising.h"
#include "time.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <unistd.h>

#define NUM_I 10000000

SDL_Window* win;
SDL_Renderer* ren;

int render_every = 100000;

void render(lattice *lat) {
	int cell_size = 1600/lat->size;
	int i, j;
	i = j = 0;
	
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_Rect re;
	re.x = 0;
	re.y = 0;
	re.w = cell_size;
	re.h = cell_size;
	
	for(j = 0; j < lat->size; j++) {
	    for(i = 0; i < lat->size; i++) {
			if(spin(lat, i, j) == 1) {
			    SDL_RenderFillRect(ren, &re);
			   }
			re.x += cell_size;
	    }
	    re.x = 0;
	    re.y += cell_size;
    }
	
	SDL_RenderPresent(ren);
	
	return;
}


int main(int argc, char **argv) {
   srand(time(0));	
   
   win = SDL_CreateWindow("Ising", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 400, 400, 0);
   ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
   SDL_RenderSetLogicalSize(ren, 1600, 1600);
  
   
   lattice grid = init_lattice(30, 0.5);
   render(&grid);

   int w = 0;
   
   while(w < NUM_I) { 
	   ising_iter(&grid);
	   
	   if((render_every > 0) && (w % render_every == 0)) {
	       render(&grid);
	       usleep(32*1000);
	   }
	   
	   w++;
	   }
	
	free_lattice(&grid);
	
	return 0;
}
