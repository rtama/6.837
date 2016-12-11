#include <vector>
#include "vertexrecorder.h"
#include "particle.h"

Particle::Particle(Vector3f pos, Vector3f vel, float r) {
    setPosition(pos);
    setVelocity(vel);
    setRadius(r);
}

