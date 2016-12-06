#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>

#define type double
//#define BLOCK 5000

double get_time();
void jacobi_avx(type *, type *, int, int);
void jacobi_avx_blocked(type * grid_new, type * grid_old, int x, int y, int b);
void draw_grid(type *, int, int, const char*);
void init(type *, type *, int, int);
double run_avx(type * grid_new, type * grid_old, int x_size, int y_size);
double run_avx_blocked(type * grid_new, type * grid_old, int x_size, int y_size, int block_size);

int main(int argc, char** argv){

	int size_mb = 0;
	type * grid_new;
	type * grid_old;
	int x_size = 0;
	int y_size = 0;
	int block_size = 0; //Sollte Vielfaches von 4 sein
	int number_blocks = 0;
	int left = 0;
	double avx = 0.;
	double avx_blocked = 0.;

	if(argc != 3){
		return -1;
		fprintf(stderr, "args wrong");
	}else{
		size_mb = atoi(argv[1]);
		block_size = atoi(argv[2]);
	}

	x_size = sqrt((size_mb*1024.0*1024.0) /(2.0 * sizeof(type)));
	number_blocks = (x_size-2.0)/block_size;
	left = (x_size-2) % block_size;
	if(left%4 != 0)
		left += (4-(left%4));
	x_size = number_blocks * block_size + left + 2;
	y_size = x_size;

	//printf("x: %d, y: %d, number_blocks: %d, left: %d, size: %d\n", x_size, y_size, number_blocks, left, block_size);
	if( posix_memalign( (void**)&grid_new, 64, sizeof(type)*x_size*y_size) != 0){
		perror("grid_new");
	}
	if( posix_memalign( (void**)&grid_old, 64, sizeof(type)*x_size*y_size) != 0){
		perror("grid_old");
	}
	
	init(grid_new, grid_old, x_size, y_size);
	avx= run_avx(grid_new, grid_old, x_size, y_size);

	//printf("avx finished %f \n", avx);
	
	init(grid_new, grid_old, x_size, y_size);
	avx_blocked = run_avx_blocked(grid_new, grid_old, x_size, y_size, block_size);

	//printf("avx blocked finished %f \n", avx_blocked);

	//draw_grid(grid_new, x_size, y_size, "avx_blocked.ppm");	
	printf("%f, %f, %f \n", (2.0*x_size*y_size*sizeof(type))/(1024.0*1024.0), avx, avx_blocked);
	
	free(grid_new);
	free(grid_old);
	return 0;
}


double run_avx(type * grid_new, type * grid_old, int x_size, int y_size){
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	long limit = 1;
	double start_time = 0.0;
	double end_time= 0.0;
	type* temp;
	
	//draw_grid(grid_new, x_size, y_size, "avx_before.ppm");	
	while( (end_time-start_time) <= 1.0){

		start_time = get_time();
		for(j = 0; j < limit; ++j){
			jacobi_avx(grid_new, grid_old, x_size, y_size);
			temp = grid_old;
			grid_old = grid_new;
			grid_new = temp;
		}
		end_time = get_time();
		//printf("%f start, %f end \n", start_time, end_time);
		//printf("%d limit \n", limit);
		limit *= 2;
	}
	//draw_grid(grid_new, x_size, y_size, "avx_after.ppm");   
	limit /= 2;
	double mups = ((double)limit*(double)(x_size-2.0)*(double)(y_size-2.0)/1000000.0)/(end_time-start_time);

	return mups;	
}


double run_avx_blocked(type * grid_new, type * grid_old, int x_size, int y_size, int block_size){
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	long limit = 1;
	double start_time = 0.0;
	double end_time= 0.0;
	type* temp;
	
	//draw_grid(grid_new, x_size, y_size, "avx_before.ppm");	
	while( (end_time-start_time) <= 1.0){

		start_time = get_time();
		for(j = 0; j < limit; ++j){
			jacobi_avx_blocked(grid_new, grid_old, x_size, y_size, block_size);
			temp = grid_old;
			grid_old = grid_new;
			grid_new = temp;
		}
		end_time = get_time();
		//printf("%f start, %f end \n", start_time, end_time);
		//printf("%d limit \n", limit);
		limit *= 2;
	}
	//draw_grid(grid_new, x_size, y_size, "avx_after.ppm");   
	limit /= 2;
	double mups = ((double)limit*(double)(x_size-2.0)*(double)(y_size-2.0)/1000000.0)/(end_time-start_time);

	return mups;	
}




void init(type * grid_new, type * grid_old, int x_size, int y_size){
	int y = 0;
	int x = 0;
	//Gesamten Bereich auf 0.0 init
	for(y = 0; y < y_size; ++y){
		for(x = 0; x < x_size; ++x){
			grid_new[y*x_size + x] = 0.0;
			grid_old[y*x_size + x] = 0.0;
		} 
	}
	//Oberen Rand init
	for(x = 0; x < x_size; ++x){
		grid_new[x] = 1.0;
		grid_old[x] = 1.0;

	}
	//linker Rand init
	for(y = 0; y < y_size; ++y){
		grid_new[y*x_size] = 1.0;
		grid_old[y*x_size] = 1.0;
	}
}

double get_time(void){
	struct timespec a;
	clock_gettime(CLOCK_MONOTONIC, &a);
	double t = (double) a.tv_nsec / (1000.0*1000.*1000.0) + (double) a.tv_sec;
	//printf("%d nsec, %d sec \n", a.tv_nsec, a.tv_sec);
	//printf("%f time function \n", t);
	return t;

}

