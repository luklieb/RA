#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void vec_sum(float *A, int N);
float vec_sum_2(float *A, int N);
float vec_sum_3(float *A, int N);
float vec_sum_4(float *A, int N);
float vec_sum_8(float *A, int N);
double get_time();


int main(int argc, char** argv){

	long size_kb = 0;
	int loop = 0;
	float * array;
	int number_elements = 0;
	long limit = 1;
	double start_time = 0.0;
	double end_time= 0.0;
	float (*calculate) (float *, int);

	if(argc != 3){
		return -1;
		fprintf(stderr, "args wrong");
	}else{
		size_kb = atol(argv[1]);
		loop = atoi(argv[2]);
	}
	
	number_elements = (size_kb*1024.0) / sizeof(float);
	array =  malloc(sizeof(float)*number_elements);
	if (array == NULL){
		fprintf(stderr, "malloc error");
		return -1;
	}
	/*switch(loop) {
        	case 1: calculate = vec_sum; break;
                case 2: calculate = vec_sum_2; break;
                case 3: calculate = vec_sum_3; break;
    	     	case 4: calculate = vec_sum_4; break;
                case 8: calculate = vec_sum_8; break;
                default: fprintf(stderr, "wrong function call in switch case \n"); break;
         }
	*/
	int i = 0;
	for(i = 0; i < number_elements; ++i){
		array [i] = 1.0;
	}

	long j = 0;
	while( (end_time-start_time) <= 1.0){

        	start_time = get_time();
		for(j = 0; j < limit; ++j){
			vec_sum(array, number_elements);
		}
        	end_time = get_time();
		//printf("%f start, %f end \n", start_time, end_time);
	//	printf("%d limit \n", limit);
		limit *= 2;
	}
    
   	limit /= 2;
	double mups = ((double)limit*(double)number_elements/1000000.0)/(end_time-start_time);
    
   	printf("%f", mups);
    	//printf("%f mups, %f start, %f end, %f time,  %d limit, %d elements, %ld size \n", mups, start_time, end_time, (end_time-start_time), limit, number_elements, size_kb);
	free(array);
	return 0;
}


double get_time(void){
    	struct timespec a;
    	clock_gettime(CLOCK_MONOTONIC, &a);
    	double t = (double) a.tv_nsec / (1000.0*1000.*1000.0) + (double) a.tv_sec;
	//printf("%d nsec, %d sec \n", a.tv_nsec, a.tv_sec);
	//printf("%f time function \n", t);
	return t;

}


