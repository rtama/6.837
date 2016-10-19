#include "spring.h"

Spring::Spring()
{
    // Initialize spring
}

void Spring::addParticle(int i)
{
    connectedParticles.push_back(i);
}

bool Spring::checkParticle(int i) {
    for (int j=0; j<connectedParticles.size(); ++j) {
        if (connectedParticles[j] == i) {
            return true;
        }
    }
    return false;
}