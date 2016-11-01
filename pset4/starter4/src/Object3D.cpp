#include "Object3D.h"

bool Sphere::intersect(const Ray &r, float tmin, Hit &h) const
{
    // BEGIN STARTER

    // We provide sphere intersection code for you.
    // You should model other intersection implementations after this one.

    // Locate intersection point ( 2 pts )
    const Vector3f &rayOrigin = r.getOrigin(); //Ray origin in the world coordinate
    const Vector3f &dir = r.getDirection();

    Vector3f origin = rayOrigin - _center;      //Ray origin in the sphere coordinate

    float a = dir.absSquared();
    float b = 2 * Vector3f::dot(dir, origin);
    float c = origin.absSquared() - _radius * _radius;

    // no intersection
    if (b * b - 4 * a * c < 0) {
        return false;
    }

    float d = sqrt(b * b - 4 * a * c);

    float tplus = (-b + d) / (2.0f*a);
    float tminus = (-b - d) / (2.0f*a);

    // the two intersections are at the camera back
    if ((tplus < tmin) && (tminus < tmin)) {
        return false;
    }

    float t = 10000;
    // the two intersections are at the camera front
    if (tminus > tmin) {
        t = tminus;
    }

    // one intersection at the front. one at the back 
    if ((tplus > tmin) && (tminus < tmin)) {
        t = tplus;
    }

    if (t < h.getT()) {
        Vector3f normal = r.pointAtParameter(t) - _center;
        normal = normal.normalized();
        h.set(t, this->material, normal);
        return true;
    }
    // END STARTER
    return false;
}

// Add object to group
void Group::addObject(Object3D *obj) {
    m_members.push_back(obj);
}

// Return number of objects in group
int Group::getGroupSize() const {
    return (int)m_members.size();
}

bool Group::intersect(const Ray &r, float tmin, Hit &h) const
{
    // BEGIN STARTER
    // we implemented this for you
    bool hit = false;
    for (Object3D* o : m_members) {
        if (o->intersect(r, tmin, h)) {
            hit = true;
        }
    }
    return hit;
    // END STARTER
}


Plane::Plane(const Vector3f &normal, float d, Material *m) : Object3D(m) {
    // TODO implement Plane constructor
    _normal = normal;
    _d = d;
    _material = m;
}

bool Plane::intersect(const Ray &r, float tmin, Hit &h) const
{
    // TODO implement

    // find intersection time t
    float numerator = (_d - Vector3f::dot(this->_normal, r.getOrigin())); // may need to put the negative here because of d
    float denom = Vector3f::dot(this->_normal, r.getDirection());
    float t_intersect = numerator/denom;

    // behind the camera -> front of camera
    if (t_intersect < tmin) {
        return false;
    } else {
        if (t_intersect < h.getT()) {
            h.set(t_intersect, this->_material, this->_normal);
            return true;
        }
    }

    return false;
}

bool Triangle::intersect(const Ray &r, float tmin, Hit &h) const 
{
    // TODO implement
    Vector3f a = getVertex(0);
    Vector3f b = getVertex(1);
    Vector3f c = getVertex(2);

    // Ax = B to solve for intersection
    Vector3f R_d = r.getDirection();
    Vector3f R_0 = r.getOrigin();
    Matrix3f A;
    Vector3f B(3);
    for (int i=0; i<3; ++i) {
        Vector3f A_row(a[i] - b[i], a[i] - c[i], R_d[i]);
        // set rows for A and B
        A.setRow(i, A_row);
        B[i] = a[i] - R_0[i];
    }

    // retrieve barycentric coordinates
    Vector3f x = A.inverse() * B;
    float beta = x[0];
    float gamma = x[1];
    float alpha = 1 - beta - gamma;
    float t_intersect = x[2];
    // make sure that the point is in the triangle
    bool inTriangle = beta >= 0.0 && gamma >= 0.0 && alpha >= 0.0;

    if (!inTriangle) {
        return false;
    }
    if (t_intersect < tmin) {
        return false;
    } else {
        if (t_intersect < h.getT()) {
            Vector3f normal = (alpha*getNormal(0) + beta*getNormal(1) + gamma*getNormal(2)).normalized();
            h.set(t_intersect, this -> material, normal);
            return true;
        }
    }
    return false;
}


Transform::Transform(const Matrix4f &m,
    Object3D *obj) : _object(obj) {
    // TODO implement Transform constructor
    _m = m;

}
bool Transform::intersect(const Ray &r, float tmin, Hit &h) const
{
    // TODO implement
    Vector3f origin = r.getOrigin();
    Vector3f dir = r.getDirection();

//    Vector3f origin_l = (_m.inverse().transposed() * Vector4f(origin, 0.0f)).xyz().normalized();
    Vector3f origin_l = (_m.inverse() * Vector4f(origin, 1.0f)).xyz();
    Vector3f dir_l = (_m.inverse() * Vector4f(dir, 0.0f)).xyz().normalized();

    Ray ray_l = Ray(origin_l, dir_l);

    if(_object -> intersect(ray_l, tmin, h)) {
        Vector3f normal_ws = (_m.inverse().transposed() * Vector4f(h.getNormal(), 0.0f)).xyz().normalized();
        h.set(h.getT(), h.getMaterial(), normal_ws);
        return true;
    } else {
        return false;
    }
}


