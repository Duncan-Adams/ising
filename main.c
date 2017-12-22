#include "ising.h"
#include "time.h"

#define NUM_I 1000

int main(int argc, char **argv) {
   srand(time(0));	
   
   lattice grid = init_lattice(10, 13.6);
   
   int w = 0;
   
   while(w < NUM_I) { 
	   ising_iter(&grid);
	   w++;
	   }
	
	free_lattice(&grid);
	
	return 0;
}
