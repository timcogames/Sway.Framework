#ifndef SWAY_GL_EXTENSIONSUPPORT_H
#define SWAY_GL_EXTENSIONSUPPORT_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct ExtensionSupport {
	bool GL_ARB_vertex_buffer_object_available;
	bool GL_ARB_shader_objects_available;
	bool GL_ARB_fragment_program_available;
	bool GL_ARB_vertex_program_available;
	bool GL_ARB_vertex_shader_available;
	bool GL_ARB_multitexture_available;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_EXTENSIONSUPPORT_H