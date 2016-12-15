#include "rigidsystem.h"
#include "particle.h"

#include <cassert>
#include <algorithm>
#include <math.h>
#include "camera.h"
#include "vertexrecorder.h"

#include <iostream>
#include <string>

// particle constants
const int INIT_PARTICLES= 10;        // num_particles includes fixed point
const float RADIUS = .2;
const float m = 5.0;
bool toAddParticles = false;
const float NUM_ADD = 3;

// physics constants
//const Vector3f g = Vector3f(0.0, -9.8, 0.0);
const Vector3f g = Vector3f(0.0, -4.9, 0.0);
const float k_vd = 2;               // viscous drag
const float restitution = 0.1;       // restitution constant
const float k_f = 1;               // coeff of friction

// container constants
const int BOTTOM = -1;
const int WIDTH = 1;
const int voxels = (2*WIDTH)/(2*RADIUS);
const float voxel_width = 2*RADIUS;

/*TODO:
 * - Side boundaries = done
 * - Naive collision particles = done
 * - Kill unused particles = done
 * - Stream of particles = done
 * - Friction = done
 * - Grid data structure
 * - Rigid body
 * - Rotational motion
 * - Textures
 */

// approximation function
bool approx(float a, float b) {
    if (std::abs(a-b) < 0.1) {
        return true;
    } else {
        return false;
    }
}

// grid optimization
//int grid[voxels][voxels][voxels] = {-1};

// get voxel location of particle position
std::vector<int> getVoxel(Vector3f pos) {
    std::vector<int> voxel;
    voxel.push_back(floor(pos.x()+.01 + WIDTH)/voxel_width);
    voxel.push_back(floor(pos.y()+.01 - BOTTOM)/voxel_width);
    voxel.push_back(floor(pos.z()+.01 + WIDTH)/voxel_width);
    return voxel;
}

RigidSystem::RigidSystem()
{
    /*
     * particles no overlapping initially
     * controllable stream
     */
    // float f = rand_uniform(-0.5f, 0.5f);

    // Create initial particles
    std::vector<Vector3f> particles = genParticles(INIT_PARTICLES);
    setState(particles);
}

// Calculate new velocity and position when colliding with boundaries
void RigidSystem::boundaryCollisions(Vector3f& vel, Vector3f& pos) {
    Vector3f zero = Vector3f(0,0,0);
    float inv_m = 1/m;

    // bottom of the container
    //if (pos.y() < -WIDTH && std::abs(pos.x()) < WIDTH && std::abs(pos.z()) < WIDTH) {
    if (pos.y() < BOTTOM) {
        // reflect position back above and kill velocity
        pos[1] = std::max(-(float)WIDTH, pos[1]);
        Vector3f normal = Vector3f(0,1,0);
        vel = collision(vel, zero, normal, inv_m, 0.0);
    }

    // left wall
    if (pos.x() < -WIDTH) {
        pos[0] = -WIDTH;
        Vector3f normal = Vector3f(1, 0, 0);
        vel = collision(vel, zero, normal, inv_m, 0.0);
    }

    // right wall
    if (pos.x() > WIDTH) {
        pos[0] = WIDTH;
        Vector3f normal = Vector3f(-1, 0, 0);
        vel = collision(vel, zero, normal, inv_m, 0.0);
    }

    // front wall
    if (pos.z() > WIDTH) {
        pos[2] = WIDTH;
        Vector3f normal = Vector3f(0, 0, -1);
        vel = collision(vel, zero, normal, inv_m, 0.0);
    }

    // back wall
    if (pos.z() < -WIDTH) {
        pos[2] = -WIDTH;
        Vector3f normal = Vector3f(0, 0, 1);
        vel = collision(vel, zero, normal, inv_m, 0.0);
    }
}

std::vector<std::vector<int>> getCollisionParticles(Vector3f pos) {
    std::vector<std::vector<int>> check;
    std::vector<int> vox = getVoxel(pos);

    for (int x=std::max(0, vox[0]); x < std::min(voxels, vox[0]+2); ++x) {
        for (int y=std::max(0, vox[1]); y < std::min(voxels, vox[1]+2); ++y) {
            for (int z=std::max(0, vox[2]); z < std::min(voxels, vox[2]+2); ++z) {
                if (x!=vox[0] || y!=vox[1] || z!=vox[2]) {
                    std::vector<int> current;
                    current.push_back(x);
                    current.push_back(y);
                    current.push_back(z);
                    check.push_back(current);
                }
            }
        }

    }

    return check;
}


