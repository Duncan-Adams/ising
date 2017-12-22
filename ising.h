#ifndef ISING_H
#define ISING_H

/* lattice is a n x n grid of magentic domains with periodic boundary conditions */
typedef struct _lattice {
	int size; 
	
	double T; /* temperature in eV */
	
	char *grid; /* -1 for spin down, 1 for spin up */
	
} lattice;

lattice init_lattice(int size, double T);

void free_lattice(lattice *lat);

void ising_iter(lattice *lat); /* perform one iteration with the Metropolos algorithm */



#endif
