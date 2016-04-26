#include <stdio.h>

#include "ShadowMap_FBO.h"

ShadowMapFBO::ShadowMapFBO()
{
	m_fbo = 0;
	m_shadowMap = 0;
}

ShadowMapFBO::~ShadowMapFBO()
{
	if (m_fbo != 0){
		glDeleteFramebuffers(1, &m_fbo);
	}
}