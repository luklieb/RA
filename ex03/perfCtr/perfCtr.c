#include<likwid.h>
#include<stdlib.h>
#include<stdio.h>


int main(int args, const char** argv){

	if(args != 2){
		fprintf(stderr, "falsche Para\n");
		return 1;
	}
	int size_kb = atoi(argv[1]);
	int num_entries = size_kb / sizeof(float);
	float * A;
	if(posix_memalign( (void**)&A, 64, num_entries*sizeof(float))){
		fprintf(stderr, "memalign\n");
		return 1;
	}

	int i, r;
	float sum = 0.0;
	for(i=0; i<num_entries; ++i){
		A[i]=0.001f;
	}
		
	LIKWID_MARKER_INIT;
	LIKWID_MARKER_START("cache");

	for(r=0; r<10000; ++r){
		
		#pragma vector aligned
		#pragma nounroll
		for(i=0; i<num_entries; i=i+16){
			sum += A[i];
		}
	}

	LIKWID_MARKER_STOP("cache");
	LIKWID_MARKER_CLOSE;	

	printf("%f", sum);
	return 0;
}
