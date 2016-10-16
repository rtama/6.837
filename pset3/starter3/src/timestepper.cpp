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
    vector<Vector3f> state = particleSystem -> getState();
    int size = state.size();
    vector<Vector3f> deriv1 = particleSystem -> evalF(state);
    vector<Vector3f> state2(state.size());

    // calculate state using deriv1
    for (int i=0; i < size; ++i) {
        state2[i] = state[i] + stepSize/2.0*deriv1[i];
    }
    vector<Vector3f> deriv2 = particleSystem -> evalF(state2);
    vector<Vector3f> state3(state.size());

    // calculate state3 using deriv2
    for (int i=0; i < size; ++i) {
        state3[i] = state[i] + stepSize/2.0*deriv2[i];
    }
    vector<Vector3f> deriv3 = particleSystem -> evalF(state3);
    vector<Vector3f> state4(state.size());

    // calculate state4 using deriv3
    for (int i=0; i < size; ++i) {
        state4[i] = state[i] + stepSize*deriv3[i];
    }
    vector<Vector3f> deriv4 = particleSystem -> evalF(state4);
    vector<Vector3f> RK4State(size);

    // calculate next state for RK4 integrator
    for (int i=0; i < size; ++i) {
        RK4State[i] = state[i] + stepSize/6.0 * (deriv1[i] + 2.0*deriv2[i] + 2.0*deriv3[i] + deriv4[i]);
    }

    particleSystem -> setState(RK4State);
}

