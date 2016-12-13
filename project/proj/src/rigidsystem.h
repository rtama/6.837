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
    Vector3f collision(Vector3f velA, Vector3f velB, Vector3f normal, float inv_ma, float inv_mb);

    void boundaryCollisions(Vector3f& vel, Vector3f& pos);
    // set boolean toAddParticles = true. Adds particles next time state is updated
    void addParticles();
    void setState(const std::vector<Vector3f>  & newState) override;
    void draw(GLProgram&);

    // inherits
    // std::vector<Vector3f> m_vVecState;
protected:
    std::vector<int> m_queue;

private:
    // generate particles for internal use
    std::vector<Vector3f> genParticles(int num);

};

#endif
