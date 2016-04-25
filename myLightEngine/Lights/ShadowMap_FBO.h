#ifndef H_SHADOWMAPFBO_H
#define H_SHADOWMAPFBO_H

#include <GL\glew.h>

class ShadowMapFBO
{
public:
	ShadowMapFBO();

	~ShadowMapFBO();


	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void BindForWriting();

	void BindForReading(GLenum TextureUnit);

private:
	GLuint m_fbo;
	GLuint m_shadowMap;
};


#endif  // H_SHADOWMAPFBO_H