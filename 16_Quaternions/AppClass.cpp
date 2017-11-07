#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//initializing the model
	m_pModel = new Simplex::Model();

	//Load a model
	m_pModel->Load("Minecraft\\Steve.obj");
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Get a timer
	static uint uClock = m_pSystem->GenClock();
	float fTimer = m_pSystem->GetTimeSinceStart(uClock);
	float fDeltaTime = m_pSystem->GetDeltaTime(uClock);
	quaternion q1;
	quaternion q2 = glm::angleAxis(359.9f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q3 = glm::angleAxis(359.9f, vector3(0.0f, 1.0f, 0.0f));
	quaternion q4 = glm::angleAxis(359.9f, vector3(1.0f, 0.0f, 0.0f));
	float fPercentage = MapValue(fTimer, 0.0f, 5.0f, 0.0f, 1.0f);
	quaternion qSLERP = glm::mix(q1, q2, fPercentage);
	quaternion qSLERP1 = glm::mix(q1, q3, fPercentage);
	quaternion qSLERP2 = glm::mix(q1, q4, fPercentage);
	m_m4Steve = glm::toMat4(qSLERP * qSLERP1 * qSLERP1);

	/*matrix4 m4Orientx = glm::rotate(IDENTITY_M4, m_v3Orientation.x, vector3(1.5f,0.0f, 0.0f));
	matrix4 m4Orienty = glm::rotate(IDENTITY_M4, m_v3Orientation.y, vector3(0.0f, 1.5f, 0.0f));
	matrix4 m4Orientz = glm::rotate(IDENTITY_M4, m_v3Orientation.z, vector3(0.0f, 0.0f, 1.5f));
	matrix4 m4Orientation = m4Orientx * m4Orienty * m4Orientz;
	m_m4Steve *= glm::toMat4(m_qOrientation);*/
	
	//Attach the model matrix that takes me from the world coordinate system
	m_pModel->SetModelMatrix(m_m4Steve, m_pModel->GetVertexList());

	//Send the model to render list
	m_pModel->AddToRenderList();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release model
	SafeDelete(m_pModel);

	//release GUI
	ShutdownGUI();
}
