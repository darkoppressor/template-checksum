/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef sorting_h
#define sorting_h

#include <vector>
#include <cmath>

template<typename Object>
void quick_sort (std::vector<Object>& objects) {
    if (objects.size() <= 1) {
        return;
    }

    int pivot_index = (int) floor((double) (objects.size() - 1) / 2.0);

    std::vector<Object> less_than;
    std::vector<Object> greater_than;
    Object pivot = objects[pivot_index];

    for (int i = 0; i < objects.size(); i++) {
        if (i != pivot_index) {
            if (objects[i] <= pivot) {
                less_than.push_back(objects[i]);
            } else {
                greater_than.push_back(objects[i]);
            }
        }
    }

    quick_sort(less_than);
    quick_sort(greater_than);

    objects = less_than;
    objects.push_back(pivot);
    objects.insert(objects.end(), greater_than.begin(), greater_than.end());
}

#endif
