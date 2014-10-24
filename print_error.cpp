#include "print_error.h"
#include "file_io.h"

using namespace std;

void print_error(string error_message){
    File_IO file_io;

    string error_msg="Error: "+error_message+"\n";

    file_io.save_file("log-checksum",error_msg,true);
}