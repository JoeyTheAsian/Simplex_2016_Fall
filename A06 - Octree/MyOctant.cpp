#include "MyOctant.h"
using namespace Simplex;

uint Simplex::MyOctant::m_uMaxLevel = 0;
uint Simplex::MyOctant::m_uOctantCount = 0;
uint Simplex::MyOctant::m_uIdealEntityCount = 0;

Simplex::MyOctant::MyOctant(uint a_uMaxLevel, uint a_uIdealEntityCount)
{
	m_pEntityManager = MyEntityManager::GetInstance();
	m_pMeshManager = MeshManager::GetInstance();

	m_fSize = 80.0f;
	m_uIdealEntityCount = a_uIdealEntityCount;
	m_uMaxLevel = a_uMaxLevel;

	m_uLevel = m_uID = 0;


	//Set min and max points
	m_v3Max = m_v3Center + vector3(m_fSize / 2.0f); 
	m_v3Min = m_v3Center - vector3(m_fSize / 2.0f);

	for (uint i = 0; i < 8; i++){
		m_pChild[i] = nullptr;
	}

	ConstructTree(m_uLevel);

	m_uOctantCount++;
}

Simplex::MyOctant::MyOctant(MyOctant* a_pParent, vector3 a_v3Center, float a_fSize, uint a_uLevel)
{
	m_pParent = a_pParent;
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;

	m_uLevel = a_uLevel;
	m_uID = m_uOctantCount;


	m_pEntityManager = MyEntityManager::GetInstance();
	m_pMeshManager = MeshManager::GetInstance();

	m_v3Max = m_v3Center + vector3(m_fSize / 2.0f);
	m_v3Min = m_v3Center - vector3(m_fSize / 2.0f);

	for (uint i = 0; i < 8; i++)
	{
		m_pChild[i] = nullptr;
	}

	m_uOctantCount++;

	ConstructTree(a_uLevel);
}

Simplex::MyOctant::~MyOctant()
{
	KillBranches();

	if (m_uID == 0){
		m_uOctantCount = 0;
		m_uMaxLevel = 0;
		m_uIdealEntityCount = 0;
	}
}
vector3 Simplex::MyOctant::GetCenterGlobal()
{
	return m_v3Center;
}

vector3 Simplex::MyOctant::GetMinGlobal()
{
	return m_v3Min;
}

vector3 Simplex::MyOctant::GetMaxGlobal()
{
	return m_v3Max;
}

float Simplex::MyOctant::GetSize()
{
	return m_fSize;
}

bool Simplex::MyOctant::IsColliding(uint a_uIndex)
{
	if (a_uIndex < 0 || a_uIndex >= m_pEntityManager->GetEntityCount())
	{
		return false;
	}

	vector3 min = m_pEntityManager->GetEntity(a_uIndex)->GetRigidBody()->GetMinGlobal();
	vector3 max = m_pEntityManager->GetEntity(a_uIndex)->GetRigidBody()->GetMaxGlobal();

	if (m_v3Min.x <= max.x && m_v3Max.x >= min.x && m_v3Min.y <= max.y && m_v3Max.y >= min.y && m_v3Min.z <= max.z && m_v3Max.z >= min.z)
	{
		return true;
	}
	return false;
}

void Simplex::MyOctant::Display()
{
	matrix4 m4Scale = glm::scale(vector3(m_fSize));
	matrix4 m4Translation = glm::translate(m_v3Center);
	matrix4 m4Model = m4Translation * m4Scale;
	m_pMeshManager->AddWireCubeToRenderList(m4Model, C_YELLOW, RENDER_WIRE);

	for (uint i = 0; i < m_uChildren; i++)
	{
		if(m_pChild[i]!= nullptr)
			m_pChild[i]->Display();
	}
}

void Simplex::MyOctant::Display(uint a_uIndex)
{
	//Check to see if index is valid
	if (a_uIndex < 0 || a_uIndex >= m_uOctantCount)
	{
		//Display normally
		Display();
	}

	//Display the target octant
	else
	{
		//Target octant found
		if (m_uID == a_uIndex)
		{
			//Display this octant
			matrix4 m4Scale = glm::scale(vector3(m_fSize));
			matrix4 m4Translation = glm::translate(m_v3Center);
			matrix4 m4Model = m4Translation * m4Scale;
			m_pMeshManager->AddWireCubeToRenderList(m4Model, C_YELLOW, RENDER_WIRE);
		}

		else
		{
			//Search children
			for (uint i = 0; i < m_uChildren; i++)
			{
				m_pChild[i]->Display(a_uIndex);
			}
		}
	}
}

