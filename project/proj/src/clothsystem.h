#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vector>

#include "particlesystem.h"

class ClothSystem : public ParticleSystem
{
    ///ADD MORE FUNCTION AND FIELDS HERE
    // add structural springs for particle i (row, col)
    void addStructuralSprings(Spring& spring, int row, int column, int i);

    // add shear springs for particle i (row, col)
    void addShearSprings(Spring& spring, int row, int column, int i);

    // add flex springs for particle i (row, cole)
    void addFlexSprings(Spring& spring, int row, int column, int i);


public:
    ClothSystem();

    // evalF is called by the integrator at least once per time step
    std::vector<Vector3f> evalF(std::vector<Vector3f> state) override;

    // draw is called once per frame
    void draw(GLProgram& ctx);

    // index of particle at position, (i,j) for an nxn cloth
    // 0 indexed, top left = (0,0)
    int indexOf(int i, int j, int n);

    // switch hold point of cloth to middle
    void switchHold();

    void switchWind();

    // inherits
    // std::vector<Vector3f> m_vVecState;
};


#endif
