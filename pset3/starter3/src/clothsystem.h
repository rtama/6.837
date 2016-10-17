#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vector>

#include "particlesystem.h"

class ClothSystem : public ParticleSystem
{
    ///ADD MORE FUNCTION AND FIELDS HERE
public:
    ClothSystem();

    // evalF is called by the integrator at least once per time step
    std::vector<Vector3f> evalF(std::vector<Vector3f> state) override;

    // draw is called once per frame
    void draw(GLProgram& ctx);

    // index of particle at position, (i,j) for an nxn cloth
    // 0 indexed, top left = (0,0)
    int indexOf(int i, int j, int n);

    // inherits
    // std::vector<Vector3f> m_vVecState;
};


#endif
