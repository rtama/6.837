#include "skeletalmodel.h"
#include <cassert>

#include "starter2_util.h"
#include "vertexrecorder.h"

using namespace std;

SkeletalModel::SkeletalModel() {
    program = compileProgram(c_vertexshader, c_fragmentshader_light);
    if (!program) {
        printf("Cannot compile program\n");
        assert(false);
    }
}

SkeletalModel::~SkeletalModel() {
    // destructor will release memory when SkeletalModel is deleted
    while (m_joints.size()) {
        delete m_joints.back();
        m_joints.pop_back();
    }

    glDeleteProgram(program);
}

void SkeletalModel::load(const char *skeletonFile, const char *meshFile, const char *attachmentsFile)
{
    loadSkeleton(skeletonFile);

    m_mesh.load(meshFile);
    m_mesh.loadAttachments(attachmentsFile, (int)m_joints.size());

    computeBindWorldToJointTransforms();
    updateCurrentJointToWorldTransforms();
}

void SkeletalModel::draw(const Camera& camera, bool skeletonVisible)
{
    // draw() gets called whenever a redraw is required
    // (after an update() occurs, when the camera moves, the window is resized, etc)

    m_matrixStack.clear();

    glUseProgram(program);
    updateShadingUniforms();
    if (skeletonVisible)
    {
        drawJoints(camera);
        drawSkeleton(camera);
    }
    else
    {
        // Tell the mesh to draw itself.
        // Since we transform mesh vertices on the CPU,
        // There is no need to set a Model matrix as uniform
        camera.SetUniforms(program, Matrix4f::identity());
        m_mesh.draw();
    }
    glUseProgram(0);
}

void SkeletalModel::updateShadingUniforms() {
    // UPDATE MATERIAL UNIFORMS
    GLfloat diffColor[] = { 0.4f, 0.4f, 0.4f, 1 };
    GLfloat specColor[] = { 0.9f, 0.9f, 0.9f, 1 };
    GLfloat shininess[] = { 50.0f };
    int loc = glGetUniformLocation(program, "diffColor");
    glUniform4fv(loc, 1, diffColor);
    loc = glGetUniformLocation(program, "specColor");
    glUniform4fv(loc, 1, specColor);
    loc = glGetUniformLocation(program, "shininess");
    glUniform1f(loc, shininess[0]);

    // UPDATE LIGHT UNIFORMS
    GLfloat lightPos[] = { 3.0f, 3.0f, 5.0f, 1.0f };
    loc = glGetUniformLocation(program, "lightPos");
    glUniform4fv(loc, 1, lightPos);

    GLfloat lightDiff[] = { 120.0f, 120.0f, 120.0f, 1.0f };
    loc = glGetUniformLocation(program, "lightDiff");
    glUniform4fv(loc, 1, lightDiff);
}

void SkeletalModel::loadSkeleton(const char* filename) {
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        // read file line by line
        std::istringstream ss(line);
        Vector3f pos;
        int parent;
        ss >> pos[0] >> pos[1] >> pos[2] >> parent;

        // create joint and add to lists
        Joint *joint = new Joint;
        joint -> transform = Matrix4f::translation(pos[0], pos[1], pos[2]);
        if (parent == -1) {
            m_rootJoint = joint;
        } else {
            m_joints[parent] -> children.push_back(joint);
        }
        m_joints.push_back(joint);
    }

}

void SkeletalModel::drawJoints(const Camera& camera)
{
    // Draw a sphere at each joint. You will need to add a recursive
    // helper function to traverse the joint hierarchy.
    //
    // We recommend using drawSphere( 0.025f, 12, 12 )
    // to draw a sphere of reasonable size.
    //
    // You should use your MatrixStack class. A function
    // should push it's changes onto the stack, and
    // use stack.pop() to revert the stack to the original
    // state.

    // this is just for illustration:

    // translate from top of stack, but doesn't push, since that's not
    // implemented yet.
//    Matrix4f M = m_matrixStack.top() * Matrix4f::translation(+0.5f, +0.5f, -0.5f);
    // update transformation uniforms
//    camera.SetUniforms(program, M);
    // draw
//    drawSphere(0.025f, 12, 12);
    // didn't push to stack, so no pop() needed
    m_matrixStack.clear();
    drawJoint(camera, m_rootJoint, &m_matrixStack);
}

