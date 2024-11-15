#pragma once

#include <string>
#include "Transform.h"
#include "Mesh.h"
#include "RigidBody.h"

using namespace std;


class GameObject
{
public:

	GameObject(string type, Geometry geometry, Material material);
	~GameObject();

	string GetType() const { return _type; }

	void SetParent(GameObject* parent) { _parent = parent; }

	Transform* GetTransform() { return _transform; }
	Mesh* GetMesh() { return _mesh; }
	RigidBody* GetRigidBody() { return _RigidBody; }


	void Update(float dt);
	void Draw(ID3D11DeviceContext* pImmediateContext);

private:
	Transform* _transform;
	Mesh* _mesh;

	GameObject* _parent = nullptr;
	RigidBody* _RigidBody;
	string _type;


};

