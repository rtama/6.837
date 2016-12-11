#include "rigidsystem.h"

#include <cassert>
#include <algorithm>
#include "camera.h"
#include "vertexrecorder.h"
#include "spring.h"

#include <iostream>
#include <string>

// particle constants
const int NUM_PARTICLES = 10;        // num_particles includes fixed point
const float m = .5;
const Vector3f g = Vector3f(0.0, -9.8, 0.0);
const float k_vd = 1;

/*TODO:
 * - side boundaries
 * - collision particles
 * - Friction
 * - Grid data structure
 */


// container constants
const int WIDTH = 1;

RigidSystem::RigidSystem()
{
    // To add a bit of randomness, use e.g.
    // float f = rand_uniform(-0.5f, 0.5f);
    // in your initial conditions.
    std::vector<Vector3f> start;

    // add particles

    // corners of the container
    start.push_back(Vector3f(-WIDTH, -WIDTH, -WIDTH));
    start.push_back(Vector3f(0, 0, 0));

    start.push_back(Vector3f(WIDTH, WIDTH, WIDTH));
    start.push_back(Vector3f(0, 0, 0));

    for (int i = 2; i < NUM_PARTICLES; ++i) {
        float f = rand_uniform(-0.1f, 0.1f);
        Vector3f pos = Vector3f(-0.5 + f, 1.0 + f, f);
        Vector3f vel = Vector3f(0.0, 0.0, 0.0);
        start.push_back(pos);
        start.push_back(vel);
    }
    setState(start);
}

// override set state so we check for the boundaries
void RigidSystem::setState(const std::vector<Vector3f> & newState) {
    // final state array
    std::vector<Vector3f> finalState;
    for (int i=0; i<newState.size()/2; ++i) {
        Vector3f pos = newState[2*i];
        Vector3f vel = newState[2*i+1];

        // bottom of the container
        if (pos.y() < -WIDTH) {
            float cap = 0;
            // reflect position back above and kill velocity
            pos[1] = std::max(-(float)WIDTH, pos[1]);
            vel[1] = - std::min(cap, vel[1]+1);
        }
        finalState.push_back(pos);
        finalState.push_back(vel);
    }
    m_vVecState = finalState;
}

std::vector<Vector3f> RigidSystem::evalF(std::vector<Vector3f> state)
{
    std::vector<Vector3f> f(state.size());
    //  - gravity
    //  - viscous drag
    //  - springs

    for (int i=0; i<2; ++i) {
        f[2*i] = Vector3f(0,0,0);
        f[2*i+1] = Vector3f(0,0,0);
    }

    // iterate through number of particles
    for (int i=2; i<(state.size()/2); ++i) {
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

    // iterate through i particles
    for (int i=0; i<getState().size()/2; ++i) {
        Vector3f pos = getPosition(i);
        gl.updateModelMatrix(Matrix4f::translation(pos));
        drawSphere(0.075f, 10, 10);
    }
}

