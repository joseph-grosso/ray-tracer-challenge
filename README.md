# The Ray Tracer Challenge

My own implementation of the Ray Tracer from the book [The Ray Tracer Challenge: A Test-Driven Guide to Your First 3D Renderer](http://www.raytracerchallenge.com/). While the book provided the test cases and general framework of this project, all of the code written here is created by myself.

## Usage

### Building and running end-of-chapter challenges:

* Edit the `MAIN_FILE_NAME` variable in `./CMakeLists.txt` to the name of the chapter file
* Run the command below:

```bash
 bash ./build.sh
```

### Converting PPM images to PNG

```bash
convert flight_path.ppm flight_path.png
```

## Sample Images

### Spheres with shadows

![Spheres with shadows](outputs/ch8/high_res_shadow.png "Spheres with shadows from an outside light source.")

### "Hand Puppet"

![Hand puppet](outputs/ch8/hi_res_hand_puppet.png "A 'hand puppet' made up of transformed spheres, highlighting the effect of shadows.")

### Baby's First 3D Rendering

![Simple purple ball](outputs/ch6/classic_purple_sphere.png "The first 3 dimensional object created by the renderer. The shading algorithm brings depth to the image.")

### Deformed Ball

![Deformed red ball](outputs/ch5/sheared_circle.png "A ball deformed by its shearing transformation. ")

## TODO:

- [ ] Fix the intersections file to directly be called from within the Sphere/Shape object, rather than be an external function
- [ ] Move common Shape functionality to a separate file
- [ ] Move Shape objects code into its own folder
- [ ] Move headers into a different folder than source code files
- [ ] TODO: Write a function for canvas.h that directly exports image files to .png instead of only to .ppm