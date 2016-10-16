#ifndef SPRING_H
#define SPRING_H

#include <vector>

class Spring {

public:
    Spring();

    // add particle to connectedParticles
    void addParticle(int i);

    // get connected particles
    std::vector<int> getConnectedParticles() {return connectedParticles;};

    // set restlength
    void setRestLength(float& restLength) {m_restLength = restLength;};

    // set stiffness
    void setStiffness(float& stiffness) {m_stiffness = stiffness;};

private:
    // particles that this this particle is connected to
    std::vector<int> connectedParticles;

    // constants
    float m_restLength;
    float m_stiffness;
};

#endif