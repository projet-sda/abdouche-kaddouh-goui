#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "citiesReader.h"
#include "adjacency_matrix.h"

int edge_valuation(float lat_a, float lat_b, float lon_a, float lon_b){

	int R = 6371, valuation;
	valuation = R*acos(sin(lat_a)*sin(lat_b) + cos(lon_b - lon_a)*cos(lat_a)*cos(lat_b));
	return(valuation);
}


int **adjacency_matrix_creation(ListOfCities *cities){

	int **matrix;
	if ((matrix = (int **)malloc(cities->number * sizeof(int *))) == NULL){
		perror("Memory allocation failed. Exit.\n");
		exit(EXIT_FAILURE);
	}

	int i, j;
	//Allocation of each row. However, using the diagonal properties
	//of an adjacency matrix, we do not need to create an n*n matrix.
	//We only need n*(n-1)/2 cells to store our valuations.
	for (i = 0; i < cities->number; i++)
		if ((matrix[i] = (int *)malloc(cities->number * sizeof(int))) == NULL){
			perror("Memory allocation failed. Exit. \n");
			exit(EXIT_FAILURE);
		}
	

	//Now, we'll fill our matrix.

	for (i = 0; i < cities->number; i++)
		for (j = 0; j < cities->number; j++)
			matrix[i][j] = edge_valuation(cities->lat[i], cities->lat[j], cities->lon[i], cities->lon[j]);

	return (matrix);

}
