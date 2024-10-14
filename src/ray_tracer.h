#include "canvas.h"
#include "intersection.h"
#include "intersections.h"
#include "lights.h"
#include "material.h"
#include "matrix.h"
#include "ray.h"
#include "transform.h"
#include "tuple.h"
#include "color.h"
#include "world.h"
#include "computation.h"
#include "camera.h"
// shapes
// TODO: move the definitions of these into shared header files in
// their directory for ease of use
#include "shape.h"
#include "sphere.h"
#include "plane.h"
// patterns
#include "pattern.h"
#include "stripe_pattern.h"
#include "gradient_pattern.h"
#include "conical_ring_pattern.h"
