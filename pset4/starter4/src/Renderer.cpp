#include "Renderer.h"

#include "ArgParser.h"
#include "Camera.h"
#include "Image.h"
#include "Ray.h"
#include "VecUtils.h"

#include <limits>


Renderer::Renderer(const ArgParser &args) :
    _args(args),
    _scene(args.input_file)
{
}

void
Renderer::Render()
{
    int w = _args.width;
    int h = _args.height;

    Image image(w, h);
    Image nimage(w, h);
    Image dimage(w, h);

    // loop through all the pixels in the image
    // generate all the samples

    // This look generates camera rays and callse traceRay.
    // It also write to the color, normal, and depth images.
    // You should understand what this code does.
    Camera* cam = _scene.getCamera();
    for (int y = 0; y < h; ++y) {
        float ndcy = 2 * (y / (h - 1.0f)) - 1.0f;
        for (int x = 0; x < w; ++x) {
            float ndcx = 2 * (x / (w - 1.0f)) - 1.0f;
            // Use PerspectiveCamera to generate a ray.
            // You should understand what generateRay() does.
            Ray r = cam->generateRay(Vector2f(ndcx, ndcy));

            Hit h;
            Vector3f color = traceRay(r, cam->getTMin(), _args.bounces, h);

            image.setPixel(x, y, color);
            nimage.setPixel(x, y, (h.getNormal() + 1.0f) / 2.0f);
            float range = (_args.depth_max - _args.depth_min);
            if (range) {
                dimage.setPixel(x, y, Vector3f((h.t - _args.depth_min) / range));
            }
        }
    }
    // END SOLN

    // save the files 
    if (_args.output_file.size()) {
        image.savePNG(_args.output_file);
    }
    if (_args.depth_file.size()) {
        dimage.savePNG(_args.depth_file);
    }
    if (_args.normals_file.size()) {
        nimage.savePNG(_args.normals_file);
    }
}



Vector3f
Renderer::traceRay(const Ray &r,
    float tmin,
    int bounces,
    Hit &h) const
{
    // The starter code only implements basic drawing of sphere primitives.
    // You will implement phong shading, recursive ray tracing, and shadow rays.

    // TODO: IMPLEMENT
    if (_scene.getGroup()->intersect(r, tmin, h)) {

        // ambient illumination
        Vector3f I_ambient = _scene.getAmbientLight() * h.getMaterial()->getDiffuseColor();
        Vector3f I_final = I_ambient;
        int numLights = _scene.getNumLights();
        Vector3f point = r.pointAtParameter(h.getT());

        for (int i=0; i< numLights; ++i) {
            Light* light = _scene.getLight(i);

            // to be updated parameters
            Vector3f toLight;
            Vector3f intensity;
            float distToLight;

            // get I_diffuse and I_specular
            light->getIllumination(point, toLight, intensity, distToLight); // this updates all the parameters before

            // Shading
            Vector3f ray_dir = toLight.normalized();
            Vector3f ray_origin = point;
            Ray rayShade(ray_origin, ray_dir);
            Hit hitShade = Hit();

            // trace ray to light source
            traceRay(rayShade, h.getT(), 0, hitShade); // update hitShade
            Vector3f intersect = rayShade.pointAtParameter(hitShade.getT());
            Vector3f shade = Vector3f(0.0, 0.0, 0.0);
//            std::cout << "shade: " << hitShade.getT() << std::endl;


            // intersection before light
//            std::cout << "intersection length: " << (intersect-ray_origin).abs() << std::endl;
            if ((intersect-ray_origin).abs() < distToLight) {
                std::cout << "intersection! " << std::endl;
                shade = h.getMaterial() -> shade(r, h, toLight, intensity);
            }
//            Vector3f shade = h.getMaterial() -> shade(r, h, toLight, intensity);
            I_final = I_final + shade;
        }

        // bounces
        if (bounces > 0) {
            // recursive trace ray
            float rDotN = Vector3f::dot(-r.getDirection(), h.getNormal().normalized());
            Vector3f r_dir = (r.getDirection() + 2 * (rDotN) * h.getNormal()).normalized();
            Vector3f r_origin = point + .01*r_dir;
            Ray rayBounce(r_origin, r_dir);
            Hit newHit = Hit();

            // find indirect illumination
//            Vector3f I_recurse = traceRay(rayBounce, h.getT(), bounces-1, newHit);
            Vector3f I_recurse = traceRay(rayBounce, 0.0, bounces-1, newHit);
            I_final = I_final + h.getMaterial()->getSpecularColor() * I_recurse;
        }
        return I_final;

    } else {
        return _scene.getBackgroundColor(r.getDirection());
    };
}

