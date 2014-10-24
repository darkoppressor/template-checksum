#ifndef main_h
#define main_h

#include <string>

void print_error(std::string error_message);

void print_usage(std::string program_name);

int main(int argc,char* args[]);

std::string get_checksum(std::string data_path);

#endif
