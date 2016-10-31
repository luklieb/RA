#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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
	
	number_elements = size_kb*1024.0 / sizeof(float);
	array = (float *) malloc(sizeof(float)*number_elements);
	if (array == NULL){
		fprintf(stderr, "malloc error");
		return -1;
	}

//TODO:LOOPUNROLLING

	for(int i = 0; i < number_elements; ++i){
		array [i] = 1.0;
	}

    	#pragma novector
    	#pragma nounroll
	for(limit = 1; end_time-start_time <= 1.0; limit *= 2){

        	start_time = get_time();
        	#pragma novector
        	#pragma nounroll
		for(int i = 0; i < limit; ++i){
            		vec_sum(array, number_elements);
		}
        	end_time = get_time();
	}
    
   	limit /= 2;
	float mups = limit*number_elements/1000000.0/(end_time-start_time);
    
   	// printf("%.2f MUp/s \t %d limit \n", mups, limit);
    	printf("%.2f \n", mups);
	return 0;
}


double get_time(){
    struct timespec a;
    clock_gettime(CLOCK_MONOTONIC, &a);
    double t = (double) a.tv_nsec / (1000000000.0) + (double) a.tv_sec;
    return t;

}


