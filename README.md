# RayTracer

![ExampleRender](./examples/results/metalsphere.ppm)
A CPU RayTracer in C++ based on the [Ray Tracing in One Weekend](https://raytracing.github.io) book series. It has additional features such as scene creation from config files and a few more shapes. This project currently works only on Linux.

## Building
You'll need the libconfig++ library to build this project. On Ubuntu, you can install it with `sudo apt install libconfig++-dev`. Then, you can build the project with `make`.

## Running
You can run the project with `./raytracer [config_file].cfg > [your_filename].ppm`. You can find example config files in the `examples` folder. The output will be a PPM image file.

## Features

### Shapes
- Sphere
- Plane
- Cube
- Cylinder
- Cone

### Materials
- Lambertian
- Metal
- Dielectric

### Other
- Config file scene creation
- Anti-aliasing
- Depth of field
- Checker textures
- Normal textures
- Ambiant light
- Directional light
- Point light

## Some examples
![ExampleRender](./examples/results/box.ppm)
![ExampleRender](./examples/results/daylight.ppm)
![ExampleRender](./examples/results/night.ppm)