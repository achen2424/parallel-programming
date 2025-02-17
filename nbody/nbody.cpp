#include <iostream>
#include <vector>

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
                double distanceSq = dx*dx + dy*dy + dz*dz + softening;
                double distance = sqrt(distanceSq);
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

int main() {

}