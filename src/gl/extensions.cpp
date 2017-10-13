#include "extensions.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

PFNGLGENBUFFERSARBPROC Extensions::glGenBuffersARB = NULL;
PFNGLBINDBUFFERARBPROC Extensions::glBindBufferARB = NULL;
PFNGLBUFFERDATAARBPROC Extensions::glBufferDataARB = NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC Extensions::glGetBufferParameterivARB = NULL;
PFNGLDELETEBUFFERSARBPROC Extensions::glDeleteBuffersARB = NULL;
PFNGLISBUFFERARBPROC Extensions::glIsBufferARB = NULL;
PFNGLBUFFERSUBDATAARBPROC Extensions::glBufferSubDataARB = NULL;

void Extensions::define()
{
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) glXGetProcAddressARB((const GLubyte*) "glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC) glXGetProcAddressARB((const GLubyte*) "glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC) glXGetProcAddressARB((const GLubyte*) "glBufferDataARB");
	glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetBufferParameterivARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) glXGetProcAddressARB((const GLubyte*) "glDeleteBuffersARB");
	glIsBufferARB = (PFNGLISBUFFERARBPROC) glXGetProcAddressARB((const GLubyte*) "glIsBufferARB");
	glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) glXGetProcAddressARB((const GLubyte*) "glBufferSubDataARB");
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)