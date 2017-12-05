#pragma once

#include "MyEntityManager.h"

namespace Simplex {

class MyOctant {
	static uint m_uOctantCount;
	static uint m_uMaxLevel;
	static uint m_uIdealEntityCount;

	uint m_uID = 0;
	uint m_uLevel = 0;
	uint m_uChildren = 0;

	float m_fSize = 0.0f;

	MeshManager* m_pMeshMngr = nullptr;
	MyEntityManager* m_pEntityMngr = nullptr;

	vector3 m_v3Center = vector3(0.0f);
	vector3 m_v3Max = vector3(0.0f);
	vector3 m_v3Min = vector3(0.0f);

	MyOctant* m_Parent = nullptr;
	MyOctant* m_PChild[8];
	
	std::vector<uint> m_EntityList;

	MyOctant* m_pRoot = nullptr;
	std::vector<MyOctant*> m_lChild;
public:
	MyOctant();
	MyOctant(MyOctant*);
	MyOctant(vector3 min, vector3 max);
	void SubDivide();
	MyOctant* GetChildren();
	std::vector<uint> GetEntities();
	

};
}