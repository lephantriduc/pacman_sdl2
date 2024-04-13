#pragma once

#include "Game.hpp"

class Particle {
public :
    double x, y;
    double dx, dy;
    int size;
    Uint8 r, g, b, a;
    int lifespan;
};

class Fireworks{
public :
    double x, y;
    double dx, dy;
    Uint8 r, g, b, a;
    int timer;
};

const int Num_Particles = 250;

inline std::vector<Particle> particles;
inline std::vector<Fireworks> fireworks;

inline void createParticle(double x, double y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    for (int i = 0; i < Num_Particles; ++i) {
        Particle p;
        p.x = x;
        p.y = y;
        double angle = 2 * M_PI * (rand() % 1000 / 1000.0);
        double speed = (rand() % 10 + 5) / 10.0;
        p.dx = speed * cos(angle);
        p.dy = speed * sin(angle);
        p.size = rand() % 5 + 1; // Random size
        p.r = r;
        p.g = g;
        p.b = b;
        p.a = a;
        p.lifespan = rand() % 60 + 30; // Random lifespan
        particles.push_back(p);
    }
}

inline void createFirework(double x, double y) {
    Fireworks fw;
    fw.x = x;
    fw.y = y;
    double angle = atan2(fw.y - SCREEN_HEIGHT / 2, fw.x - SCREEN_WIDTH / 2);
    double speed = (rand() % 5 + 5) / 10.0;
    fw.dx = -speed * cos(angle); // Fireworks move towards the center of the screen
    fw.dy = -speed * sin(angle); // Fireworks move towards the center of the screen
    fw.r = rand() % 256; // Bright color (100-255)
    fw.g = rand() % (fw.r + 1) + 255 - fw.r; // Bright color (100-255)
    fw.b = 510 - fw.r - fw.g; // Bright color (100-255)
    fw.timer = rand() % 60 + 30; // Random lifetime
    fireworks.push_back(fw);
}

inline void update() {
    for (int i = fireworks.size() - 1; i >= 0; --i) {
        fireworks[i].x += fireworks[i].dx;
        fireworks[i].y += fireworks[i].dy;
        fireworks[i].dy += 0.05; // Gravity
        fireworks[i].timer--;

        if (fireworks[i].timer <= 0) {
            createParticle(fireworks[i].x, fireworks[i].y, fireworks[i].r, fireworks[i].g, fireworks[i].b, fireworks[i].a);
            fireworks.erase(fireworks.begin() + i);
        }
    }

    for (int i = particles.size() - 1; i >= 0; --i) {
        particles[i].x += particles[i].dx;
        particles[i].y += particles[i].dy;
        particles[i].dy += 0.05; // Gravity
        particles[i].lifespan--;
        particles[i].a = particles[i].lifespan * 255 / 90; // Decrease alpha value over time

        if (particles[i].lifespan <= 0) {
            particles.erase(particles.begin() + i);
        }
    }
}