/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "print_error.h"

#include <iostream>

using namespace std;

void print_error(string error_message,bool quiet){
    if(!quiet){
        cout<<"Error: "<<error_message<<"\n";
    }
}
