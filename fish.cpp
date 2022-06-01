#include "fish.h"
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>

using namespace Eigen;
using namespace std;

int main(int argc, char *argv[]) {
 
    vector<Fishy> boids; // Vector to store boids and foods
    vector<Food> foods;     
    double size,neighbor_radius,num_neighbors,mass,collision,centering,velocity,hunger,damping,dt,length;        // Various Parameters descripiton

    string fname(argv[1]);
    string line;
    ifstream f(fname);
    int fishSize;
    int ffood;

    boids.clear();
    foods.clear();

    getline(f, line);  // Parsing the input 
    sscanf(line.c_str(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&size, &neighbor_radius, &num_neighbors, &mass, &collision, &centering,&velocity, &hunger, &damping, &dt, &length);

    getline(f, line); 
    sscanf(line.c_str(), "%d", &fishSize);
   
    for (int i=0; i<fishSize; i++) { // parsing  the boids values
        getline(f, line);
        Fishy boi;
        boi.pos=Vector3d(0,0,0); //Initializing pos,vec
        boi.vel=Vector3d(0,0,0);
        
        sscanf(line.c_str(), "[%lf,%lf,%lf] [%lf,%lf,%lf]", &boi.pos[0], &boi.pos[1],
                &boi.pos[2], &boi.vel[0], &boi.vel[1], &boi.vel[2]);
        boids.push_back(boi);
    }

    getline(f, line);
    sscanf(line.c_str(), "%d", &ffood); // parsing food input
    for (int i=0; i<ffood; i++) {
        getline(f, line);
        Food food;
        sscanf(line.c_str(), "[%lf,%lf,%lf] [%lf,%lf,%lf] %lf", &food.pos[0], &food.pos[1],
                &food.pos[2], &food.vel[0], &food.vel[1], &food.vel[2], &food.t);
        foods.push_back(food);
    }

    int fframes = 0; // calcualting number of frames
    for (double t=0; t<length; t+=dt) {
        fframes++;
    }
    
    cout << fframes << endl;// Output is the number of frames for the viewer

    for (double t=0; t<length; t+=dt) {
        
         for (unsigned int i=0; i<boids.size(); i++) {
            double neighbors = 0;
            boids[i].frc = Vector3d(0,0,0); // Initializing force and center vectors 
            Vector3d center = Vector3d(0,0,0); 

        for (unsigned int j=0; j<boids.size(); j++) {
            if (j == i)
                continue; //checking for neighbour
            
            double dist = (boids[j].pos - boids[i].pos).norm();
            if (dist < neighbor_radius) {
                
                neighbors++;
                center += boids[j].pos;
            
            if(dist>0.00001) //collison avoidance
                boids[i].frc += (velocity*(boids[j].vel - boids[i].vel))+ collision*((boids[j].pos - boids[i].pos) / pow(dist, 3));
             
            }
        }
            //calcualting total force acting
        center = (neighbors != 0) ? (center/neighbors) : boids[i].pos;
        boids[i].frc += centering*(center - boids[i].pos);
    }

        for (unsigned int i=0; i<boids.size(); i++) {
           
            if (boids[i].frc.norm() > 15) {            
                boids[i].frc = 15 * boids[i].frc.normalized(); // limiting max force
            }

            if (boids[i].boxy()) { 
                boids[i].vel *= damping ; //No issue with boundary, hence muli vel with damping
            }
            else {
                boids[i].vel *= -1;       //Inverting the velocity and making the boid swim back as it is touching the boundary
            }

            if (boids[i].vel.norm() > 0.33) {    //limiting Velocity
                boids[i].vel = 0.33 * boids[i].vel.normalized();
            }

            boids[i].pos += boids[i].vel * dt;   // Changing positon wrt time and velocity
        }

        cout << boids.size() << endl;      // pritning the size of boid to output
    for (unsigned int i=0; i<boids.size(); i++) {  // printing the position and velocity of boids 
        cout << "[" << boids[i].pos[0] << "," << boids[i].pos[1] << "," << boids[i].pos[2] << "] ";
        cout << "[" << boids[i].vel[0] << "," << boids[i].vel[1] << "," << boids[i].vel[2] << "]" << endl;
    }
    cout << foods.size() << endl;
    for (unsigned int i=0; i<foods.size(); i++) {  // printing the position of food ,but is zero here as we didn't handle it.
        cout << "[" << foods[i].pos[0] << "," << foods[i].pos[1] << "," << foods[i].pos[2] << "]" << endl;
    }
    }

    return 0;
}

bool Fishy::boxy() { // This functions cheks if the boids is in the bounds  [-0.5,0.5]x[-0.25,0.25]x[-0.125,0.125] , Used the bounds specfied in the https://www.csee.umbc.edu/~adamb/435/proj5.html

    if ( pos[0] > 0.5   || pos[0] < -0.5  || pos[1] > 0.25  || pos[1] < -0.25 || pos[2] > 0.125 || pos[2] < -0.125 )
    return false;

    else
    return true;
}