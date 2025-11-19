#include "_collisioncheck.h"

_collisionCheck::_collisionCheck()
{
    //ctor
}

_collisionCheck::~_collisionCheck()
{
    //dtor
}

// Very simple: true if all coordinates are (almost) equal
bool _collisionCheck::isLinearCol(vec3 p1, vec3 p2)
{
    const float eps = 1e-3f;
    return (fabs(p1.x - p2.x) < eps &&
            fabs(p1.y - p2.y) < eps &&
            fabs(p1.z - p2.z) < eps);
}

// 2D circle–circle
bool _collisionCheck::isRadialCol(vec2 p1, vec2 p2, float r1, float r2, float thrhld)
{
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    float dist = sqrtf(dx*dx + dy*dy);
    return (dist - (r1 + r2) < thrhld);
}

// 3D sphere–sphere
bool _collisionCheck::isSphereCol(vec3 p1, vec3 p2, float r1, float r2, float thrhld)
{
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    float dz = p1.z - p2.z;
    float dist = sqrtf(dx*dx + dy*dy + dz*dz);
    return (dist - (r1 + r2) < thrhld);
}

// Simple 2D equality check
bool _collisionCheck::isPlanoCol(vec2 p1, vec2 p2)
{
    const float eps = 1e-3f;
    return (fabs(p1.x - p2.x) < eps &&
            fabs(p1.y - p2.y) < eps);
}

// Very rough 3D cube–cube overlap: we just check distance < fixed threshold
bool _collisionCheck::isCubicCol(vec3 p1, vec3 p2)
{
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    float dz = p1.z - p2.z;
    float dist2 = dx*dx + dy*dy + dz*dz;
    // threshold radius ~ 1 unit
    return dist2 < (1.0f * 1.0f);
}
