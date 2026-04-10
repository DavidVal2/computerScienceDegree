//
// Created by david on 3/08/2025.
//

#include "Arreglos.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void Arreglos::Arreglador() {
    vector<int> v(100);
    srand(time(0));
    for (int& num : v)
        num = rand() % 5000 + 1;

    int maxPosicion = 0, minPosicion = 0;
    for (int i = 1; i < 100; i++) {
        if (v[i] > v[maxPosicion]) maxPosicion = i;
        if (v[i] < v[minPosicion]) minPosicion = i;
    }

    swap(v[0], v[maxPosicion]);
    if (minPosicion == 0) minPosicion = maxPosicion + 1;
    swap(v[99], v[minPosicion]);

    cout << "Mayor en la primera posicion: " << v[0] << endl;
    cout << "Menor en la ultima posicion: " << v[99] << endl;
};

