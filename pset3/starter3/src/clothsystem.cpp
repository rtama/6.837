#include "clothsystem.h"
#include "camera.h"
#include "vertexrecorder.h"

#include <iostream>
#include <math.h>

using namespace std;

 // your system should at least contain 8x8 particles.
const int N = 8;

const bool showSprings = true;
const int W = N;
const int H = N;
const float m = .01;
const Vector3f g = Vector3f(0.0, -9.8, 0.0);
const float k_vd = .10;
const float k_s = 10.0;
const float restLength = 2.0/W;

ClothSystem::ClothSystem()
{
    // TODO 5. Initialize m_vVecState with cloth particles. 
    // You can again use rand_uniform(lo, hi) to make things a bit more interesting

    // set springs size
    int totParticles = W * H;
    springs.resize(totParticles);

    float wEach = 2.0f/W;
    float hEach = 2.0f/H;
    vector<Vector3f> start;
    Vector3f topLeft = Vector3f(1.0, 1.0, 0.0);

    // add particles to start
    for (int i=0; i < totParticles; ++i) {
        int column = i % W;
        int row = i / H;
        float f = rand_uniform(-0.1f, 0.1f);

        Vector3f toAdd = Vector3f(wEach * column, hEach * -row, f);
        Vector3f particle = topLeft + toAdd;

        // add pos and vel to start vector
        start.push_back(particle);
        start.push_back(Vector3f(0.0, 0.0, 0.0)); // velocity

        // structural springs
        Spring structuralSpring = Spring();
        addStructuralSprings(structuralSpring, row, column, i);

        // shear springs
        Spring shearSpring = Spring();
        addShearSprings(shearSpring, row, column, i);

        // flex springs
        Spring flexSpring = Spring();
        addFlexSprings(flexSpring, row, column, i);

    }
    setState(start);
}

void ClothSystem::addStructuralSprings(Spring& spring, int row, int column, int i) {
    if (column > 0) {
        int index = indexOf(row, column-1, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength);
            springs[index].addParticle(i); // Make sure added particle also adds this particle
            springs[index].setRestLength(restLength);
        }
    }
    if (column < W-1) {
        int index = indexOf(row, column+1, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength);
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength);
        }
    }
    if (row > 0) {
        int index = indexOf(row-1, column, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength);
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength);
        }
    }
    if (row < H-1) {
        int index = indexOf(row+1, column, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength);
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength);
        }
    }
    springs.push_back(spring);
}

// add shear springs for particle i (row, col)
void ClothSystem::addShearSprings(Spring& spring, int row, int column, int i) {
    if (column > 0 && row > 0) {
        int index = indexOf(row-1, column-1, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength*sqrt(2.0)); // Added particle also adds this particle
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength*sqrt(2.0));
        }

    }
    if (column < W-1 && row > 0) {
        int index = indexOf(row-1, column+1, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength*sqrt(2.0));
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength*sqrt(2.0));
        }
    }
    if (column > 0 && row < H-1) {
        int index = indexOf(row+1, column-1, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength*sqrt(2.0));
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength*sqrt(2.0));
        }

    }
    if (column < W-1 && row < H-1) {
        int index = indexOf(row+1, column+1, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength*sqrt(2.0));
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength*sqrt(2.0));
        }
    }
}

void ClothSystem::addFlexSprings(Spring& spring, int row, int column, int i) {
    if (column > 1) {
        int index = indexOf(row, column-2, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength*2.0); // Added particle also adds this particle
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength*2.0);
        }
    }
    if (column < W-2) {
        int index = indexOf(row, column+2, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength*2.0);
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength*2.0);
        }
    }
    if (row < H-2) {
        int index = indexOf(row+2, column, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength*2.0);
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength*2.0);
        }

    }
    if (row > 1) {
        int index = indexOf(row-2, column, N);
        if (!spring.checkParticle(index)) {
            spring.addParticle(index);
            spring.setRestLength(restLength*2.0);
            springs[index].addParticle(i);
            springs[index].setRestLength(restLength*2.0);
        }
    }
}

