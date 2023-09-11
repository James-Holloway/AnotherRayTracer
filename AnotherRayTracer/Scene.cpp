#include "Scene.h"

#define SINGLETHREADED

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

void Scene::TraceBatch(std::vector<unsigned char>* image, unsigned int offset, unsigned int batchSize)
{
    unsigned int j = 0;
    for (unsigned int i = offset; i < offset + batchSize; i++)
    {
        unsigned int x = i % width;
        unsigned int y = floor(i / width);

        if (j >= batchSize * 3)
            break;

        unsigned char red = 0, green = 0, blue = 0;

        Color color = Trace(x, y);
        color.ToBytes(red, green, blue);

        (*image)[j++] = red;
        (*image)[j++] = green;
        (*image)[j++] = blue;
    }
}

std::vector<unsigned char> Scene::TraceScene()
{
    std::vector<unsigned char> image{};

#ifdef SINGLETHREADED
    // Single threaded
    image.resize(width * height * 3);
    std::fill(image.begin(), image.end(), 0);
    TraceBatch(&image, 0, width * height);
#else
    // Multithreaded
    unsigned int threadCount = std::max<unsigned int>(1, std::thread::hardware_concurrency());
    unsigned int batchSize = (width * height) / threadCount;

    std::vector<std::thread> threads{};
    std::vector<std::vector<unsigned char>*> images;
    for (unsigned int t = 0; t < threadCount; t++)
    {
        std::vector<unsigned char>* img = new std::vector<unsigned char>();
        img->resize(batchSize * 3);
        std::fill(img->begin(), img->end(), 0);
        images.push_back(img);

        std::thread thread = std::thread(
            [=]()
            {
                TraceBatch(img, t * batchSize, batchSize);
            });
        threads.push_back(std::move(thread));
    }

    for (std::thread& thread : threads)
    {
        if (thread.joinable())
            thread.join();
    }

    for (std::vector<unsigned char>* img : images)
    {
        image.insert(image.end(), img->begin(), img->end());
        delete img;
    }
#endif

    return image;
}
