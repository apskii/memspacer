#pragma once

#include <GL/glew.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define BOOST_DISABLE_THREADS
#include <boost/pool/pool.hpp>

typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::quat Quat;
typedef glm::mat3 Mat3;
typedef glm::mat4 Mat4;

typedef boost::pool<> Pool;

#define TPL(A)     template<typename A>
#define TPL_2(A,B) template<typename A, typename B>
