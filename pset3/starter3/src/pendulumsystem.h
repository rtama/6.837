#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include <vector>
#include "vertexrecorder.h"
#include "particlesystem.h"

class PendulumSystem : public ParticleSystem
{
public:
    PendulumSystem();

    std::vector<Vector3f> evalF(std::vector<Vector3f> state) override;
    void draw(GLProgram&);

    // draw springs connected to particle i
    void drawSprings(int particle_i, GLProgram& gl);

    // inherits
    // std::vector<Vector3f> m_vVecState;
};

#endif
