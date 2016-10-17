#include "clothsystem.h"
#include "camera.h"
#include "vertexrecorder.h"

#include <iostream>

using namespace std;

 // your system should at least contain 8x8 particles.
//const int W = 8;
//const int H = 8;

const bool showSprings = true;
const int W = 3; // for testing
const int H = 3;
const float m = 5.0;
const Vector3f g = Vector3f(0.0, -9.8, 0.0);
const float k_vd = 7.0;
const float k_s = 150.0;
const float restLength = 0.1;

ClothSystem::ClothSystem()
{
    // TODO 5. Initialize m_vVecState with cloth particles. 
    // You can again use rand_uniform(lo, hi) to make things a bit more interesting

    int totParticles = W * H;
    float wEach = 2.0f/W;
    float hEach = 2.0f/H;
    vector<Vector3f> start;
    Vector3f topLeft = Vector3f(1.0, 1.0, 0.0);

    // add particles to start
    for (int i=0; i < totParticles; ++i) {
        int column = i % W;
        int row = i / H;
        Vector3f toAdd = Vector3f(wEach * column, hEach * -row, 0.0);
        Vector3f particle = topLeft + toAdd;

        // add pos and vel to start vector
        start.push_back(particle);
        start.push_back(Vector3f(0.0, 0.0, 0.0)); // velocity

        // structural springs
        Spring spring = Spring();
        if (column > 0) {
            int index = indexOf(row, column-1, W);
            spring.addParticle(index);
        }
        if (column < W-1) {
            int index = indexOf(row, column+1, W);
            spring.addParticle(index);
        }
        if (row > 0) {
            int index = indexOf(row-1, column, W);
            spring.addParticle(index);
        }
        if (row < H-1) {
            int index = indexOf(row+1, column, W);
            spring.addParticle(index);
        }
        springs.push_back(spring);


    }
    setState(start);
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
        drawSphere(0.04f, 8, 8);
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

