#ifndef fish_H_
#define fish_H_

#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
using namespace Eigen;
using namespace std;


struct Food {               // Struct to handle food 
    Vector3d pos;
    Vector3d vel;
    double t; 
};

class Fishy {               // Class fishy has values for calcualting position , velocity and other variables
     public:
     
        inline bool boxy();

        Vector3d pos;     
        Vector3d vel;     
        vector<int> neighs; 
        Vector3d frc;        
};



#endif
