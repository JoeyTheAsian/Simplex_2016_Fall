#ifndef _MYOCTANT_H_
#define _MYOCTANT_H_

#include "MyEntityManager.h"

namespace Simplex
{
//System class
class MyOctant
{
		static uint m_uOctantCount; //total # of octs
		static uint m_uMaxLevel; //max tree depth
		static uint m_uIdealEntityCount; //max entities per oct

		uint m_uID = 0; //oct id
		uint m_uLevel = 0; //current tree dpeth
		uint m_uChildren = 0; //# of child nodes
		
		float m_fSize = 0.0f; //world size of the octant

		MeshManager* m_pMeshManager = nullptr;
		MyEntityManager* m_pEntityManager = nullptr;

		vector3 m_v3Center = vector3(0.0f);//center pt
		vector3 m_v3Min = vector3(0.0f);//min pt
		vector3 m_v3Max = vector3(0.0f);//max pt


		MyOctant* m_pParent = nullptr;//stores parent node
		MyOctant* m_pChild[8];//stores children

		std::vector<uint> m_EntityList; //list of entities inside oct

		MyOctant* m_pRoot = nullptr; //root node
		//std::vector<MyOctant*> m_lChild; //list of nodes that contain objects (this will be applied to root only)

	public:
		
		MyOctant(uint a_uMaxLevel, uint a_uIdealEntityCount = 8);

		MyOctant(MyOctant* a_pParent, vector3 a_v3Center, float a_fSize, uint a_uMaxLevel);

		//MyOctant(vector3 a_v3Center, float a_fSize);
		//MyOctant(MyOctant const& other);
		//MyOctant& operator=(MyOctant const& other);

		~MyOctant();

		//void Swap(MyOctant& other);

		float GetSize();

		vector3 GetCenterGlobal();

		vector3 GetMinGlobal();

		vector3 GetMaxGlobal();
		
		//checks if object is inside octant
		bool IsColliding(uint a_uIndex);

		//Display octtree recursively
		void Display();

		//Displays specific oct
		void Display(uint a_uIndex);
		
		//void DisplayLeafs(vector3 a_v3Color = C_YELLOW);
		
		//Clears entity list
		void ClearEntityList();

		void Subdivide();
		

		//Returns the child octant specified (0-7)
		MyOctant* GetChild(uint a_uIndex);

		//Returns the parent octant of this octant
		MyOctant* GetParent();

		//true if the octant has no children
		bool IsLeaf();

		//bool ContainsMoreThan(uint a_nEntities);

		//Deletes all octants in the octree
		//Used in the destructor to avoid memory leaks
		void KillBranches();

		//Constructs a tree according to the max level
		void ConstructTree(uint a_uLevel);

		//Gives an entity in the scene an octant ID
		void AssignIDtoEntity();

		//Returns total number of octants created
		uint GetOctantCount();
	/*private:
		void Release(void);

		void Init(void);

		void ConstructList(void);*/
	};

}




#endif // !_MYOCTANT_H_
