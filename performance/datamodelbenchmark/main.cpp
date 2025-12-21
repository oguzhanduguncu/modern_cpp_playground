//
// Created by oguzh on 21.12.2025.
//

/*AoS update: 6941137
AoS read: 5697677
SoA update: 4575963
SoA read: 4895066*/
#include <iostream>
#include <vector>
#include <chrono>

constexpr double dt = 0.16;
volatile double sum;
size_t N = 1'000'000;

struct Particle {
    double x, y;
    double vx, vy;
};

std::vector<Particle> particles;  //AoS

struct Particles {                //SoA
    std::vector<double> x, y;
    std::vector<double> vx, vy;
};

void integratormodel1(Particle& p) {
    p.x += p.vx * dt;
    p.y += p.vy * dt;
}

void integratormodel1_soa(double &x, double &y, double &vx, double &vy) {
    x += vx * dt;
    y += vy * dt;
}

void integratormodel2(const double x, const double y) {
    sum += x;
    sum += y;

}

 int main () {
    particles.resize(N);
    Particles particles_soa;
    particles_soa.x.resize(N);
    particles_soa.y.resize(N);
    particles_soa.vx.resize(N);
    particles_soa.vy.resize(N);
    for (int i = 0; i < N; i++) {
        particles[i].x = 1;
        particles[i].y = 2;
        particles[i].vx = 3;
        particles[i].vy = 4;
        particles_soa.x[i] = 1;
        particles_soa.y[i] = 1;
        particles_soa.vx[i] = 1;
        particles_soa.vy[i] = 1;
    }
    auto start = std::chrono::steady_clock::now();
    for (int j = 0; j < N; j++) {
        integratormodel1(particles[j]);
    }
    auto m1 = std::chrono::steady_clock::now();
    for (int j = 0; j < N; j++) {
        integratormodel2(particles[j].x, particles[j].y);
    }
    auto m2 = std::chrono::steady_clock::now();
    for (int j = 0; j < N; j++) {
        integratormodel1_soa(particles_soa.x[j], particles_soa.y[j],
            particles_soa.vx[j], particles_soa.vy[j]);
    }
    auto m3 = std::chrono::steady_clock::now();
    for (int j = 0; j < N; j++) {
        integratormodel2(particles_soa.x[j], particles_soa.y[j]);
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "AoS update: " << (m1-start).count() << '\n';
    std::cout << "AoS read: " << (m2-m1).count() << '\n';
    std::cout << "SoA update: "<< (m3-m2).count() << '\n';
    std::cout << "SoA read: " << (end-m3).count();
}