void Simplex::MyOctant::ClearEntityList()
{
	m_EntityList.clear();
}

void Simplex::MyOctant::Subdivide()
{
	if (IsLeaf()) {
		m_uChildren = 8;
		vector3 p1 = m_v3Min;
		vector3 p2 = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
		vector3 p3 = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);
		vector3 p4 = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
		vector3 p5 = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
		vector3 p6 = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
		vector3 p7 = m_v3Max;
		vector3 p8 = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);

		vector3 center = m_v3Center;

		m_pChild[0] = new MyOctant(this, p1 - (p1 - center) / 2.0f, m_fSize / 2, m_uLevel + 1);
		m_pChild[1] = new MyOctant(this, p2 - (p2 - center) / 2.0f, m_fSize / 2, m_uLevel + 1);
		m_pChild[2] = new MyOctant(this, p3 - (p3 - center) / 2.0f, m_fSize / 2, m_uLevel + 1);
		m_pChild[3] = new MyOctant(this, p4 - (p4 - center) / 2.0f, m_fSize / 2, m_uLevel + 1);
		m_pChild[4] = new MyOctant(this, p5 - (p5 - center) / 2.0f, m_fSize / 2, m_uLevel + 1);
		m_pChild[5] = new MyOctant(this, p6 - (p6 - center) / 2.0f, m_fSize / 2, m_uLevel + 1);
		m_pChild[6] = new MyOctant(this, p7 - (p7 - center) / 2.0f, m_fSize / 2, m_uLevel + 1);
		m_pChild[7] = new MyOctant(this, p8 - (p8 - center) / 2.0f, m_fSize / 2, m_uLevel + 1);

		for (uint i = 0; i < 7; i++) {
			for (uint j = 0; j < m_EntityList.size();j++) {
				if (IsColliding(m_EntityList[j])) {
					m_pChild[i]->m_EntityList.push_back(m_EntityList[j]);
				}
			}
		}
	}
}

MyOctant * Simplex::MyOctant::GetChild(uint a_uIndex)
{
	return m_pChild[a_uIndex];
}

MyOctant * Simplex::MyOctant::GetParent()
{
	return m_pParent;
}

bool Simplex::MyOctant::IsLeaf()
{
	//Check if it has children
	if (m_uChildren != 0)
	{
		return false;
	}

	return true;
}

void Simplex::MyOctant::KillBranches()
{
	if (!IsLeaf())
	{
		for (uint i = 0; i < m_uChildren; i++)
		{
			delete m_pChild[i];
		}
	}
}

void Simplex::MyOctant::ConstructTree(uint a_uLevel)
{
	bool subdividable = false;

	//stop at max
	if (a_uLevel >= m_uMaxLevel){
		AssignIDtoEntity();
		return;
	}

	for (uint i = 0; i < m_pEntityManager->GetEntityCount(); i++){
		//add colliding entities
		if (IsColliding(i)){
			m_EntityList.push_back(i);

			//check if exceeded max entity count
			if (m_EntityList.size() >= m_uIdealEntityCount){
				subdividable = true;

				//Clear
				m_EntityList.clear();
				break;
			}
		}
	}
	
	if (subdividable){
		Subdivide();
	}
	else
	{
		//Add entity to the dimension
		for (uint i = 0; i < m_EntityList.size(); i++)
		{
			m_pEntityManager->AddDimension(m_EntityList[i], m_uID);
		}
	}
}

void Simplex::MyOctant::AssignIDtoEntity()
{
	if (IsLeaf())
	{
		for (uint i = 0; i < m_pEntityManager->GetEntityCount(); i++)
		{
			//Add colliding entities to appropriate dimension
			if (IsColliding(i))
			{
				m_pEntityManager->AddDimension(i, m_uID);
				m_EntityList.push_back(i);
			}
		}
	}
}

uint Simplex::MyOctant::GetOctantCount()
{
	return m_uOctantCount;
}
