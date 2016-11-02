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

    // This look generates camera rays and calls traceRay.
    // It also write to the color, normal, and depth images.
    // You should understand what this code does.
    Camera* cam = _scene.getCamera();
    for (int y = 0; y < h; ++y) {
        float ndcy = 2 * (y / (h - 1.0f)) - 1.0f;
        for (int x = 0; x < w; ++x) {
            float ndcx = 2 * (x / (w - 1.0f)) - 1.0f;

            // Use PerspectiveCamera to generate a ray.
            // You should understand what generateRay() does.
            std::default_random_engine generator;
            std::normal_distribution<double> distribution(0.0, 1.0/w);
            std::normal_distribution<double> distribution_h(0.0, 1.0/h);
            std::vector<Ray> rays;
            Hit h;

            if (_args.jitter) {
                // 3 different jittered rays
                for (int i=0; i<3; ++i) {
                    double w_j = distribution(generator);
                    double h_j = distribution_h(generator);
                    rays.push_back(cam->generateRay(Vector2f(ndcx+w_j, ndcy+h_j)));
                }

                // want to supersample with 3 rays
                Hit h1;
                Vector3f color = traceRay(rays[0], cam->getTMin(), _args.bounces, h1);

                Hit h2;
                Vector3f color2 = traceRay(rays[1], cam->getTMin(), _args.bounces, h2);

                Hit h3;
                Vector3f color3 = traceRay(rays[2], cam->getTMin(), _args.bounces, h3);

                Vector3f ave_color = (color + color2 + color3)/3;
                Vector3f ave_normal = (h.getNormal() + h2.getNormal() + h3.getNormal())/3;
                ave_normal = ave_normal.normalized();

                image.setPixel(x, y, ave_color);
                nimage.setPixel(x, y, (ave_normal + 1.0f) / 2.0f);

                float range = (_args.depth_max - _args.depth_min);
                if (range) {
                    dimage.setPixel(x, y, Vector3f((h1.t - _args.depth_min) / range));
                }
            } else {
                Ray ray = cam->generateRay(Vector2f(ndcx, ndcy));
                Vector3f color = traceRay(ray, cam->getTMin(), _args.bounces, h);

                image.setPixel(x, y, color);
                nimage.setPixel(x, y, (h.getNormal() + 1.0f) / 2.0f);

                float range = (_args.depth_max - _args.depth_min);
                if (range) {
                    dimage.setPixel(x, y, Vector3f((h.t - _args.depth_min) / range));
                }
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
            Vector3f shade = Vector3f(0.0, 0.0, 0.0);

            // if shadows flag
            if (_args.shadows) {
                // Shading
                Vector3f ray_dir = toLight.normalized();
                Vector3f ray_origin = point + 0.01*ray_dir;
                Ray rayShade(ray_origin, ray_dir);
                Hit hitShade = Hit();

                // trace ray to light source
                traceRay(rayShade, 0, 0, hitShade); // update hitShade
                Vector3f intersect = rayShade.pointAtParameter(hitShade.getT());

                if (hitShade.getT() < std::numeric_limits<float>::max() && (intersect - ray_origin).abs() < distToLight) {
                    shade = Vector3f(0.0, 0.0, 0.0);
                } else {
                    shade = h.getMaterial() -> shade(r, h, toLight, intensity);
                }

            } else {
                shade = h.getMaterial() -> shade(r, h, toLight, intensity);
            }

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
            Vector3f I_recurse = traceRay(rayBounce, 0.0, bounces-1, newHit);
            I_final = I_final + h.getMaterial()->getSpecularColor() * I_recurse;
        }
        return I_final;

    } else {
        return _scene.getBackgroundColor(r.getDirection());
    };
}

