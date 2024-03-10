# The Ray Tracer Challenge

Implementation of the code from the book [The Ray Tracer Challenge: A Test-Driven Guide to Your First 3D Renderer](http://www.raytracerchallenge.com/).

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

## TODO:

- [x] Import and use `gtest`
- [x] Do some sample tests using gtest
- [x] Fix the tests folder to actually be tests of your code
- [x] Create a bash script that does all of your building for you
    - [x] main function building
    - [x] test building
- [ ] TODO: Write a function for canvas.h that directly exports image files to .png instead of only to .ppm