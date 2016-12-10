#ifndef RIGIDSYSTEM_H
#define RIGIDSYSTEM_H

#include <vector>
#include "vertexrecorder.h"
#include "particlesystem.h"

class RigidSystem : public ParticleSystem
{
public:
    RigidSystem();

    std::vector<Vector3f> evalF(std::vector<Vector3f> state) override;
    void draw(GLProgram&);

    // inherits
    // std::vector<Vector3f> m_vVecState;
};

#endif
