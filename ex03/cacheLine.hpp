#pragma once
#include <vector>
#include <iostream>


using std::vector;


class cacheLine{

public:
	cacheLine(int size, uint64_t global_pos, int set, int pos);

	uint64_t get_global_pos() const;
	int get_pos() const;
	int get_set() const;
	bool valid() const;
	int get_age() const;
	uint64_t get_tag() const;
	uint64_t get_address() const;
	void set_valid(bool b);
	void set_tag(uint64_t);
	void set_address(uint64_t);
	void inc_age();
	void zero_age();
	
private:
	const int size_;
	const int set_;
	const int pos_;
	const uint64_t global_pos_;
	bool valid_;
	int age_;
	uint64_t tag_;
	uint64_t address_;
};

std::ostream & operator<<( std::ostream & os, const cacheLine & cl);
void print_address_to_bits(uint64_t address, uint64_t cl_bits, uint64_t set_bits);