// override set state so we check for the boundaries
void RigidSystem::setState(const std::vector<Vector3f> & newState) {
    // final state array
    std::vector<Vector3f> finalState;

    // add particles to my grid for faster collision lookup
    // initialize grid
    // int grid[voxels][voxels][voxels] = {-1};

    /*
    for (int i=0; i<newState.size()/2; ++i) {
        Vector3f pos = newState[2*i];

        // add particle to grid
        std::vector<int> vox = getVoxel(pos);
        grid[vox[0]][vox[1]][vox[2]] = i;
        //std::cout << vox[0] << ", " << vox[1] << ", " << vox[2] << std::endl;
    }*/

    // actually attempt to set state
    // boundaries + collisions
    for (int i=0; i<newState.size()/2; ++i) {
        Vector3f pos = newState[2*i];
        Vector3f vel = newState[2*i+1];

        // kill objects that have fallen
        if (pos.y() < -5) {
            continue;
        }

        // calculate boundary collisions
        boundaryCollisions(vel, pos);

        std::vector<int> particleIndices;
        // all particles to check for this particular position
        /*
        std::vector<std::vector<int>> check = getCollisionParticles(pos);
        for (std::vector<int> c : check) {
            int particle = grid[c[0]][c[1]][c[2]];
            if (particle != -1) {
                particleIndices.push_back(particle);
            }
        }*/

        // check other particles
        //for (int c=0; c<newState.size()/2; ++c) {
        //make sure that there are any adjacent particles
        /*
        if (particleIndices.size() > 0) {
            for (int c : particleIndices) {
                if (c != i) {
                    Vector3f collide_pos = newState[2 * c];
                    Vector3f collide_vel = newState[2 * c + 1];

                    // vector pointing to this particle
                    Vector3f collision_vect = pos - collide_pos;
                    Vector3f normal = collision_vect.normalized();
                    float dist = collision_vect.absSquared();

                    if (dist < (2 * RADIUS) * (2 * RADIUS)) {
                        if (dist == 0) {
                            std::cerr << "divide by zero" << std::endl;
                        } else {
                            float inv_m = 1 / m;

                            //pos += collision_vect/4;
                            vel = collision(vel, collide_vel, normal, inv_m, inv_m);
                        }
                    }
                }
            }
        }*/
        Vector3f finalVel = Vector3f(0,0,0);
        for (int c=0; c<newState.size()/2; ++c) {
            if (c != i) {
                Vector3f collide_pos = newState[2 * c];
                Vector3f collide_vel = newState[2 * c + 1];

                // vector pointing to this particle
                Vector3f collision_vect = pos - collide_pos;
                Vector3f normal = collision_vect.normalized();
                float dist = collision_vect.absSquared();

                if (dist < (2 * RADIUS) * (2 * RADIUS)) {
                    if (dist == 0) {
                        std::cerr << "divide by zero" << std::endl;
                    } else {
                        float inv_m = 1 / m;

                        //pos += collision_vect/4;
                        vel = collision(vel, collide_vel, normal, inv_m, inv_m);
                        //finalVel += collision(vel, collide_vel, normal, inv_m, inv_m);
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
// make sure they don't overlapp
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
    //  - Friction

    // iterate through number of particles
    for (int i=0; i<(state.size()/2); ++i) {
        Vector3f pos = state[2*i];
        Vector3f vel = state[2*i+1];

        // Gravity
        Vector3f F_g = m*g;

        // Viscous Drag
        Vector3f F_vd = -k_vd * vel;

        // G + VG
        Vector3f tot = F_g + F_vd;

        // Friction
        Vector3f F_f;
        // only apply friction when on the ground
        if (approx(vel.y(), -0.0887) && approx(pos.y(), BOTTOM)) {
            // calculate direction of friction
            float f_normal = m * g.abs();
            Vector3f F_dir = Vector3f(vel.xz().x(), 0.0, vel.xz().y());
            Vector3f F_uncapped = -k_f * f_normal * F_dir.normalized();

            if (F_dir.abs() == 0) {
                F_f = Vector3f(0,0,0);
            } else {
                F_f = F_uncapped;
            }
        }

        // F_collisions
        Vector3f F_c = Vector3f(0,0,0);
        for (int c=0; c<(state.size()/2); ++c) {
            if (c != i) {
                Vector3f collide_pos = state[2*c];

                // vector pointing to this particle
                Vector3f collision_vect = pos - collide_pos;
                float dist = collision_vect.absSquared();

                // collision
                if (dist < (2*RADIUS)*(2*RADIUS)) {
                    if (dist == 0) {
                        std::cerr << "divide by zero" << std::endl;
                    } else {
                        //F_c = collision_vect.normalized() * 50;
                        F_c += collision_vect.normalized()*10/dist;
                    }
                }
            }
        }

        // net force
        Vector3f F_all = F_g + F_vd + F_f + F_c;
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
    std::vector<Vector3f> COLORS;
    // create color bank
    const Vector3f PARTICLE_COLOR(0.73f, 0.0f, 0.83f);
    const Vector3f PARTICLE_COLOR1(0.0f, 0.73f, 0.83f);
    const Vector3f PARTICLE_COLOR2(0.73f, 0.73f, 0.0f);
    const Vector3f PARTICLE_COLOR3(0.23f, 0.73f, 0.23f);
    const Vector3f PARTICLE_COLOR4(0.73f, 0.23f, 0.23f);
    COLORS.push_back(PARTICLE_COLOR);
    COLORS.push_back(PARTICLE_COLOR1);
    COLORS.push_back(PARTICLE_COLOR2);
    COLORS.push_back(PARTICLE_COLOR3);
    COLORS.push_back(PARTICLE_COLOR4);

    // iterate through i particles
    for (int i=0; i<getState().size()/2; ++i) {

        gl.updateMaterial(COLORS[i%5]);

        Vector3f pos = getPosition(i);
        gl.updateModelMatrix(Matrix4f::translation(pos));
        // drawSphere(0.075f, 10, 10);
        drawSphere(RADIUS, 10, 10);
    }
}

