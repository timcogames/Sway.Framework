#ifndef SWAY_GL_GLPREREQS_H
#define SWAY_GL_GLPREREQS_H

#define BUFFER_OFFSET(x)((lpstr) NULL + (x))

/* Имена униформ. */
#define SHADER_UNIFORM_NAME_MODEL_MATRIX "modelMatrix"
#define SHADER_UNIFORM_NAME_VIEW_MATRIX "viewMatrix"
#define SHADER_UNIFORM_NAME_PROJ_MATRIX "projectionMatrix"

/* Имена атрибутов. */
#define VERTEX_ATTRIBUTE_POSITION "attr_position"
#define VERTEX_ATTRIBUTE_COLOR "attr_color"
#define VERTEX_ATTRIBUTE_TEXCOORD0 "attr_texCoord_0"
#define VERTEX_ATTRIBUTE_TEXCOORD1 "attr_texCoord_1"
#define VERTEX_ATTRIBUTE_TEXCOORD2 "attr_texCoord_2"
#define VERTEX_ATTRIBUTE_TEXCOORD3 "attr_texCoord_3"
#define VERTEX_ATTRIBUTE_NORMAL "attr_normal"
#define VERTEX_ATTRIBUTE_TANGENT "attr_tangent"
#define VERTEX_ATTRIBUTE_BINORMAL "attr_binormal"
#define VERTEX_ATTRIBUTE_BLEND_WEIGHTS "attr_blendWeights"
#define VERTEX_ATTRIBUTE_BLEND_INDICES "attr_blendIndices"

#include "../memory/safedeletemacros.h"
#include "../defines.h"
#include "../types.h"

#include <vector> // std::vector
#include <string> // std::string
#include <fstream> // std::ifstream
#include <iostream> // std::cout, std::ios
#include <algorithm> // std::for_each
#include <map> // std::map
#include <unordered_map> // std::unordered_map
#include <initializer_list> // std::initializer_list

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct HardwareBufferDescription;
struct HardwareBufferCreateInfo;
struct VertexAttribute;
struct VertexElement;

class ShaderBuilder;
class ShaderTypeUtils;
class HardwareBuffer;
class HardwareBufferTargetUtils;
class PrimitiveTopologyUtils;
class VertexAttributeBinding;
class VertexDeclaration;

typedef u32 ShaderProgramHandle_t;
typedef u32 ShaderHandle_t;
typedef u32 HardwareBufferHandle_t;

typedef std::unordered_map<std::string, math::TVector4<f32>> UniformVec4fContainer_t;
typedef std::unordered_map<std::string, VertexAttribute> VertexAttributeContainer_t;
typedef std::vector<VertexElement> VertexElementContainer_t;

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_GLPREREQS_H