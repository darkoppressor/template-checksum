/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "print_error.h"

#include <iostream>

using namespace std;

void print_error (string error_message, bool quiet) {
    if (!quiet) {
        cout << "Error: " << error_message << "\n";
    }
}
