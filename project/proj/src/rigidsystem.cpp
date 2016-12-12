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
const int INIT_PARTICLES= 10;        // num_particles includes fixed point
const float RADIUS = .1;
const float m = 1.0;
bool toAddParticles = false;
const float NUM_ADD = 3;

// physics constants
const Vector3f g = Vector3f(0.0, -9.8, 0.0);
const float k_vd = 1;               // viscous drag
const float restitution = .1;       // restitution constant
const float k_f = .5;               // coeff of friction

// container constants
const int WIDTH = 1;

/*TODO:
 * - Side boundaries
 * - Naive collision particles = done
 * - Kill unused particles = done
 * - Stream of particles = done
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
    std::vector<Vector3f> particles = genParticles(INIT_PARTICLES);
    setState(particles);
}


// override set state so we check for the boundaries
void RigidSystem::setState(const std::vector<Vector3f> & newState) {
    // final state array
    std::vector<Vector3f> finalState;
    for (int i=0; i<newState.size()/2; ++i) {
        Vector3f pos = newState[2*i];
        Vector3f vel = newState[2*i+1];

        // kill objects that have fallen
        if (pos.y() < -5) {
            continue;
        }

        // bottom of the container
        if (pos.y() < -WIDTH && std::abs(pos.x()) < WIDTH && std::abs(pos.z()) < WIDTH) {
            // reflect position back above and kill velocity
            pos[1] = std::max(-(float)WIDTH, pos[1]);

            //constants
            Vector3f zero = Vector3f(0,0,0);
            Vector3f normal = Vector3f(0,1,0);
            float inv_m = 1/m;
            vel = collision(vel, zero, normal, inv_m, 0.0);
        }

        // check other particles
        for (int c=0; c<newState.size()/2; ++c) {
            if (c != i) {
                Vector3f collide_pos = newState[2*c];
                Vector3f collide_vel = newState[2*c+1];

                // vector pointing to this particle
                Vector3f collision_vect = pos - collide_pos;
                Vector3f normal = collision_vect.normalized();
                float dist = collision_vect.absSquared();

                if (dist < (2*RADIUS)*(2*RADIUS)) {
                    if (dist == 0) {
                        std::cerr << "divide by zero" << std::endl;
                    } else {
                        float inv_m = 1/m;
                        vel = collision(vel, collide_vel, normal, inv_m, inv_m);
                    }
                }
            }
        }
        finalState.push_back(pos);
        finalState.push_back(vel);
    }

    // if user keypress adds particles
    if (toAddParticles) {
        for (Vector3f p : genParticles(NUM_ADD)) {
            finalState.push_back(p);
        }
        toAddParticles = false;
    }

    m_vVecState = finalState;
}

// generate particles
std::vector<Vector3f> RigidSystem::genParticles(int num) {
    std::vector<Vector3f> generatedParticles;
    for (int i = 0; i < num; ++i) {
        // random ints
        float f = rand_uniform(-0.5f, 0.5f);
        float f2 = rand_uniform(-0.5f, 0.5f);
        float f3 = rand_uniform(-0.5f, 0.5f);

        // create new particle
        Vector3f pos = Vector3f(f, 1.0 + f2, f3);
        Vector3f vel = Vector3f(0.0, 0.0, 0.0);

        generatedParticles.push_back(pos);
        generatedParticles.push_back(vel);
    }
    return generatedParticles;
}

// add particles
void RigidSystem::addParticles() {
    toAddParticles = true;
}

// find impulse on A
// Returns new velocity for A
Vector3f RigidSystem::collision(Vector3f velA, Vector3f velB, Vector3f normal, float inv_ma, float inv_mb) {
    // relative velocity
    Vector3f relVelocity = velA - velB;

    // Calculate relative velocity in terms of the normal direction
    float velAlongNormal = Vector3f::dot(relVelocity, normal);

    // Do not resolve if velocities are separating
    if (velAlongNormal > 0){
        return velA;
    }

    // Calculate impulse scalar
    float j = (1 + restitution) * velAlongNormal;
    j /= (inv_ma + inv_mb);

    // Apply impulse
    Vector3f impulse = j * normal;
    velA -= inv_ma * impulse;
    return velA;
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

        /*
        for (int c=2; c<(state.size()/2); ++c) {
            if (c != i) {
                Vector3f collide_pos = state[2*c];

                // vector pointing to this particle
                Vector3f collision_vect = pos - collide_pos;
                float dist = collision_vect.absSquared();

                // collision
                if (dist < .2f) {
                    if (dist == 0) {
                        std::cerr << "divide by zero" << std::endl;
                    } else {
                        F_collision = (k_c / (dist+.1)) * collision_vect.normalized();
                    }
            }
        }
         */

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
        // drawSphere(0.075f, 10, 10);
        drawSphere(RADIUS, 10, 10);
    }
}

