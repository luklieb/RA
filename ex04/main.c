#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>

#define type double

double get_time();
void jacobi_vanilla(type *, type *, int, int);
void jacobi_sse(type *, type *, int, int);
void jacobi_avx(type *, type *, int, int);
void draw_grid(type *, int, int, const char*);
void init(type *, type *, int, int);
double run_vanilla(type * grid_new, type * grid_old, int x_size, int y_size);
double run_sse(type * grid_new, type * grid_old, int x_size, int y_size);
double run_avx(type * grid_new, type * grid_old, int x_size, int y_size);

int main(int argc, char** argv){

	int size_kb = 0;
	type * grid_new;
	type * grid_old;
	int x_size = 0;
	int y_size = 0;
	double vanilla = 0;
	double sse = 0;
	double avx = 0;

	if(argc != 2){
		return -1;
		fprintf(stderr, "args wrong");
	}else{
		size_kb = atol(argv[1]);
	}

	x_size = sqrt((size_kb*1024.0) /(2.0 * sizeof(type)));
	y_size = x_size;
	if( posix_memalign( (void**)&grid_new, 64, sizeof(type)*x_size*y_size) != 0){
		perror("grid_new");
	}
	if( posix_memalign( (void**)&grid_old, 64, sizeof(type)*x_size*y_size) != 0){
		perror("grid_old");
	}
	
	init(grid_new, grid_old, x_size, y_size);
	vanilla = run_vanilla(grid_new, grid_old, x_size, y_size);
	
	init(grid_new, grid_old, x_size, y_size);
	sse = run_sse(grid_new, grid_old, x_size, y_size);
	
	init(grid_new, grid_old, x_size, y_size);
	avx = run_avx(grid_new, grid_old, x_size, y_size);
	
	printf("%d, %f, %f, %f \n", size_kb, vanilla, sse, avx);
	
	free(grid_new);
	free(grid_old);
	return 0;
}

double run_vanilla(type * grid_new, type * grid_old, int x_size, int y_size){
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	long limit = 1;
	double start_time = 0.0;
	double end_time= 0.0;
	type * temp;

		
	//draw_grid(grid_new, x_size, y_size, "vanilla_before.ppm");	
	while( (end_time-start_time) <= 1.0){
		start_time = get_time();
		for(j = 0; j < limit; ++j){
			jacobi_vanilla(grid_new, grid_old, x_size, y_size);
			temp = grid_old;
			grid_old = grid_new;
			grid_new = temp;
		}
		end_time = get_time();
		//printf("%f start, %f end \n", start_time, end_time);
		//printf("%d limit \n", limit);
		limit *= 2;
	}
	//draw_grid(grid_new, x_size, y_size, "vanilla_after.ppm");   
	limit /= 2;
	double mups = ((double)limit*(double)x_size*(double)y_size/1000000.0)/(end_time-start_time);

	return mups;	
}

double run_sse(type * grid_new, type * grid_old, int x_size, int y_size){
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	long limit = 1;
	double start_time = 0.0;
	double end_time= 0.0;
	type * temp;	
	
	//draw_grid(grid_new, x_size, y_size, "sse_before.ppm");	
	while( (end_time-start_time) <= 1.0){

		start_time = get_time();
		for(j = 0; j < limit; ++j){
			jacobi_sse(grid_new, grid_old, x_size, y_size);
			temp = grid_old;
			grid_old = grid_new;
			grid_new = temp;
		}
		end_time = get_time();
		//printf("%f start, %f end \n", start_time, end_time);
		//printf("%d limit \n", limit);
		limit *= 2;
	}
	//draw_grid(grid_new, x_size, y_size, "sse_after.ppm");   
	limit /= 2;
	double mups = ((double)limit*(double)x_size*(double)y_size/1000000.0)/(end_time-start_time);

	return mups;	
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
	double mups = ((double)limit*(double)x_size*(double)y_size/1000000.0)/(end_time-start_time);

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
	//linker Rankd init
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