// recursive helper function
void SkeletalModel::drawJoint(const Camera& camera, Joint* joint, MatrixStack* stack)
{
    stack -> push(joint -> transform);
    Matrix4f topMatrix = stack -> top();
    camera.SetUniforms(program, topMatrix);
    drawSphere(0.025f, 12, 12);

    // recurse down to children
    for (int i=0; i < joint -> children.size(); ++i) {
        Joint *childJoint = joint -> children[i];
        drawJoint(camera, childJoint, stack);
        stack -> pop();
    }
}

void SkeletalModel::drawSkeleton(const Camera& camera)
{
    // Draw cylinders between the joints. You will need to add a recursive 
    // helper function to traverse the joint hierarchy.
    //
    // We recommend using drawCylinder(6, 0.02f, <height>);
    // to draw a cylinder of reasonable diameter.

    // you can use the stack with push/pop like this
    // m_matrixStack.push(Matrix4f::translation(+0.6f, +0.5f, -0.5f))
    // camera.SetUniforms(program, m_matrixStack.top());
    // drawCylinder(6, 0.02f, 0.2f);
    // callChildFunction();
    // m_matrixStack.pop();
    m_matrixStack.clear();
    drawRecurseSkeleton(camera, m_rootJoint, &m_matrixStack);
}
/*
void SkeletalModel::drawRecurseSkeleton(const Camera& camera, Joint* joint, MatrixStack* stack) {
    if (joint == m_rootJoint) {
        stack -> push(joint -> transform);
    }

    for (int i=0; i < joint -> children.size(); ++i) {
        Joint *childJoint = joint -> children[i];
        Matrix4f beforeMatrix = stack->top();
        stack -> push(childJoint -> transform);
        Matrix4f topMatrix = stack -> top();

        // dist
//        Vector3f v1 = ((childJoint -> transform)*(joint -> transform)).getCol(3).xyz();
        Vector3f v1 = joint -> transform.getCol(3).xyz();
//        Vector3f v1 = topMatrix.getCol(3).xyz();

        Vector3f v2 = childJoint -> transform.getCol(3).xyz();
//        Vector3f v2 = (beforeMatrix * (childJoint -> transform)).getCol(3).xyz();
        Vector3f diff = -1 * v2;
//        Vector3f diff = v1 - v2;
        float dist = v2.abs();

        // rotation
        float a = (diff[0] * -1.0) / diff[2];
//        Vector3f y = (-1*v2).normalized();
        Vector3f y = diff.normalized();
        Vector3f x = Vector3f(1.0, 0.0, a).normalized();
        Vector3f z = Vector3f::cross(x, y).normalized();

        // set rotation matrix
        Matrix3f direction = Matrix3f(x, y, z, true);
        Matrix3f m = topMatrix.getSubmatrix3x3(0,0);
        topMatrix.setSubmatrix3x3(0, 0, m*direction);

        // draw
        camera.SetUniforms(program, topMatrix);
        drawCylinder(6, 0.02f, dist);
        drawRecurseSkeleton(camera, childJoint, stack);
        stack -> pop();
    }

}*/

void SkeletalModel::drawRecurseSkeleton(const Camera& camera, Joint* joint, MatrixStack* stack) {
    for (int i=0; i < joint -> children.size(); ++i) {

        stack -> push(joint -> transform);
        Joint *childJoint = joint -> children[i];
        Matrix4f topMatrix = stack -> top();

        // dist
        Vector3f v1 = joint -> transform.getCol(3).xyz();
        Vector3f v2 = childJoint -> transform.getCol(3).xyz();
        Vector3f diff = v2;
        float dist = v2.abs();

        // rotation
        float a = (diff[0] * -1.0) / diff[2];
        Vector3f y = diff.normalized();
        Vector3f x = Vector3f(1.0, 0.0, a).normalized();
        Vector3f z = Vector3f::cross(x, y).normalized();

        // set rotation matrix
        Matrix3f direction = Matrix3f(x, y, z, true);
        Matrix3f m = topMatrix.getSubmatrix3x3(0,0);
        topMatrix.setSubmatrix3x3(0, 0, m*direction);

        // draw
        camera.SetUniforms(program, topMatrix);
        drawCylinder(6, 0.02f, dist);
        drawRecurseSkeleton(camera, childJoint, stack);
        stack -> pop();
    }

}

