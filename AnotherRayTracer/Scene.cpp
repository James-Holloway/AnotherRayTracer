
#include "Scene.h"

Color Scene::Trace(unsigned int x, unsigned int y)
{
    // Remap [0,width] & [0,height] to [-1,+1]
    double u = 2 * (x / (double)width) - 1.0;
    double v = 2 * (y / (double)height) - 1.0;

    Vector3D vx = camera.right * u * camera.scale;
    Vector3D vy = camera.up.Inverted() * v * camera.scale;

    if (width > height)
    {
        double ratio = width / (double)height;
        vx = vx * ratio;
    }
    else if( height > width)
    {
        double ratio = height / (double)width;
        vy = vy * ratio;
    }

    Vector3D r = camera.forward + vx + vy;
    Ray ray = Ray(camera.position, r);

    std::map<double, std::shared_ptr<Shape>> intersections;
    for (std::shared_ptr<Shape> shape : shapes)
    {
        std::vector<double> intersects = shape->Intersects(ray);
        for (double& intersect : intersects)
        {
            intersections[intersect] = shape;
        }
    }

    if (intersections.size() == 0)
        return background;

    // Get first intersection
    auto intersected = intersections.begin();

    // TODO use a material struct
    return intersected->second->color;
}

void Scene::TraceBatch(std::vector<unsigned char>& image, unsigned int offset, unsigned int batchSize)
{
    unsigned int j = offset * 3;
    for (unsigned int i = offset; i < offset + batchSize; i++)
    {
        unsigned int x = i % width;
        unsigned int y = floor(i / width);

        unsigned char red = 0, green = 0, blue = 0;

        Color color = Trace(x, y);
        color.ToBytes(red, green, blue);

        image[j++] = red;
        image[j++] = green;
        image[j++] = blue;
    }
}

std::vector<unsigned char> Scene::TraceScene()
{
    std::vector<unsigned char> image{};
    image.resize(width * height * 3);
    std::fill(image.begin(), image.end(), 0);

    TraceBatch(image, 0, width * height);

    return image;
}
