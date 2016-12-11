#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include "vertexrecorder.h"

class Particle
{
public:
    Particle(Vector3f pos, Vector3f vel, float r);

    // Getter functions
    Vector3f getPosition(){return m_position};
    Vector3f getVelocity(){return m_velocity};
    float getRadius(){return radius;};

    // Setter functions
    void setPosition(Vector3f position) {m_position = position;};
    void setVelocity(Vector3f velocity) {m_velocity= velocity;};
    void setRadius(float r){radius = r;};

private:
    Vector3f m_position;
    Vector3f m_velocity;
    float radius;
};

#endif
