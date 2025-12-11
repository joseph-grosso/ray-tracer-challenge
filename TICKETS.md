# Ray Tracer Challenge - Development Tickets

## Quick Wins

### 1. PNG Export for Canvas
**Priority**: High
**Effort**: Small (2-4 hours)
**Type**: Feature

**Description**:
Add direct PNG export functionality to the Canvas class, eliminating the need for manual PPM-to-PNG conversion using external tools.

**Current Workflow**:
- Build renders to `values.ppm`
- User must manually run: `convert values.ppm ./img.png`

**Desired Workflow**:
- Build renders directly to PNG (or provides easy one-command export)

**Acceptance Criteria**:
- [ ] Canvas has method to export to PNG format
- [ ] PNG export maintains same image quality as PPM
- [ ] Integration in build pipeline is documented
- [ ] Tests verify PNG output validity

**Related Files**: `src/canvas.hpp`, `src/canvas.cpp`

---

### 2. Fix CMake Configuration for Patterns and Shapes Subdirectories
**Priority**: Medium
**Effort**: Small-Medium (2-3 hours)
**Type**: Refactor

**Description**:
Refactor CMakeLists.txt in `src/patterns/` and `src/shapes/` directories to be self-contained and not rely on parent directory configuration.

**Current Issue**:
Subdirectory CMake files have implicit dependencies on parent configuration.

**Acceptance Criteria**:
- [ ] `src/patterns/CMakeLists.txt` is self-contained
- [ ] `src/shapes/CMakeLists.txt` is self-contained
- [ ] Build succeeds with `-Dtest=ON` and without
- [ ] No configuration changes needed to parent CMakeLists.txt

**Related Files**: `src/CMakeLists.txt`, `src/patterns/CMakeLists.txt`, `src/shapes/CMakeLists.txt`

---

### 3. Fix PerlinNoise Download and Fallback
**Priority**: Medium
**Effort**: Small (1-2 hours)
**Type**: Maintenance

**Description**:
Improve robustness of PerlinNoise.hpp download in CMakeLists.txt. Handle network failures gracefully and consider alternative download sources.

**Current Issue**:
- Downloads directly from GitHub master branch (unstable reference)
- No fallback if download fails
- Build fails without internet connectivity

**Acceptance Criteria**:
- [ ] Download uses stable release reference (tag/commit hash)
- [ ] Graceful error handling if download fails
- [ ] Option to use local copy if already present
- [ ] Documentation on manual download process
- [ ] Build warning if PerlinNoise.hpp not available

**Related Files**: `CMakeLists.txt`

---

## Code Quality Improvements

### 4. Use Initializer Lists in Constructors
**Priority**: Medium
**Effort**: Medium (4-6 hours)
**Type**: Refactor

**Description**:
Refactor constructors throughout the codebase to use initializer lists instead of member assignments in constructor body. Follows C++ Core Guidelines.

**Why**:
- Better performance (no default construction then assignment)
- More idiomatic modern C++
- Supports const members properly

**Acceptance Criteria**:
- [ ] All constructors use initializer lists
- [ ] No member assignments in constructor bodies (except complex logic)
- [ ] All tests pass
- [ ] Code compiles with no warnings

**Estimated Scope**: Multiple files across src/, shapes/, patterns/

**Reference**: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c49-prefer-initialization-to-assignment-in-constructors

---

### 5. Convert Trivial Getters/Setters to Public Members
**Priority**: Low
**Effort**: Medium (3-4 hours)
**Type**: Refactor

**Description**:
Replace simple getter/setter pairs with public data members following C++ Core Guidelines for data members that don't require encapsulation logic.

**Why**:
- Simpler, more concise code
- Fewer lines of boilerplate
- Still maintains public interface contract

**Acceptance Criteria**:
- [ ] All trivial getters/setters removed
- [ ] No functionality changes
- [ ] All tests pass
- [ ] Public members documented with comments where needed

**Reference**: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c131-avoid-trivial-getters-and-setters

---

## Feature Additions

### 6. Anti-aliasing Implementation
**Priority**: Medium
**Effort**: Medium (4-6 hours)
**Type**: Feature

**Description**:
Implement anti-aliasing by sampling multiple rays per pixel and averaging results. Improves image quality, especially on edges and fine details.

**Technical Approach**:
- Modify Camera/RayTracer to support sub-pixel sampling
- Sample rays at multiple points within each pixel
- Average color results
- Make sample count configurable

**Acceptance Criteria**:
- [ ] Camera supports configurable anti-aliasing samples (e.g., 4x4 grid)
- [ ] Output quality visibly improved on test images
- [ ] Performance impact documented
- [ ] Tests verify correct ray distribution
- [ ] Can be toggled on/off

