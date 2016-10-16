#include "timestepper.h"
#include <iostream>

#include <cstdio>

using namespace std;
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
   //TODO: See handout 3.1
    vector<Vector3f> state = particleSystem -> getState();
    vector<Vector3f> derivative = particleSystem -> evalF(state);
    vector<Vector3f> newState(state.size());

    // calculate new state using forward euler: dX = f(X,t) * dt
    for (int i=0; i < state.size(); ++i) {
        newState[i] = state[i] + (stepSize*derivative[i]);
        Vector3f s = stepSize*derivative[i];
    }
    particleSystem -> setState(newState);
}

void Trapezoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
   //TODO: See handout 3.1
    vector<Vector3f> state = particleSystem -> getState();
    int size = state.size();
    vector<Vector3f> firstDerivative = particleSystem -> evalF(state);
    vector<Vector3f> nextState(state.size());

    // calculate state after one timestep
    for (int i = 0; i < size; ++i) {
        nextState[i] = state[i] + stepSize*firstDerivative[i];
    }

    // calculate trapezoidal state
    vector<Vector3f> nextDerivative = particleSystem -> evalF(nextState);
    vector<Vector3f> trapezoidalState(state.size());
    for (int x = 0; x < size; ++x) {
        Vector3f f_0 = firstDerivative[x];
        Vector3f f_1 = nextDerivative[x];
        trapezoidalState[x] = state[x] + (stepSize/2.0 * (f_0 + f_1));
    }

    particleSystem -> setState(trapezoidalState);
}


void RK4::takeStep(ParticleSystem* particleSystem, float stepSize)
{
   //TODO: See handout 4.4
}

