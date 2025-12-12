# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an implementation of a 3D ray tracer from the book "The Ray Tracer Challenge" by Jamis Buck. The project uses C++23 and CMake, progressively implementing ray tracing features chapter by chapter, from basic vector math to advanced features like reflections, refractions, patterns, and mesh rendering.

## Build System & Commands

The project uses CMake with C++23 standard. All build scripts are located in the root directory.

**Building and running a challenge:**
```bash
sh ./build.sh
# Optionally convert PPM output to PNG: convert values.ppm ./img.png
```
- Before running, edit `MAIN_FILE_NAME` in `CMakeLists.txt` to select which challenge file to build
- Outputs a `values.ppm` file that can be converted to PNG format

**Running unit tests:**
```bash
sh ./testing.sh
```
- Runs the complete test suite using Google Test framework
- Run individual test with: `./build/test.out --gtest_filter=TestName`

**Profiling (performance analysis):**
```bash
sh ./profiling.sh
```
- Requires `perf`, FlameGraph, and Google Chrome
- Generates flame graphs for performance analysis

**Manual CMake setup:**
```bash
mkdir build
cd build
cmake ..          # For challenges
cmake -Dtest=ON   # For tests
make challenge.out  # Build a specific challenge
make test.out       # Build test suite
```

## Code Architecture

### Core Ray Tracing Pipeline

The codebase is organized around a 3D rendering pipeline:

1. **Foundational Math** (`tuple.hpp`, `matrix.hpp`, `transform.hpp`)
   - Tuples (points, vectors, homogeneous coordinates)
   - 4x4 matrices for transformations
   - Transformation composition (translation, scaling, rotation, shearing)

2. **Geometry** (`ray.hpp`, `camera.hpp`, `canvas.hpp`, `intersections.hpp`)
   - Rays and ray casting
   - Camera and viewport definitions
   - Canvas (pixel grid output)
   - Intersection detection and computation

3. **Shape Hierarchy** (`src/shapes/`)
   - Base `shape.hpp` class providing interface
   - Concrete shapes: `sphere.hpp`, `plane.hpp`, `cube.hpp`, `cylinder.hpp`, `cone.hpp`, `triangle.hpp`, `smooth_triangle.hpp`
   - Composite structures: `group.hpp` (bounding hierarchy), `csg.hpp` (Constructive Solid Geometry)
   - OBJ file loading for mesh rendering via `obj_loader.hpp`

4. **Lighting & Materials** (`lights.hpp`, `material.hpp`)
   - Point light sources
   - Phong reflection model for shading
   - Material properties (color, ambient/diffuse/specular factors, shininess, reflection/refraction)

5. **Patterns** (`src/patterns/`)
   - Base `pattern.hpp` interface
   - Solid colors (`solid_pattern.hpp`)
   - Geometric patterns: `stripe_pattern.hpp`, `checkers_pattern.hpp`, `gradient_pattern.hpp`
   - Ring patterns: `radial_ring_pattern.hpp`, `conical_ring_pattern.hpp`
   - Advanced: `perlin_pattern.hpp`, `permutation_pattern.hpp` (Perlin noise based)
   - Composite: `blend_pattern.hpp` (pattern composition)
   - Patterns are applied to materials for texture effects

6. **World & Rendering** (`world.hpp`, `ray_tracer.hpp`, `computation.hpp`)
   - `world.hpp` manages scene (lights, objects)
   - `ray_tracer.hpp` provides main rendering pipeline
   - `computation.hpp` caches ray-surface intersection data for efficient shading
   - Supports reflection/refraction with recursion depth control

### Key Design Patterns

- **Shape inheritance hierarchy**: All shapes inherit from base `Shape` class with virtual methods for ray intersection and normal calculation
- **Patterns via composition**: Materials use patterns through the `Pattern` interface
- **Transformation matrices**: All shapes support transformation via 4x4 matrices; transformations compose naturally
- **Intersection caching**: `Computation` struct captures ray-surface intersection point details (position, normal, reflection vectors, etc.) to avoid recalculation

## Project Structure

```
src/
├── Core math: tuple.hpp, matrix.hpp, transform.hpp
├── Rendering: ray.hpp, camera.hpp, canvas.hpp, world.hpp
├── Lighting: lights.hpp, material.hpp, color.hpp
├── Geometry: intersection.hpp, intersections.hpp, computation.hpp
├── shapes/          # 2D and 3D shape implementations
└── patterns/        # Texture pattern implementations

challenges/         # Chapter-by-chapter challenge implementations
tests/             # Google Test test suite (one file per chapter)
```

## Code Style & Standards

- **Formatting**: Clang-format with Google style (enforced by pre-commit hook)
- **C++ Standard**: C++23
- **Testing**: Google Test framework (gtest)
- **Header files**: All use `.hpp` extension

## Implementation Notes

### Important Caveat on Challenge Files
The `challenges/` directory contains implementations from each chapter. Later chapters introduce major refactors (especially after Ch9). Older challenge files may not be compatible with the current codebase structure. Use git history to find compatible versions for older chapters if needed.

### Eigen Library
The project uses Eigen library for linear algebra (referenced in build setup).

### PerlinNoise Dependency
`PerlinNoise.hpp` is automatically downloaded from GitHub during CMake configuration. Internet connectivity is required for the build process.

### Float Epsilon Comparison
Throughout the codebase, floating-point comparisons use epsilon-based equality checks due to floating-point precision limitations (typically `epsilon = 0.00001` or `EPSILON` constants).

## Development Workflow

1. **Adding a new shape**: Extend `src/shapes/shape.hpp` interface, implement in new `.cpp/.hpp` pair
2. **Adding patterns**: Inherit from `src/patterns/pattern.hpp`, implement `pattern_at()` method
3. **Testing changes**: Run `sh testing.sh` to ensure all tests pass
4. **Running code formatting**: `pre-commit run --all-files` (clang-format)
5. **Profiling optimizations**: Use `sh profiling.sh` to generate flame graphs

## Common TODOs in Codebase

Notable open tasks (see README.md for complete list):
- Move headers to separate directory
- Direct PNG export from canvas (currently only PPM)
- CMake configuration improvements for subdirectories
- Config file for camera/light settings
- Advanced features: motion blur, anti-aliasing, normal perturbation, GPU optimization