std::vector<Vector3f> ClothSystem::evalF(std::vector<Vector3f> state)
{
    std::vector<Vector3f> f(state.size());
    // TODO 5. implement evalF
    // - gravity
    // - viscous drag
    // - structural springs
    // - shear springs
    // - flexion springs
    // first fixed particle doesn't move

    // iterate through number of particles
    for (int i=1; i<(state.size()/2); ++i) {
        Vector3f pos = state[2*i];
        Vector3f vel = state[2*i+1];

        // Gravity
        Vector3f F_g = m*g;

        // Viscous Drag
        Vector3f F_vd = -k_vd * vel;

        // Springs
        std::vector<int> particles = springs[i].getConnectedParticles();
        Vector3f F_s = Vector3f(0.0, 0.0, 0.0);
        for (int j = 0; j < particles.size(); ++j) {
            float restL = springs[i].getRestLength(j);
            Vector3f dir = pos - state[2*particles[j]];
            Vector3f unitDir = dir.normalized();
            Vector3f f = -k_s * (dir.abs() - restL) * unitDir;
            F_s = F_s + f;
        }

        // net force
        Vector3f F_all = F_g + F_vd + F_s;
        Vector3f acceleration = F_all/m;

        // position -> velocity ; velocity -> acceleration
        if (i == 0 || i == W-1) {
            f[2*i] = Vector3f(0.0, 0.0, 0.0);
            f[2*i+1] = Vector3f(0.0, 0.0, 0.0);
        } else {
            f[2*i] = vel;
            f[2*i+1] = acceleration;
        }

    }

    return f;
}


// index of particle at position, (i,j) for an nxn cloth
// 0 indexed, top left = (0,0)
int ClothSystem::indexOf(int i, int j, int n) {
    return i * n + j;
}


void ClothSystem::draw(GLProgram& gl)
{
    //TODO 5: render the system 
    //         - ie draw the particles as little spheres
    //         - or draw the springs as little lines or cylinders
    //         - or draw wireframe mesh

    const Vector3f CLOTH_COLOR(0.9f, 0.9f, 0.9f);
    gl.updateMaterial(CLOTH_COLOR);

    for (int i=0; i<getState().size()/2; ++i) {
        gl.updateModelMatrix(Matrix4f::translation(getPosition(i)));
//        drawSphere(0.04f, 8, 8);
    }

    // EXAMPLE for how to render cloth particles.
    //  - you should replace this code.
    /*
    float w = 0.2f;
    Vector3f O(0.4f, 1, 0);
    gl.updateModelMatrix(Matrix4f::translation(O));
    drawSphere(0.04f, 8, 8);
    gl.updateModelMatrix(Matrix4f::translation(O + Vector3f(w, 0, 0)));
    drawSphere(0.04f, 8, 8);
    gl.updateModelMatrix(Matrix4f::translation(O + Vector3f(w, -w, 0)));
    drawSphere(0.04f, 8, 8);
    gl.updateModelMatrix(Matrix4f::translation(O + Vector3f(0, -w, 0)));
    drawSphere(0.04f, 8, 8);
    */

    if (showSprings) {
        gl.disableLighting();
        gl.updateModelMatrix(Matrix4f::identity());
        VertexRecorder rec;

        // iterate through each particle in mesh
        for (int i=0; i<getState().size()/2; ++i) {
            Vector3f currParticle = getPosition(i);
            Spring spring = springs[i];
            vector<int> particles = spring.getConnectedParticles();
            for (int j=0; j<particles.size(); ++j) {
                int index = particles[j];
                Vector3f attachedParticle = getPosition(index);
                Vector3f diff = attachedParticle-currParticle;
                rec.record(currParticle, CLOTH_COLOR);
                rec.record(currParticle + diff, CLOTH_COLOR);
            }
        }
        glLineWidth(3.0f);
        rec.draw(GL_LINES);
    }
    gl.enableLighting();


    // EXAMPLE: This shows you how to render lines to debug the spring system.
    //
    //          You should replace this code.
    //
    //          Since lines don't have a clearly defined normal, we can't use
    //          a regular lighting model.
    //          GLprogram has a "color only" mode, where illumination
    //          is disabled, and you specify color directly as vertex attribute.
    //          Note: enableLighting/disableLighting invalidates uniforms,
    //          so you'll have to update the transformation/material parameters
    //          after a mode change.
    /*
    gl.disableLighting();
    gl.updateModelMatrix(Matrix4f::identity()); // update uniforms after mode change
    VertexRecorder rec;
    rec.record(O, CLOTH_COLOR);
    rec.record(O + Vector3f(w, 0, 0), CLOTH_COLOR);
    rec.record(O, CLOTH_COLOR);
    rec.record(O + Vector3f(0, -w, 0), CLOTH_COLOR);

    rec.record(O + Vector3f(w, 0, 0), CLOTH_COLOR);
    rec.record(O + Vector3f(w, -w, 0), CLOTH_COLOR);

    rec.record(O + Vector3f(0, -w, 0), CLOTH_COLOR);
    rec.record(O + Vector3f(w, -w, 0), CLOTH_COLOR);
    glLineWidth(3.0f);
    rec.draw(GL_LINES);

    gl.enableLighting(); // reset to default lighting model
    // EXAMPLE END
     */
}

