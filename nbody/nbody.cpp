#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>

using namespace std;

struct Particle {
    double mass;
    double x, y, z, vx, vy, vz, fx, fy, fz;
};

//initialize particles with random position & velocity
void initialize(vector<Particle>& particles, int nbpart) {
    for (int i = 0; i < nbpart; i++) {
        Particle p;
        p.mass = 1.0;
        p.x = rand() % 100;
        p.y = rand() % 100;
        //using x-y plane
        p.z = 0;
        p.vx = rand() % 100;
        p.vy = rand() % 100;
        p.vz = 0;
        p.fx = 0.0;
        p.fy = 0.0;
        p.fz = 0.0;
        particles.push_back(p);
    }
}

//calculate gravitational forces
void computeForces(vector<Particle>& particles) {
    const double G = 6.674e-11;
    const double softening = 1e-10;
    //forces reset to 0
    for(size_t i = 0; i < particles.size(); i++) {
        particles[i].fx = 0.0;
        particles[i].fy = 0.0;
        particles[i].fz = 0.0;
        for(size_t j = 0; j < particles.size(); j++) {
            if (i != j) {
                double dx = particles[j].x - particles[i].x;
                double dy = particles[j].y - particles[i].y;
                double dz = particles[j].z - particles[i].z;
                //calculate squared distance
                double distanceSq = dx*dx + dy*dy + dz*dz;
                double distance = sqrt(distanceSq + softening);
                //gravitational force magnitude
                double force = G * particles[j].mass * particles[i].mass / distanceSq;
                //force components added to each particle
                particles[i].fx += dx * force / distance;
                particles[i].fy += dy * force / distance;
                particles[i].fz += dz * force / distance;
            }
        }
    }
}

//update particle positions
void update(vector<Particle>& particles, double dt) {
    for(size_t i = 0; i < particles.size(); i++) {
        //calculate acceleration
        double ax = particles[i].fx / particles[i].mass;
        double ay = particles[i].fy / particles[i].mass;
        double az = particles[i].fz / particles[i].mass;
        //update velocity
        particles[i].vx += ax * dt;
        particles[i].vy += ay * dt;
        particles[i].vz += az * dt;
        //update position
        particles[i].x += particles[i].vx * dt;
        particles[i].y += particles[i].vy * dt;
        particles[i].z += particles[i].vz * dt;
    }
}

//write particles to file
void output(vector<Particle>& particles, int timeStep, ofstream& file) {
    file << particles.size() << endl;
    for(size_t i = 0; i < particles.size(); i++) {
        file << "\t" << particles[i].mass << "\t" << particles[i].x << "\t" << particles[i].y << "\t" << particles[i].z;
        file << "\t" << particles[i].vx << "\t" << particles[i].vy << "\t" << particles[i].vz;
        file << "\t" << particles[i].fx << "\t" << particles[i].fy << "\t" << particles[i].fz;
    }
    file << endl;
}

int main(int argc, char* argv[]) {
    int numParticles = 10;
    double dt = 0.01;
    int numIterations = 10000;
    string outputFile = "nbody_output.tsv";

    if (argc == 4) {
        numParticles = atoi(argv[1]);
        dt = atof(argv[2]);
        numIterations = atoi(argv[3]);
    } else {
        cout << "Please enter the following arguments: ./nbody [numParticles] [dt] [numIterations]" << endl;
    }
    
    vector<Particle> particles;
    initialize(particles, numParticles);
    ofstream file(outputFile);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < numIterations; i++) {
        computeForces(particles);
        update(particles, dt);
        output(particles, i, file);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    file.close();
    return 0;
}