void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
    // Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
    // [-pi, pi] range
    Matrix3f rotationX = Matrix3f(Vector3f(1, 0, 0), Vector3f(0, cos(rX), sin(rX)), Vector3f(0, -sin(rX), cos(rX)) );
    Matrix3f rotationZ = Matrix3f(Vector3f(cos(rY), 0, -sin(rY)), Vector3f(0, 1, 0), Vector3f(sin(rY), 0, cos(rY)) );
    Matrix3f rotationY = Matrix3f(Vector3f(cos(rZ), sin(rZ), 0), Vector3f(-sin(rZ), cos(rZ), 0), Vector3f(0, 0, 1) );

    Matrix3f allRotations = rotationZ * rotationY * rotationX;
    m_joints[jointIndex] -> transform.setSubmatrix3x3(0, 0, allRotations);

}

void SkeletalModel::computeBindWorldToJointTransforms()
{
    // 2.3.1. Implement this method to compute a per-joint transform from
    // world-space to joint space in the BIND POSE.
    //
    // Note that this needs to be computed only once since there is only
    // a single bind pose.
    //
    // This method should update each joint's bindWorldToJointTransform.
    // You will need to add a recursive helper function to traverse the joint hierarchy.
    m_matrixStack.clear();
    recurseBindWorldToJointTransforms(m_rootJoint, &m_matrixStack);
}

void SkeletalModel::recurseBindWorldToJointTransforms(Joint* joint, MatrixStack* stack) {
    stack -> push(joint -> transform);
    Matrix4f topMatrix = stack -> top();
    joint -> bindWorldToJointTransform = topMatrix.inverse(NULL, 0.00001f);

    for (int i=0; i < joint -> children.size(); ++i) {
        Joint *childJoint = joint -> children[i];
        recurseBindWorldToJointTransforms(childJoint, stack);
        stack -> pop();
    }
}

void SkeletalModel::updateCurrentJointToWorldTransforms()
{
    // 2.3.2. Implement this method to compute a per-joint transform from
    // joint space to world space in the CURRENT POSE.
    //
    // The current pose is defined by the rotations you've applied to the
    // joints and hence needs to be *updated* every time the joint angles change.
    //
    // This method should update each joint's currentJointToWorldTransform.
    // You will need to add a recursive helper function to traverse the joint hierarchy.
    m_matrixStack.clear();
    recurseUpdateCurrentJointToWorldTransforms(m_rootJoint, &m_matrixStack);
}

void SkeletalModel::recurseUpdateCurrentJointToWorldTransforms(Joint* joint, MatrixStack* stack) {
    stack -> push(joint -> transform);
    Matrix4f topMatrix = stack -> top();
    joint -> currentJointToWorldTransform = topMatrix;

    for (int i=0; i < joint -> children.size(); ++i) {
        Joint *childJoint = joint->children[i];
        recurseUpdateCurrentJointToWorldTransforms(childJoint, stack);
        stack->pop();
    }
}

void SkeletalModel::updateMesh()
{
    // 2.3.2. This is the core of SSD.
    // Implement this method to update the vertices of the mesh
    // given the current state of the skeleton.
    // You will need both the bind pose world --> joint transforms.
    // and the current joint --> world transforms.
    for (int i=0; i < m_mesh.bindVertices.size(); ++i) {
        Vector4f p = Vector4f(m_mesh.bindVertices[i], 1);
        std::vector< float > weights;
        std::vector< int > jointIndices;

        for (int x=0; x < m_mesh.attachments[i].size(); ++x) {
            float w = m_mesh.attachments[i][x];
            if (w > 0) {
                jointIndices.push_back(x+1);
                weights.push_back(w);
            }
        }
        Vector4f p_i = Vector4f();
        for (int m=0; m < weights.size(); ++m) {
            Matrix4f B = m_joints[jointIndices[m]]->bindWorldToJointTransform;
            Matrix4f T = m_joints[jointIndices[m]]->currentJointToWorldTransform;

            p_i = p_i + weights[m]*T*B*p;
        }
        m_mesh.currentVertices[i] = p_i.xyz();
    }
}

