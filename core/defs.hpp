#ifndef CORE_DEFS_HPP
#define CORE_DEFS_HPP

#include <GL/glew.h>
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

#define TSPEC template<>

#define TPL(A)         template<typename A>
#define TPL_2(A,B)     template<typename A, typename B>
#define TPL_3(A,B,C)   template<typename A, typename B, typename C>
#define TPL_4(A,B,C,D) template<typename A, typename B, typename C, typename D>

#define HKT(TY_CON) template <template <typename> class TY_CON>

#define func static auto
#define meth auto
#define virt virtual auto

#define val const auto
#define var auto

#endif CORE_DEFS_HPP