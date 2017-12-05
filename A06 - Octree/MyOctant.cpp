#include "MyOctant.h"
#include "MyEntityManager.h"

namespace Simplex {

Simplex::MyOctant::MyOctant()
{
}

Simplex::MyOctant::MyOctant(MyOctant *)
{
}

Simplex::MyOctant::MyOctant(vector3 min, vector3 max)
{
	m_v3Center = min + ((max - min) / 2.0f);
}

void Simplex::MyOctant::SubDivide()
{
	vector3 p1 = m_v3Min;
	vector3 p2 = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	vector3 p3 = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);
	vector3 p4 = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	vector3 p5 = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	vector3 p6 = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	vector3 p7 = m_v3Max;
	vector3 p8 = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);

	vector3 center = m_v3Center;

	m_PChild[0] = new MyOctant(p1, center);
	m_PChild[1] = new MyOctant(p1 + ((p2 - p1) / 2.0f), p2 + ((p7 - p2) / 2.0f));
	m_PChild[2] = new MyOctant(p1 + ((p3 - p1) / 2.0f), p3 + ((p7 - p3) / 2.0f));
	m_PChild[3] = new MyOctant(p1 + ((p4 - p1) / 2.0f), p4 + ((p7 - p4) / 2.0f));
	m_PChild[4] = new MyOctant(p1 + ((p5 - p1) / 2.0f), p5 + ((p7 - p5) / 2.0f));
	m_PChild[5] = new MyOctant();
	m_PChild[6] = new MyOctant();
	m_PChild[7] = new MyOctant();

}

MyOctant * Simplex::MyOctant::GetChildren()
{
	return nullptr;
}

std::vector<uint> Simplex::MyOctant::GetEntities()
{
	return m_EntityList;
}

}