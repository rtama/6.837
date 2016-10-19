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

    // check if particle i already connected. true = already connected
    bool checkParticle(int i);

    // set restlength
    void setRestLength(float restLength) {m_restLength.push_back(restLength);};

    // get restlength of connected particle i
    float getRestLength(int i) {return m_restLength[i];};

private:
    // particles that this this particle is connected to
    std::vector<int> connectedParticles;

    // constants
    std::vector<float> m_restLength;
    std::vector<float> m_stiffness;
};

#endif