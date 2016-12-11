#include "rigidsystem.h"
#include "particle.h"

#include <cassert>
#include <algorithm>
#include "camera.h"
#include "vertexrecorder.h"
#include "spring.h"

#include <iostream>
#include <string>

// particle constants
const int NUM_PARTICLES = 10;        // num_particles includes fixed point
const float RADIUS = .1;
const float m = .5;
const Vector3f g = Vector3f(0.0, -9.8, 0.0);
const float k_vd = 1;
const float k_c = .2;

// container constants
const int WIDTH = 1;

/*TODO:
 * - Side boundaries
 * - Naive collision particles
 * - Stream of particles
 * - Friction
 * - Grid data structure
 * - Rigid body
 * - Rotational motion
 * - Textures
 */


RigidSystem::RigidSystem()
{
    /*
     * TODO: Starting arrangement
     * particles no overlapping initially
     * controllable stream
     */

    // float f = rand_uniform(-0.5f, 0.5f);
    // in your initial conditions.
    std::vector<Vector3f> start;

    // Create initial particles
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        // random ints
        float f = rand_uniform(-0.5f, 0.5f);
        float f2 = rand_uniform(-0.5f, 0.5f);
        float f3 = rand_uniform(-0.5f, 0.5f);

        // create new particle
        Vector3f pos = Vector3f(f, 1.0 + f2, f3);
        Vector3f vel = Vector3f(2.0, 0.0, 1.0);

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
        if (pos.y() < -WIDTH && std::abs(pos.x()) < WIDTH && std::abs(pos.z()) < WIDTH) {
            float cap = 0;
            // reflect position back above and kill velocity
            pos[1] = std::max(-(float)WIDTH, pos[1]);
            vel[1] = - std::min(cap, vel[1]+1);
        }

        // check other particles
        for (int c=0; c<newState.size()/2; ++c) {
            Vector3f pos = newState[2*i];
            Vector3f vel = newState[2*i+1];
            if (c != i) {
                Vector3f collide_pos = newState[2*c];

                // vector pointing to this particle
                Vector3f collision_vect = pos - collide_pos;
                float dist = collision_vect.absSquared();

                if (dist < (RADIUS*RADIUS)) {
                    if (dist == 0) {
                        std::cerr << "divide by zero" << std::endl;
                    } else {

                    }
                }
            }


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
    //  - TODO: Friction, collisions

    // iterate through number of particles
    for (int i=0; i<(state.size()/2); ++i) {
        Vector3f pos = state[2*i];
        Vector3f vel = state[2*i+1];

        // Gravity
        Vector3f F_g = m*g;

        // Viscous Drag
        Vector3f F_vd = -k_vd * vel;

        // collisions Naive
        Vector3f F_collision;

        for (int c=2; c<(state.size()/2); ++c) {
            if (c != i) {
                Vector3f collide_pos = state[2*c];

                // vector pointing to this particle
                Vector3f collision_vect = pos - collide_pos;
                float dist = collision_vect.absSquared();

                /*
                // collision
                if (dist < .2f) {
                    if (dist == 0) {
                        std::cerr << "divide by zero" << std::endl;
                    } else {
                        F_collision = (k_c / (dist+.1)) * collision_vect.normalized();
                    }
                }*/
            }
        }

        // net force
        Vector3f F_all = F_g + F_vd + F_collision;
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
        // drawSphere(0.075f, 10, 10);
        drawSphere(RADIUS, 10, 10);
    }
}

