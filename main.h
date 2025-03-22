/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef main_h
#define main_h

#include <string>
#include <vector>

void print_usage(std::string program_name);

int main(int argc, char* args[]);

void add_files(std::string data_path, std::vector<std::string>& file_list);

std::string get_checksum(std::string data_path, bool quiet);

#endif
