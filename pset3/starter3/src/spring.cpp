#include "spring.h"

Spring::Spring()
{
    // Initialize spring
}

void Spring::addParticle(int i)
{
    connectedParticles.push_back(i);
}
