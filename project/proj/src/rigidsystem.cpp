#include "rigidsystem.h"

#include <cassert>
#include "camera.h"
#include "vertexrecorder.h"
#include "spring.h"

#include <iostream>
#include <string>

// TODO adjust to number of particles.
const int NUM_PARTICLES = 5;        // num_particles includes fixed point
const float m = .05;
const Vector3f g = Vector3f(0.0, -9.8, 0.0);
const float k_vd = .02;
const float k_s = 1.5;
const float restLength = 0.01;


RigidSystem::RigidSystem()
{

    // TODO 4.2 Add particles for simple pendulum
    // TODO 4.3 Extend to multiple particles

    // To add a bit of randomness, use e.g.
    // float f = rand_uniform(-0.5f, 0.5f);
    // in your initial conditions.
    std::vector<Vector3f> start;

    // add particles
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        // Add fixed point
        if (i == 0) {
            Vector3f fixedPointPos = Vector3f(-0.5, 1.0, 0.0);
            Vector3f fixedPointV = Vector3f(0.0, 0.0, 0.0);
            start.push_back(fixedPointPos);
            start.push_back(fixedPointV);

        } else {
            // any other particles
            float f = rand_uniform(-0.1f, 0.1f);
            Vector3f pos = Vector3f(-0.5 + f, 1.0 + f, f);
            Vector3f vel = Vector3f(0.0, 0.0, 0.0);
            start.push_back(pos);
            start.push_back(vel);
        }
    }
    setState(start);
}


std::vector<Vector3f> RigidSystem::evalF(std::vector<Vector3f> state)
{
    std::vector<Vector3f> f(state.size());
    // TODO 4.1: implement evalF
    //  - gravity
    //  - viscous drag
    //  - springs

    // first fixed particle doesn't move
    f[0] = Vector3f(0.0, 0.0, 0.0);
    f[1] = Vector3f(0.0, 0.0, 0.0);

    // iterate through number of particles
    for (int i=1; i<(state.size()/2); ++i) {
        Vector3f pos = state[2*i];
        Vector3f vel = state[2*i+1];

        // Gravity
        Vector3f F_g = m*g;

        // Viscous Drag
        Vector3f F_vd = -k_vd * vel;

        // net force
        Vector3f F_all = F_g + F_vd;
        Vector3f acceleration = F_all/m;

        // position -> velocity ; velocity -> acceleration
        f[2*i] = vel;
        f[2*i+1] = acceleration;
    }

    return f;
}

// render the system (ie draw the particles)
void RigidSystem::draw(GLProgram& gl)
{
    const Vector3f PENDULUM_COLOR(0.73f, 0.0f, 0.83f);
    gl.updateMaterial(PENDULUM_COLOR);

    // TODO 4.2, 4.3

    // iterate through i particles
    for (int i=0; i<getState().size()/2; ++i) {
        Vector3f pos = getPosition(i);
        gl.updateModelMatrix(Matrix4f::translation(pos));
        drawSphere(0.075f, 10, 10);
    }
}

