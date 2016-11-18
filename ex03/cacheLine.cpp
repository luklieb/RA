#include "cacheLine.hpp"


cacheLine::cacheLine(int size, uint64_t global_pos, int set, int pos)
	: global_pos_(global_pos), 
	size_(size),
	set_(set),
	pos_(pos),
	valid_(false),
	age_(0),
	tag_(0U),
	address_(0U)
{}


uint64_t cacheLine::get_global_pos() const{
	return global_pos_;
}
int cacheLine::get_pos() const{
	return pos_;
}
int cacheLine::get_set() const{
	return set_;
}
bool cacheLine::valid() const{
	return valid_;
}
int cacheLine::get_age() const{
	return age_;
}
uint64_t cacheLine::get_tag() const{
	return tag_;
}
uint64_t cacheLine::get_address() const{
	return address_;
}
void cacheLine::set_valid(bool b){
	valid_ = b;
}
void cacheLine::set_tag(uint64_t tag){
	tag_ = tag;
}
void cacheLine::set_address(uint64_t address){
	address_ = address;
}
void cacheLine::inc_age(){
	age_++;
}
void cacheLine::zero_age(){
	age_ = 0;
}


std::ostream & operator<<( std::ostream & os, const cacheLine & cl){
	os << "cl: " << cl.get_global_pos() << ", set: " << cl.get_set() << ", pos: " << cl.get_pos() << ", valid: " << cl.valid() << ", age: " << cl.get_age() << ", address: " << cl.get_address() << ", tag: " << cl.get_tag();; 
	return os;
}

void print_address_to_bits(uint64_t address, uint64_t cl_bits, uint64_t set_bits){
	std::cout << "converting address " << address << " to bits: |";
	for (int i=0; i<64; ++i){
		if (((63-i)==cl_bits-1) || ((63-i)==cl_bits+set_bits-1))
			std::cout << "|";
		std::cout << ((int)(address >> (63 - i)) & 1);
	}
	std::cout << "|" << std::endl;



}






