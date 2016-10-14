#include "matrixstack.h"
#include <vector>

MatrixStack::MatrixStack()
{
	// Initialize the matrix stack with the identity matrix.
    Matrix4f I = Matrix4f::identity();
    m_matrices.push_back(I);
}

void MatrixStack::clear()
{
	// Revert to just containing the identity matrix.
    m_matrices.resize(1);
}

Matrix4f MatrixStack::top()
{
	// Return the top of the stack
	// return Matrix4f();
    return m_matrices.back();
}

void MatrixStack::push( const Matrix4f& m )
{
	// Push m onto the stack.
	// Your stack should have OpenGL semantics:
	// the new top should be the old top multiplied by m
    Matrix4f top = m_matrices.back();
    Matrix4f new_top = top * m;
    m_matrices.push_back(new_top);

}

void MatrixStack::pop()
{
	// Remove the top element from the stack
    m_matrices.pop_back();

}
