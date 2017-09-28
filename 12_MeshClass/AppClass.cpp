#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Make MyMesh object
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(2.0f, C_RED);

	//Make MyMesh object
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateCube(1.0f, C_WHITE);


	//create space invader
	m_m4Object1[1] *= glm::translate(vector3(0.00f, 2.0f, 0.0f));
	m_m4Object1[2] *= glm::translate(vector3(0.00f, 4.0f, 0.0f));
	m_m4Object1[3] *= glm::translate(vector3(0.00f, 6.0f, 0.0f));

	m_m4Object1[4] *= glm::translate(vector3(-2.00f, 2.0f, 0.0f));
	m_m4Object1[5] *= glm::translate(vector3(-2.00f, 4.0f, 0.0f));
	m_m4Object1[6] *= glm::translate(vector3(-2.00f, 6.0f, 0.0f));
	m_m4Object1[7] *= glm::translate(vector3(-2.00f, 0.0f, 0.0f));
	m_m4Object1[8] *= glm::translate(vector3(-2.00f, -4.0f, 0.0f));

	m_m4Object1[9] *= glm::translate(vector3(-4.00f, 2.0f, 0.0f));
	m_m4Object1[10] *= glm::translate(vector3(-4.00f, 6.0f, 0.0f));
	m_m4Object1[11] *= glm::translate(vector3(-4.00f, 0.0f, 0.0f));
	m_m4Object1[12] *= glm::translate(vector3(-4.00f, 8.0f, 0.0f));
	m_m4Object1[13] *= glm::translate(vector3(-4.00f, 8.0f, 0.0f));
	m_m4Object1[14] *= glm::translate(vector3(-4.00f, -4.0f, 0.0f));

	m_m4Object1[15] *= glm::translate(vector3(-6.00f, 2.0f, 0.0f));
	m_m4Object1[16] *= glm::translate(vector3(-6.00f, 4.0f, 0.0f));
	m_m4Object1[17] *= glm::translate(vector3(-6.00f, 6.0f, 0.0f));
	m_m4Object1[18] *= glm::translate(vector3(-6.00f, 0.0f, 0.0f));
	m_m4Object1[19] *= glm::translate(vector3(-6.00f, 10.0f, 0.0f));
	m_m4Object1[20] *= glm::translate(vector3(-6.00f, -2.0f, 0.0f));

	m_m4Object1[21] *= glm::translate(vector3(-8.00f, 4.0f, 0.0f));
	m_m4Object1[22] *= glm::translate(vector3(-8.00f, 2.0f, 0.0f));
	
	m_m4Object1[23] *= glm::translate(vector3(-10.00f, 0.0f, 0.0f));
	m_m4Object1[24] *= glm::translate(vector3(-10.00f, 2.0f, 0.0f));
	m_m4Object1[25] *= glm::translate(vector3(-10.00f, -2.0f, 0.0f));

	m_m4Object1[26] *= glm::translate(vector3(2.00f, 2.0f, 0.0f));
	m_m4Object1[27] *= glm::translate(vector3(2.00f, 4.0f, 0.0f));
	m_m4Object1[28] *= glm::translate(vector3(2.00f, 6.0f, 0.0f));
	m_m4Object1[29] *= glm::translate(vector3(2.00f, 0.0f, 0.0f));
	m_m4Object1[30] *= glm::translate(vector3(2.00f, -4.0f, 0.0f));

	m_m4Object1[31] *= glm::translate(vector3(4.00f, 2.0f, 0.0f));
	m_m4Object1[32] *= glm::translate(vector3(4.00f, 6.0f, 0.0f));
	m_m4Object1[33] *= glm::translate(vector3(4.00f, 0.0f, 0.0f));
	m_m4Object1[34] *= glm::translate(vector3(4.00f, 8.0f, 0.0f));
	m_m4Object1[35] *= glm::translate(vector3(4.00f, 8.0f, 0.0f));
	m_m4Object1[36] *= glm::translate(vector3(4.00f, -4.0f, 0.0f));

	m_m4Object1[37] *= glm::translate(vector3(6.00f, 2.0f, 0.0f));
	m_m4Object1[38] *= glm::translate(vector3(6.00f, 4.0f, 0.0f));
	m_m4Object1[39] *= glm::translate(vector3(6.00f, 6.0f, 0.0f));
	m_m4Object1[40] *= glm::translate(vector3(6.00f, 0.0f, 0.0f));
	m_m4Object1[41] *= glm::translate(vector3(6.00f, 10.0f, 0.0f));
	m_m4Object1[42] *= glm::translate(vector3(6.00f, -2.0f, 0.0f));

	m_m4Object1[43] *= glm::translate(vector3(8.00f, 4.0f, 0.0f));
	m_m4Object1[44] *= glm::translate(vector3(8.00f, 2.0f, 0.0f));

	m_m4Object1[45] *= glm::translate(vector3(10.00f, 0.0f, 0.0f));
	m_m4Object1[46] *= glm::translate(vector3(10.00f, 2.0f, 0.0f));
	m_m4Object1[47] *= glm::translate(vector3(10.00f, -2.0f, 0.0f));

	for (int i = 0; i < 48; i++) {
		m_m4Object1[i] *= glm::translate(vector3(-60.0f, 0.0f, -80.0f));
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//m_m4Object1 = m_m4Object1 * glm::translate(vector3(0.01f, 0.0f, 0.0f));
	//m_pMesh->Render(m4Projection, m4View, glm::translate(vector3(3.0f, 0.0f,0.0f)) * ToMatrix4(m_qArcBall));
	//m_pMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3( 3.0f, 0.0f, 0.0f)));
	for (int i = 0; i < 48; i++) {
		m_m4Object1[i] *= glm::translate(vector3(direction * .5f, 0.0f, 0.0f));
		m_pMesh->Render(m4Projection, m4View, m_m4Object1[i]);
	}
	if (timer <= 0) {
		direction *= -1;
		timer = 60 * 4;
	}
	timer--;

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
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	if (m_m4Object1 != nullptr) {
		delete m_m4Object1;
	}

	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}