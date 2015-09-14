/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "print_error.h"
#include "file_io.h"

#include <iostream>

using namespace std;

void print_error(string error_message){
    File_IO file_io;

    string error_msg="Error: "+error_message+"\n";

    cout<<error_msg;

    file_io.save_file("log-checksum",error_msg,true);
}
