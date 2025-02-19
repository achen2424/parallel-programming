#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>
#include <random>

using namespace std;
const double G = 6.674e-11;

struct Particle {
    double mass;
    double x, y, z, vx, vy, vz, fx, fy, fz;
    Particle() : mass(0), x(0), y(0), z(0), vx(0), vy(0), vz(0), fx(0), fy(0), fz(0) {}
    Particle(double mass, double x, double y, double z, double vx, double vy, double vz, double fx, double fy, double fz)
        : mass(mass), x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), fx(fx), fy(fy), fz(fz) {}
};

//initialize particles with random position & velocity
void initialize(vector<Particle>& particles, int nbpart) {
    particles.resize(nbpart);

    if (nbpart == 2) {  //sun at the center and earth
        particles[0] = Particle(1.95e30, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        particles[1] = Particle(5.9e24, 1.5e11, 0, 0, 0, 29800, 0, 0, 0, 0); 
    } 
    else {
        //sun at the center
        particles[0] = Particle(1.95e30, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        //randomly generate particles
        random_device rd;
        //random number generator
        mt19937 gen(rd());
        //random x, y, mass
        uniform_real_distribution<double> dist_x(-5e11, 5e11);
        uniform_real_distribution<double> dist_y(-5e11, 5e11);
        uniform_real_distribution<double> mass_dist(1e20, 1e25);

        for (int i = 1; i < nbpart; i++) {
            double x = dist_x(gen);
            double y = dist_y(gen);
            //2d
            double z = 0;

            double distance = sqrt(x * x + y * y);
            double orbital_speed = sqrt(G * particles[0].mass / distance);
            double vx = -orbital_speed * (y / distance);
            double vy = orbital_speed * (x / distance);
            double vz = 0;
            double mass = mass_dist(gen);

            particles[i] = Particle(mass, x, y, z, vx, vy, vz, 0, 0, 0);
        }
    }
}


//calculate gravitational forces
void computeForces(vector<Particle>& particles) {
    //prevent division by 0
    const double softening = 1e9;
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
                //force components
                particles[i].fx += force * (dx  / distance);
                particles[i].fy += force * (dy / distance);
                particles[i].fz += force* (dz / distance);


                particles[j].fx -= force * (dx  / distance);
                particles[j].fy -= force * (dy / distance);
                particles[j].fz -= force* (dz / distance);
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

//write state of particles to file
void output(vector<Particle>& particles, ofstream& file) {
    file << particles.size();
    for(size_t i = 0; i < particles.size(); i++) {
        file << "\t" << particles[i].mass << "\t" << particles[i].x << "\t" << particles[i].y << "\t" << particles[i].z;
        file << "\t" << particles[i].vx << "\t" << particles[i].vy << "\t" << particles[i].vz;
        file << "\t" << particles[i].fx << "\t" << particles[i].fy << "\t" << particles[i].fz;
    }
    file << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Please provide 4 arguments: " << argv[0] << " num_particles time_step num_iterations log_interval" << std::endl;
        return 1;
    }

    //convert string to int
    int numParticles = std::stoi(argv[1]);
    double dt = std::stoi(argv[2]);
    int numIterations = std::stoi(argv[3]);
    int log_interval = std::stoi(argv[4]);
    string outputFile = "solar.tsv";
    
    vector<Particle> particles;
    initialize(particles, numParticles);
    ofstream file(outputFile);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < numIterations; i++) {
        computeForces(particles);
        update(particles, dt);

        //dump state at every "log_interval" steps
        if (i % log_interval == 0) {
            output(particles, file);
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    file.close();
    return 0;
}




