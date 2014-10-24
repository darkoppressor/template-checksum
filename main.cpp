#include "main.h"
#include "string_stuff.h"
#include "file_io.h"
#include "print_error.h"
#include "sorting.h"

#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/crc.hpp>

using namespace std;

void print_usage(string program_name){
    cout<<"Usage: "<<program_name<<" [path/to/data/]\n";
    cout<<"path/to/data/ should point to the directory with the data that a checksum is required for\n";
}

int main(int argc,char* args[]){
    File_IO file_io;

    file_io.remove_directory("log-checksum");

    //Can this even happen?
    if(argc<=0){
        print_error("Did not receive the program name");

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
    File_IO file_io;

    string checksum="";
    string checksum_data="";

    string log="";
    uint32_t files=0;

    vector<string> file_list;

    for(File_IO_Directory_Iterator it(data_path);it.evaluate();it.iterate()){
        string file_path=it.get_full_path();

        //If the file is not a directory.
        if(it.is_regular_file()){
            file_list.push_back(file_path);
        }
        else{
            log+="File '"+file_path+"' not parsed because it is not a regular file\n";
        }
    }

    quick_sort(file_list);

    for(int i=0;i<file_list.size();i++){
        File_IO_Load load(file_list[i]);

        if(load.file_loaded()){
            files++;

            string data=load.get_data();

            log+="Length (in bytes) of file '"+file_list[i]+"': "+string_stuff.num_to_string(data.length())+"\n";

            checksum_data+=data;
        }
        else{
            print_error("Error loading file for checksum calculation: '"+file_list[i]+"'");
        }
    }

    log+="Files parsed: "+string_stuff.num_to_string(files)+"\n";
    log+="Checksum data length in bytes: "+string_stuff.num_to_string(checksum_data.length())+"\n";

    if(checksum_data.length()>0){
        boost::crc_32_type result;
        result.process_bytes(checksum_data.data(),checksum_data.length());

        checksum=string_stuff.num_to_string((uint32_t)result.checksum());
    }

    log+="Checksum: "+checksum+"\n";

    print_error(log);

    return checksum;
}
