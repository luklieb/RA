#include <iostream>
#include "cacheLine.hpp"
#include <cassert>
#include <vector>
#include <cmath>



void cache_init(vector<vector<cacheLine>> & cache, const int size_cl, const int number_cl_set, const int number_sets) ;
void print_cache( vector<vector<cacheLine>> & cache, const int size_cl, const int number_cl_set, const int number_sets);
bool cache_access(vector<vector<cacheLine>> & cache, const int & size_cl, const int & number_cl_set, const int & number_sets, const uint64_t & address);


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

	//const int bits_address = 64;
	//const int bits_word = log2(size_cl);
	//const int bits_set = log2(number_sets);
	//const int bits_tag = bits_address - bits_word - bits_set;

	vector<vector<cacheLine>> cache;
	cache_init(cache, size_cl, number_cl_set, number_sets);
	//print_cache(cache, size_cl, number_cl_set, number_sets);
	int total_loads = 0;
	int load_hits = 0;
	
	for(uint64_t i = 0; i<size_array; i += size_cl){
		cache_access(cache, size_cl, number_cl_set, number_sets, i); 
		
		
	}
	print_cache(cache, size_cl, number_cl_set, number_sets);
	
	for(uint64_t i = 0; i<size_array; i += size_cl){
		total_loads ++;
		if( cache_access(cache, size_cl, number_cl_set, number_sets, i) ){
			load_hits ++;
		}
		
	}
	std::cout << "hallo" << std::endl;
	std::cout << "Total loads: " << total_loads << ", Hits: " << load_hits << ", Hit rate: " << ((double)load_hits/(double)total_loads)*100.0 << "%" << std::endl;

	return EXIT_SUCCESS;
}

bool cache_access(vector<vector<cacheLine>> & cache, const int & size_cl, const int & number_cl_set, const int & number_sets, const uint64_t & address){

	vector<cacheLine>::iterator it_cl;
	vector<cacheLine>::iterator it_cl_oldest;
	
	for(it_cl = cache[address%number_sets].begin(); it_cl != cache[address%number_sets].end(); ++it_cl){
		if( (*it_cl).valid() && ((*it_cl).get_address() == address)){
			(*it_cl).inc_age();	
			return true; //cache hit
		}
	}	
	
	for(it_cl = cache[address%number_sets].begin(); it_cl != cache[address%number_sets].end(); ++it_cl){
		int oldest = 0;
		bool lru = false;
		if( !(*it_cl).valid() ){
			(*it_cl).set_address(address);
			(*it_cl).zero_age();
			(*it_cl).inc_age(); //evtl nicht
			(*it_cl).set_valid(true);
			return false; //cache miss
		}
		if( (*it_cl).get_age() <= oldest ){
			oldest = (*it_cl).get_age();
			it_cl_oldest = it_cl;
		}
	}
//	std::cout << "LRU von: " << std::endl;
	(*it_cl_oldest).set_address(address);
	(*it_cl_oldest).zero_age();
	//(*it_cl_oldest).inc_age(); //evtl nicht
	(*it_cl_oldest).set_valid(true);
//	std::cout << "vor BUs fehler" << std::endl;
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
