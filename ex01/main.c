#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vec_sum(float *A, int N);
double get_time();


int main(int argc, char** argv){

	int size_kb = 0;
	float *array;
	int number_elements = 0;
	int limit = 1;
	long start_time;
	long end_time;
	struct timespec time;

	if(argc != 2){
		return -1;
	}else{
		size_kb = atoi(argv[1]);
	}
	
	number_elements = size_kb / sizeof(float);
	array = malloc(sizeof(float)*number_elements);
	if (array == NULL){
		fprintf("calloc error");		
		return -1;
	}

	for(int i = 0; i < number_elements; ++i){
		array [i] = 1.0;
	}

	for(limit = 1; end_time-start_time <= 1000000000; limit *= 2){

		for(int i = 0; i < limit; ++i){
			
			
		}


	}
	return 0;
}


double get_time(){
	struct timespec *t;
	if( clock_gettime(CLOCK_REALTIME, struct timespec *t) )
		return (double)(t->tv_sec) + (((double)(t->tv_nsec))/1000000000.0);
	else
		return -1;

}


