/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef main_h
#define main_h

#include <string>

void print_usage(std::string program_name);

int main(int argc, char* args[]);

std::string get_checksum(std::string data_path, bool quiet);

#endif
