#include "main.h"
#include "string_stuff.h"
#include "file_io.h"

#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/crc.hpp>

using namespace std;

void print_error(string error_message){
    cout<<"Error: "<<error_message<<"\n";
}

void print_usage(string program_name){
    cout<<"Usage: "<<program_name<<" [path/to/data/]\n";
    cout<<"path/to/data/ should point to the directory with the data that a checksum is required for\n";
}

int main(int argc,char* args[]){
    File_IO file_io;

    //Can this even happen?
    if(argc<=0){
        cout<<"Error: Did not receive the program name\n";

        return 1;
    }
    else if(argc==1){
        print_usage(args[0]);

        return 0;
    }

    string data_path=args[1];

    string checksum=get_checksum(data_path);

    cout<<checksum;

    ///file_io.save_file("checksum.out",checksum);
}

string get_checksum(string data_path){
    String_Stuff string_stuff;

    string checksum="";
    string checksum_data="";

    for(File_IO_Directory_Iterator it(data_path);it.evaluate();it.iterate()){
        //If the file is not a directory.
        if(it.is_regular_file()){
            string file_path=it.get_full_path();

            File_IO_Load load(file_path);

            if(load.file_loaded()){
                checksum_data+=load.get_data();
            }
            else{
                print_error("Error loading file for checksum calculation: '"+file_path+"'");
            }
        }
    }

    if(checksum_data.length()>0){
        boost::crc_32_type result;
        result.process_bytes(checksum_data.data(),checksum_data.length());

        checksum=string_stuff.num_to_string((uint32_t)result.checksum());
    }

    return checksum;
}
