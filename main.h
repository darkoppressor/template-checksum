/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef main_h
#define main_h

#include <string>

void print_usage(std::string program_name);

int main(int argc,char* args[]);

std::string get_checksum(std::string data_path,bool quiet);

#endif
