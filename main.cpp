/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

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
    //Not enforcing quiet here, because if you failed to type the command correctly,
    //you have bigger problems
    cout<<program_name<<" - compute a CRC32 hash from a directory full of data files\n";
    cout<<"Output will be either the computed hash if the program succeeds\nor an empty string if the program fails, on standard output\n";
    cout<<"Usage: "<<program_name<<" DATA-DIRECTORY QUIET\n";
    cout<<"QUIET is optional and should be either 'true/1' or 'false/0' (default = false)\n";
}

int main(int argc,char* args[]){
    String_Stuff string_stuff;

    //Can this even happen?
    if(argc<=0){
        //This is passed as quiet, so it will never show up even if it happens
        //This is not ideal, but I can't risk it messing up the output
        print_error("Did not receive the program name",true);

        return 1;
    }
    else if(argc<2 || argc>3){
        print_usage(args[0]);

        return 0;
    }

    string data_path=args[1];

    bool quiet=false;
    if(argc==3){
        //We better pass true as quiet here,
        //since we are reading in the quiet argument
        quiet=string_stuff.string_to_bool(args[2],true);
    }

    string checksum=get_checksum(data_path,quiet);

    cout<<checksum;

    return 0;
}

string get_checksum(string data_path,bool quiet){
    String_Stuff string_stuff;

    string checksum="";
    string checksum_data="";

    ///string log="";
    ///uint32_t files=0;

    vector<string> file_list;

    for(File_IO_Directory_Iterator it(data_path);it.evaluate();it.iterate()){
        string file_path=it.get_full_path();

        //If the file is not a directory.
        if(it.is_regular_file()){
            file_list.push_back(file_path);
        }
        else{
            ///log+="File '"+file_path+"' not parsed because it is not a regular file\n";
        }
    }

    quick_sort(file_list);

    for(int i=0;i<file_list.size();i++){
        File_IO_Load load(file_list[i]);

        if(load.file_loaded()){
            ///files++;

            string data=load.get_data();

            ///log+="Length (in bytes) of file '"+file_list[i]+"': "+string_stuff.num_to_string(data.length())+"\n";

            checksum_data+=data;
        }
        else{
            print_error("Error loading file for checksum calculation: '"+file_list[i]+"'",quiet);

            return "";
        }
    }

    ///log+="Files parsed: "+string_stuff.num_to_string(files)+"\n";
    ///log+="Checksum data length in bytes: "+string_stuff.num_to_string(checksum_data.length())+"\n";

    if(checksum_data.length()>0){
        boost::crc_32_type result;
        result.process_bytes(checksum_data.data(),checksum_data.length());

        checksum=string_stuff.num_to_string((uint32_t)result.checksum());
    }

    ///log+="Checksum: "+checksum+"\n";

    ///print_error(log,quiet);

    return checksum;
}
