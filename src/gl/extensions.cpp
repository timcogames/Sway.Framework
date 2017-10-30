#include "extensions.h"
#include <string.h> // strstr

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

PFNGLGENBUFFERSARBPROC Extensions::glGenBuffersARB = NULL;
PFNGLBINDBUFFERARBPROC Extensions::glBindBufferARB = NULL;
PFNGLBUFFERDATAARBPROC Extensions::glBufferDataARB = NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC Extensions::glGetBufferParameterivARB = NULL;
PFNGLDELETEBUFFERSARBPROC Extensions::glDeleteBuffersARB = NULL;
PFNGLISBUFFERARBPROC Extensions::glIsBufferARB = NULL;
PFNGLBUFFERSUBDATAARBPROC Extensions::glBufferSubDataARB = NULL;
PFNGLMAPBUFFERARBPROC Extensions::glMapBufferARB = NULL;
PFNGLUNMAPBUFFERARBPROC Extensions::glUnmapBufferARB = NULL;

PFNGLCREATEPROGRAMOBJECTARBPROC Extensions::glCreateProgramObjectARB = NULL;
PFNGLCREATESHADEROBJECTARBPROC Extensions::glCreateShaderObjectARB = NULL;
PFNGLSHADERSOURCEARBPROC Extensions::glShaderSourceARB = NULL;
PFNGLCOMPILESHADERARBPROC Extensions::glCompileShaderARB = NULL;
PFNGLATTACHOBJECTARBPROC Extensions::glAttachObjectARB = NULL;
PFNGLLINKPROGRAMARBPROC Extensions::glLinkProgramARB = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC Extensions::glUseProgramObjectARB = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC Extensions::glGetUniformLocationARB = NULL;
PFNGLDELETEPROGRAMSARBPROC Extensions::glDeleteProgramsARB = NULL;
PFNGLDETACHOBJECTARBPROC Extensions::glDetachObjectARB = NULL;
PFNGLDELETEOBJECTARBPROC Extensions::glDeleteObjectARB = NULL;
PFNGLVALIDATEPROGRAMARBPROC Extensions::glValidateProgramARB = NULL;
PFNGLUNIFORM4FARBPROC Extensions::glUniform4fARB = NULL;
PFNGLGETPROGRAMIVARBPROC Extensions::glGetProgramivARB = NULL;
PFNGLGETPROGRAMINFOLOGPROC Extensions::glGetProgramInfoLog = NULL;
PFNGLGETSHADERIVPROC Extensions::glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC Extensions::glGetShaderInfoLog = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC Extensions::glGetObjectParameterivARB = NULL;
PFNGLGETINFOLOGARBPROC Extensions::glGetInfoLogARB = NULL;

PFNGLDISABLEVERTEXATTRIBARRAYARBPROC Extensions::glDisableVertexAttribArrayARB = NULL;
PFNGLGETATTRIBLOCATIONARBPROC Extensions::glGetAttribLocationARB = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC Extensions::glVertexAttribPointerARB = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC Extensions::glEnableVertexAttribArrayARB = NULL;	

b32 Extensions::checkSupport(lpcstr extensions, lpcstr name) {
	if (NOT strstr(extensions, name)) {
		printf("Extension %s is not supported.", name);
		return false;
	}

	return true;
}

struct ExtensionAvailability {
	b32 GL_ARB_vertex_buffer_object_supported;
	b32 GL_ARB_map_buffer_range_available;
	b32 vertexArrayObject;
	b32 drawElementsBaseVertex;
	b32 fragmentProgram;
};

void Extensions::define() {
	ExtensionAvailability availability;
	lpcstr extensions = (lpcstr) glGetString(GL_EXTENSIONS);

	availability.GL_ARB_vertex_buffer_object_supported = checkSupport(extensions, "GL_ARB_vertex_buffer_object");
	if (availability.GL_ARB_vertex_buffer_object_supported) {
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) glXGetProcAddressARB((const GLubyte*) "glGenBuffersARB");
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) glXGetProcAddressARB((const GLubyte*) "glBindBufferARB");
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) glXGetProcAddressARB((const GLubyte*) "glBufferDataARB");
		glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetBufferParameterivARB");
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) glXGetProcAddressARB((const GLubyte*) "glDeleteBuffersARB");
		glIsBufferARB = (PFNGLISBUFFERARBPROC) glXGetProcAddressARB((const GLubyte*) "glIsBufferARB");
		glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) glXGetProcAddressARB((const GLubyte*) "glBufferSubDataARB");
		glMapBufferARB = (PFNGLMAPBUFFERARBPROC) glXGetProcAddressARB((const GLubyte*) "glMapBufferARB");
		glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) glXGetProcAddressARB((const GLubyte*) "glUnmapBufferARB");
	}

	glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glCreateProgramObjectARB");
	glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glCreateShaderObjectARB");
	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) glXGetProcAddressARB((const GLubyte*) "glShaderSourceARB");
	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) glXGetProcAddressARB((const GLubyte*) "glCompileShaderARB");
	glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glAttachObjectARB");
	glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) glXGetProcAddressARB((const GLubyte*) "glLinkProgramARB");
	glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glUseProgramObjectARB");
	glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetUniformLocationARB");
	glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC) glXGetProcAddressARB((const GLubyte*) "glDeleteProgramsARB");
	glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glDetachObjectARB");
	glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glDeleteObjectARB");
	glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC) glXGetProcAddressARB((const GLubyte*) "glValidateProgramARB");
	glUniform4fARB = (PFNGLUNIFORM4FARBPROC) glXGetProcAddressARB((const GLubyte*) "glUniform4fARB");
	glGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetProgramivARB");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) glXGetProcAddressARB((const GLubyte*) "glGetProgramInfoLog");
	glGetShaderiv = (PFNGLGETSHADERIVPROC) glXGetProcAddressARB((const GLubyte*) "glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glXGetProcAddressARB((const GLubyte*) "glGetShaderInfoLog");
	glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetObjectParameterivARB");
	glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetInfoLogARB");

	glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) glXGetProcAddressARB((const GLubyte*) "glDisableVertexAttribArrayARB");
	glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetAttribLocationARB");
	glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC) glXGetProcAddressARB((const GLubyte*) "glVertexAttribPointerARB");
	glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) glXGetProcAddressARB((const GLubyte*) "glEnableVertexAttribArrayARB");
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)