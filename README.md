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

### Patterns

![Spheres On A Plane with Stripes](outputs/ch10/hq_stripes_and_spheres.png "Some striped spheres sit on a plane, showing the first implementation of a pattern object.")

### Spheres and Planes

![Walls with Planes](outputs/ch9/high_res_multi_wall_pic.png "A wall made of planes interacting with a deformed sphere.")

### Spheres with shadows

![Spheres with shadows](outputs/ch9/high_res_plane_pic.png "Spheres with shadows from an outside light source on an infinite plane.")

### "Hand Puppet"

![Hand puppet](outputs/ch8/hi_res_hand_puppet.png "A 'hand puppet' made up of transformed spheres, highlighting the effect of shadows.")

### Baby's First 3D Rendering

![Simple purple ball](outputs/ch6/classic_purple_sphere.png "The first 3 dimensional object created by the renderer. The shading algorithm brings depth to the image.")

### Deformed Ball

![Deformed red ball](outputs/ch5/sheared_circle.png "A ball deformed by its shearing transformation. ")

## TODO

### Chapters

- [x] ch1
- [x] ch2
- [x] ch3
- [x] ch4
- [x] ch5
- [x] ch6
- [x] ch7
- [x] ch8
- [x] ch9
- [ ] ch10
- [ ] ch11
- [ ] ch12
- [ ] ch13
- [ ] ch14
- [ ] ch15
- [ ] ch16
- [ ] Bonus chapters (online)

### Code Enhancements

- [x] Move common Shape functionality to a separate file
- [ ] Move Shape objects code into its own folder
- [ ] Move headers into a different folder than source code files
- [ ] Write a function for canvas.h that directly exports image files to .png instead of only to .ppm
- [x] Separate Color class into its own header file
- [ ] Rename all .h files to .hpp


# Rename all *.h to *.hpp
for file in *.h; do
    mv -- "$file" "${file%.h}.hpp"
done