**Related Files**: `src/camera.hpp`, `src/camera.cpp`, `src/ray_tracer.hpp`

---

### 7. Config File Support for Camera and Light Settings
**Priority**: Medium
**Effort**: Medium-Large (6-8 hours)
**Type**: Feature

**Description**:
Add support for YAML or JSON config files to define camera position, field of view, and light sources, eliminating hardcoding in challenge files.

**Technical Approach**:
- Choose format (YAML recommended for readability)
- Create parser/loader
- Integrate with World/Camera initialization
- Provide example config templates

**Acceptance Criteria**:
- [ ] YAML config files can define camera (position, target, FOV)
- [ ] YAML config files can define lights (position, color, intensity)
- [ ] Config files can define scene objects (shapes, materials, transforms)
- [ ] Example configs provided for existing challenges
- [ ] Graceful error handling for malformed configs
- [ ] Documentation with config file schema

**Related Files**: New files for config loader, modified `src/world.hpp`, challenge files

---

### 8. Motion Blur Implementation
**Priority**: Low
**Effort**: Large (8-12 hours)
**Type**: Feature

**Description**:
Add motion blur effect by simulating camera/object movement over exposure time during rendering.

**Technical Approach**:
- Extend Ray and Intersection to include time parameter
- Modify shapes to support time-dependent transforms
- Sample rays at multiple times during exposure
- Average results

**Acceptance Criteria**:
- [ ] Objects can have time-dependent motion
- [ ] Motion blur renders correctly
- [ ] Time/exposure configurable
- [ ] Performance acceptable for reasonable exposure durations
- [ ] Test images demonstrate effect

**Related Files**: `src/ray.hpp`, shapes files, `src/ray_tracer.hpp`

---

## Stretch Goals

### 9. Torus Primitive Shape
**Priority**: Low
**Effort**: Large (8-10 hours)
**Type**: Feature

**Description**:
Add Torus (doughnut shape) as a primitive shape with ray intersection via quadratic equation solving.

**Technical Approach**:
- Solve torus ray intersection equations
- Handle edge cases (rays through hole, tangent rays)
- Implement normal vector calculation
- Add comprehensive tests

**Related Files**: New `src/shapes/torus.hpp/cpp`

---

### 10. Bounding Box Optimization
**Priority**: Low
**Effort**: Large (8-10 hours)
**Type**: Performance

**Description**:
Implement axis-aligned bounding boxes for accelerated ray-object intersection tests, improving performance on complex scenes.

**Technical Approach**:
- Add AABB class
- Integrate with Shape hierarchy
- Implement Group/CSG spatial indexing
- Benchmark performance improvements

**Acceptance Criteria**:
- [ ] AABB intersection tests implemented
- [ ] Measurable performance improvement on complex scenes
- [ ] Backward compatible API
- [ ] Tests verify correctness

**Related Files**: New AABB class, modified shapes, `src/world.hpp`

---

### 11. Move Headers to Separate Directory
**Priority**: Low
**Effort**: Medium (3-4 hours)
**Type**: Refactor

**Description**:
Reorganize project to move all `.hpp` files to a dedicated `include/` directory, separating interface from implementation.

**Current Structure**: Headers mixed with source in `src/`

**Proposed Structure**:
```
include/
├── core/
├── shapes/
├── patterns/
└── ...
src/
├── core/
├── shapes/
├── patterns/
└── ...
```

**Acceptance Criteria**:
- [ ] All headers moved to include/ with same structure
- [ ] Include paths updated
- [ ] CMakeLists.txt updated to reflect structure
- [ ] Build succeeds with `-Dtest=ON` and without
- [ ] All tests pass

---

### 12. Texture Mapping Support
**Priority**: Low
**Effort**: Large (10-12 hours)
**Type**: Feature

**Description**:
Implement UV-mapped texture rendering, allowing image textures to be applied to objects.

**Technical Approach**:
- Add UV coordinate support to shapes
- Create Texture class wrapping image data
- Implement texture sampling in material shading
- Support OBJ texture coordinates

**Acceptance Criteria**:
- [ ] UV coordinates supported on triangle meshes
- [ ] Image textures can be loaded and sampled
- [ ] Texture filtering implemented (nearest/bilinear)
- [ ] Works with OBJ loader
- [ ] Example scene with textured objects

---

## Notes

- Tickets are roughly ordered by recommended implementation priority
- Quick wins (1-3) are good for immediate productivity gains
- Code quality improvements (4-5) improve maintainability
- Features (6-8) add rendering capabilities
- Stretch goals (9-12) are longer-term enhancements

