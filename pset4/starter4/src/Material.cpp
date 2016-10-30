#include "Material.h"
Vector3f Material::shade(const Ray &ray,
    const Hit &hit,
    const Vector3f &dirToLight,
    const Vector3f &lightIntensity)
{
    // TODO implement Diffuse and Specular phong terms


    // diffuse
    float diffuse = clamp(dirToLight.normalized(), hit.getNormal().normalized());
    Vector3f I_diffuse;
    for (int i=0; i<3; ++i) {
        I_diffuse = diffuse * lightIntensity * getDiffuseColor();
    }

    // specular
    // reflected eye ray
    float rDotN = Vector3f::dot(-ray.getDirection(), hit.getNormal());
    Vector3f r = ray.getDirection() +  2 * (rDotN) * hit.getNormal();

    float specular = powf(clamp(dirToLight.normalized(), r.normalized()), _shininess);
    Vector3f I_specular;
    for (int i=0; i<3; ++i) {
        I_specular = specular * lightIntensity * getSpecularColor();
    }
    return I_diffuse + I_specular;
}

float Material::clamp(Vector3f v1, Vector3f v2) {
    float dot = Vector3f::dot(v1, v2);
    return std::max(0.0f, dot);
}

