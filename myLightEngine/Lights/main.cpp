#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Util_han.h"
#include "Pipeline.h"
#include "Camera.h"
#include "LightTechnique.h"
#include "Glut_backend.h"
#include "Mesh.h"

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1200

static float FieldDepth = 10.0f;

class Tutorial22 : public ICallbacks
{
public:

	Tutorial22()
	{
		m_pGameCamera = NULL;
		m_pEffect = NULL;
		m_scale = 0.0f;
		m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
		m_directionalLight.AmbientIntensity = 1.0f;
		m_directionalLight.DiffuseIntensity = 0.01f;
		m_directionalLight.Direction = Vector3f(1.0f, -1.0, 0.0);

		m_persProjInfo.FOV = 60.0f;
		m_persProjInfo.Height = WINDOW_HEIGHT;
		m_persProjInfo.Width = WINDOW_WIDTH;
		m_persProjInfo.zNear = 1.0f;
		m_persProjInfo.zFar = 50.0f;
	}

	~Tutorial22()
	{
		delete m_pEffect;
		delete m_pGameCamera;
		delete m_pMesh;
	}

	bool Init()
	{
		Vector3f Pos(3.0f, 7.0f, -10.0f);
		Vector3f Target(0.0f, -0.2f, 1.0f);
		Vector3f Up(0.0, 1.0f, 0.0f);

		m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

		m_pEffect = new LightingTechnique();

		if (!m_pEffect->Init()) {
			printf("Error initializing the lighting technique\n");
			return false;
		}

		m_pEffect->Enable();

		m_pEffect->SetTextureUnit(0);

		m_pMesh = new Mesh();

		return m_pMesh->LoadMesh("../Resource/room.obj");
	}

	void Run()
	{
		GLUTBackendRun(this);
	}

	virtual void RenderSceneCB()
	{
		m_scale += 0.01f;

		m_pGameCamera->OnRender();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Pipeline p;

		p.WorldPos(0.0f, 0.0f, 10.0f);
		p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
		p.SetPerspectiveProj(m_persProjInfo);
		m_pEffect->SetWVP(p.GetWVPTrans());
		m_pEffect->SetWorldMatrix(p.GetWorldTrans());
		m_pEffect->SetDirectionalLight(m_directionalLight);
		m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
		m_pEffect->SetMatSpecularIntensity(0.0f);
		m_pEffect->SetMatSpecularPower(0);


		m_pEffect->SetWVP(p.GetWVPTrans());
		m_pMesh->Render();

		glutSwapBuffers();
	}



	void KeyboardCB(HAN_KEY HANKey)
	{
		switch (HANKey) {
		case HAN_KEY_ESCAPE:
		case HAN_KEY_q:
			GLUTBackendLeaveMainLoop();
			break;
		case HAN_KEY_a:
			m_directionalLight.AmbientIntensity += 0.05f;
			break;
		case HAN_KEY_s:
			m_directionalLight.AmbientIntensity -= 0.05f;
			break;
		case HAN_KEY_z:
			m_directionalLight.DiffuseIntensity += 0.05f;
			break;
		case HAN_KEY_x:
			m_directionalLight.DiffuseIntensity -= 0.05f;
			break;
		default:
			m_pGameCamera->OnKeyboard(HANKey);
		}
	}


	virtual void PassiveMouseCB(int x, int y)
	{
		m_pGameCamera->OnMouse(x, y);
	}

private:

	LightingTechnique* m_pEffect;
	Camera* m_pGameCamera;
	float m_scale;
	DirectionalLight m_directionalLight;
	Mesh* m_pMesh;
	PersProjInfo m_persProjInfo;
};


int main(int argc, char** argv)
{
	//    Magick::InitializeMagick(*argv);
	GLUTBackendInit(argc, argv, true, false);

	if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "Tutorial 22")) {
		return 1;
	}

	Tutorial22* pApp = new Tutorial22();

	if (!pApp->Init()) {
		return 1;
	}

	pApp->Run();

	delete pApp;

	return 0;
}
