#include "ising.h"
#include "stdlib.h"
#include "math.h"

lattice init_lattice(int size, double T) {
	lattice lat;
	int i, j;
	i = j = 0;
	char s = 0;
	
	lat.size = size;
	lat.T = T;
	lat.grid = calloc(size*size, sizeof(char));
	
	for(j = 0; j < size; j++) {
		for (i = 0; i < size; i++) {
			s = rand() % 2;
			if(s == 0) s = -1;
			lat.grid[j*size + i] = s;
		}
	}
	
	return lat;
}


void free_lattice(lattice *lat) {
	free(lat->grid);
	lat->grid = NULL;
	lat->size = 0;
	
	return;
}


static char spin(lattice *lat, uint i, uint j) {
	if ((i > lat->size) || (j > lat->size)) {
		return 0;
	}
	
	return lat->grid[j*lat->size + i];
}

static double deltaU(lattice *lat, uint i, uint j) {
    if ((i > lat->size) || (j > lat->size)) {
		return 0.0;
	}
	
	char top, bot, left, right;
	top = bot = left = right = 0;
	
	/* find the four nearest neighbors with periodic boundary conditions*/
	left  = (i == 0)         ? spin(lat, lat->size, j) : spin(lat, i-1, j);
	right = (i == lat->size) ? spin(lat, 0, j)         : spin(lat, i+1, j);
	
	top = (j == 0)         ? spin(lat, i, lat->size) : spin(lat, i, j - 1);
	bot = (j == lat->size) ? spin(lat, i, 0)         : spin(lat, i, j + 1);
	
	return 2*spin(lat, i, j)*(top + bot + left + right);
}

static void flip(lattice *lat, uint i, uint j) {
    if ((i > lat->size) || (j > lat->size)) {
		return;
	}
	
	lat->grid[j*lat->size + i] *= -1;
	
	return; 
}

void ising_iter(lattice *lat) {
	uint i = 0;
	uint j = 0; 
	double dE = 0.0;
	
	i = (rand() % lat->size);
	j = (rand() % lat->size);

    dE = deltaU(lat, i, j);

	if (dE <= 0) {
		flip(lat, i, j);
	} else if ( ((double)rand()/(double)(RAND_MAX)) < exp(-dE/(lat->T)) ) {
		flip(lat, i, j);
	}
}
