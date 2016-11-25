#include <iostream>
#include "cacheLine.hpp"
#include <cassert>
#include <vector>
#include <cmath>

#include <likwid.h>





void cache_init(vector<vector<cacheLine>> & cache, const int size_cl, const int number_cl_set, const int number_sets) ;
void print_cache( vector<vector<cacheLine>> & cache, const int size_cl, const int number_cl_set, const int number_sets);
bool cache_access(vector<vector<cacheLine>> & cache, const int & size_cl, const int & number_cl_set, const int & number_sets, const uint64_t & address);
float reduction_sum_modified(float *A, int N);


using std::vector;




int main(int argv, const char* args[]){

	if(argv != 6){
		std::cerr << "Falsche Anzahl an Parametetr" << std::endl;
		return EXIT_FAILURE; 
	}
	const int size_cache = atoi(args[1]); //in Byte
	const int number_sets = atoi(args[2]);
	const int asso = atoi(args[3]);
	const int size_cl = atoi(args[4]); //in Byte
	const uint64_t size_array = atoi(args[5]); //in Byte
	assert( (size_cache%size_cl) == 0);
	assert( (size_cl*number_sets*asso) == size_cache );
	
	const int number_cl = size_cache/size_cl;
	assert( (number_cl%number_sets) == 0 );
	const int number_cl_set = number_cl / number_sets;
	assert( number_cl_set == asso );
	
	assert( size_array%sizeof(float) == 0 );
	float sum = 0.0;
	
	float * A = new float[size_array/sizeof(float)]();	
	/*void* temp = nullptr;
	if(posix_memalign(&temp, 64, size_array))
		std::cerr << "error memalign" << std::endl;
	float * A = new(temp) float[size_array/sizeof(float)];
	*/
	for(int i = 0; i < ((long)size_array)/sizeof(float); ++i){
		A[i]=0.0001;
	}
	

	vector<vector<cacheLine>> cache;
	cache_init(cache, size_cl, number_cl_set, number_sets);
	int total_loads = 0;
	int load_hits = 0;
	
	for(uint64_t i = 0; i<size_array; i += size_cl){
		cache_access(cache, size_cl, number_cl_set, number_sets, i); 	
	}
	
	for(uint64_t i = 0; i<size_array; i += size_cl){
		//print_cache(cache, size_cl, number_cl_set, number_sets);
		//std::cout << std::endl << std::endl;
		
		total_loads ++;
		if( cache_access(cache, size_cl, number_cl_set, number_sets, i) ){
			load_hits ++;
		}
		
		//std::cout << "cl at address: " <<  i << std::endl;
	}
	
	std::cout << "Total loads: " << total_loads << ", Hits: " << load_hits << ", Hit rate cacheSim: " << ((double)load_hits/(double)total_loads)*100.0 << "%" << std::endl;



	LIKWID_MARKER_INIT;
	LIKWID_MARKER_START("CACHE");

	sum = reduction_sum_modified(A, size_array/sizeof(float));

	LIKWID_MARKER_STOP("CACHE");
	LIKWID_MARKER_CLOSE;


	std::cout << sum << std::endl;
	//delete [] A;
	return EXIT_SUCCESS;
}











bool cache_access(vector<vector<cacheLine>> & cache, const int & size_cl, const int & number_cl_set, const int & number_sets, const uint64_t & address){
		
	bool free = false;
	uint64_t tag_bits = address >> (uint64_t) (log2(size_cl)+log2(number_sets));
	uint64_t set_bits = address >> (uint64_t) (log2(size_cl));
	set_bits = set_bits & (uint64_t) (pow(2, log2(number_sets)) -1);
	vector<cacheLine>::iterator it_cl;
	vector<cacheLine>::iterator it_cl_oldest = cache[set_bits].end();
	int oldest = cache[set_bits].begin()->get_age();


	for(it_cl = cache[set_bits].begin(); it_cl != cache[set_bits].end(); ++it_cl){
		if( (*it_cl).valid() && ((*it_cl).get_tag() == tag_bits)){
			(*it_cl).inc_age();	
			return true; //cache hit
		}
	}	
	
	for(it_cl = cache[set_bits].begin(); it_cl != cache[set_bits].end(); ++it_cl){
		if( !(*it_cl).valid() ){
			(*it_cl).set_tag(tag_bits);
			(*it_cl).zero_age();
			//(*it_cl).inc_age(); //evtl nicht
			(*it_cl).set_valid(true);
			//return false; //cache miss
			free = true;
		}
		if( (*it_cl).get_age() >= oldest ){
			//std::cout << " LRU bedingung Pointer kopie" << std::endl;
			oldest = (*it_cl).get_age();
			it_cl_oldest = it_cl;
		}
		(*it_cl).inc_age();
	}

	if (free)
		return false;
	if(it_cl_oldest == cache[set_bits].end()){
		std::cerr << "nullptr fuer oldest" << std::endl;
	}
	(*it_cl_oldest).set_tag(tag_bits);
	(*it_cl_oldest).zero_age();
	//(*it_cl_oldest).inc_age(); //evtl nicht
	(*it_cl_oldest).set_valid(true);
	return false; //cache miss & LRU	
	
}







void cache_init(vector<vector<cacheLine>> & cache, const int size_cl, const int number_cl_set, const int number_sets ){
	uint64_t  global = 0;
	for( auto i = 0; i < number_sets; ++i){
		vector<cacheLine> row;
		for ( auto j = 0; j < number_cl_set; ++j){
			row.push_back(cacheLine(size_cl, global, i, j));
			global++;  
		}
		cache.push_back(row);
		row.clear();
	}
}

void print_cache( vector<vector<cacheLine>> & cache, const int size_cl, const int number_cl_set, const int number_sets){
	
	for(vector<vector<cacheLine>>::iterator it = cache.begin(); it != cache.end(); ++it){
		for(vector<cacheLine>::iterator it2 = it->begin(); it2 != it->end(); ++it2){
			std::cout << (*it2)  << std::endl;
		}
	}
	/*
	for( auto i = 0; i < number_sets; ++i){
                 for ( auto j = 0; j < number_cl_set; ++j){
                         cout << cache[i][j] << endl;  
                  }       
          }  	
	*/
}


	


