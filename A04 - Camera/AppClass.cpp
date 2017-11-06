#include "AppClass.h"
#include <GL\glut.h>
using namespace Simplex;
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//init the camera
	m_pCamera = new MyCamera();
	m_pCamera->SetPositionTargetAndUp(
			vector3(0.0f, 3.0f, 20.0f), //Where my eyes are
			vector3(0.0f, 3.0f, 19.0f), //where what I'm looking at is
			AXIS_Y);					//what is up
	//camDirection = (m_pCamera->GetTarget - m_pCamera->GetPosition);
	camPosition = vector3(0.0f, 3.0f, 20.0f);
	camDirection = vector3(0.0f, 0.0f, -1.0f);
	//Get the singleton
	m_pMyMeshMngr = MyMeshManager::GetInstance();
	m_pMyMeshMngr->SetCamera(m_pCamera);
}
//move forward and backwards
void Application::MoveForward(float speed) {
	camPosition += camDirection * speed * deltaTime;
	m_pCamera->SetPosition(camPosition);
	m_pCamera->SetTarget(camPosition + camDirection);
	m_pCamera->SetUp(vector3(0, 1, 0));
}
//move left and right
void Application::MoveSideways(float speed) {
	vector3 right = vector3(camDirection.z, camDirection.y, -camDirection.x);
	camPosition -=  right * speed * deltaTime;
	m_pCamera->SetPosition(camPosition);
	m_pCamera->SetTarget(camPosition + camDirection);
	m_pCamera->SetUp(vector3(0, 1, 0));
}
//rotate the camera by the mouse movement delta
void Application::RotateCamera(vector2 mouseDelta) {
		// Get the view vector
	mouseDelta *= deltaTime;
	camRotation += vector3(mouseDelta.x, 0, mouseDelta.y);
	//this code should apply pitch and yaw, I'm not sure why it has no effect on pitch. 
	//calculate direction
	float x = (cos(camRotation.x) * cos(camRotation.y));
	float z = (sin(camRotation.x) * cos(camRotation.y));
	float y = sin(camRotation.y);
	camDirection = vector3(x, y, z);
	//std::cout << mouseDelta.y << std::endl;
	
	//TRIED TO USE QUATERNIONS TO APPLY ROTATIONS, DID NOT HAVE ANY EFFECT ON CAMERA MATRIX, NO CLUE WHY
	//m_pCamera->GetViewMatrix() *= glm::toMat4(quaternion(vector3(glm::radians(mouseDelta.y), glm::radians(mouseDelta.x), 0.0f)));
	
	//m_pCamera->GetViewMatrix() = glm::toMat4(glm::angleAxis(mouseDelta.y, vector3(0.0, 0.0f, 1.0f)));
	//m_pCamera->GetViewMatrix() = glm::toMat4(glm::angleAxis(mouseDelta.x, vector3(0.0, 1.0f, 0.0f)));

	//camDirection = vector3(m_pCamera->GetTarget().x, m_pCamera->GetTarget().y, m_pCamera->GetTarget().z);
	m_pCamera->SetTarget(camPosition + camDirection);
	m_pCamera->SetUp(vector3(0, 1, 0));
}
void Application::Update(void)
{
	float time = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (time - oldTime) / 1000;
	oldTime = time;
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();
	//camPosition.x += .01f;
	
	//m_pCamera->SetPositionTargetAndUp(camPosition, camPosition + vector3(0.0f,0.0f,-1.0f));
	//m_pCamera->SetUp(vector3(0.0f, 1.0f, 0.0f));
	
	//Is the first person camera active?
	CameraRotation();
	//camDirection = (m_pCamera->GetTarget() - m_pCamera->GetPosition());
	
	//Add objects to the Manager
	for (int j = -50; j < 50; j += 2)
	{
		for (int i = -50; i < 50; i += 2)
		{
			m_pMyMeshMngr->AddConeToRenderList(glm::translate(vector3(i, 0.0f, j)));
		}
	}
}
void Application::Display(void)
{
	//Clear the screen
	ClearScreen();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//Render the list of MyMeshManager
	m_pMyMeshMngr->Render();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the MyMeshManager list
	m_pMyMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release the singleton
	MyMeshManager::ReleaseInstance();

	//release the camera
	SafeDelete(m_pCamera);

	//release GUI
	ShutdownGUI();
}
