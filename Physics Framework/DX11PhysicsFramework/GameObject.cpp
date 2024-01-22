#include "GameObject.h"

GameObject::GameObject(string type, Geometry geometry, Material material) : _type(type)
{
	_parent = nullptr;
	_transform = new Transform();
	_mesh = new Mesh(geometry, material);
	_pm = new PhysicsModel(_transform);
}

GameObject::~GameObject()
{
	delete(_transform);
	_parent = nullptr;

}

void GameObject::Update(float dt)
{
	_transform->Update(dt);
	_mesh->Update(dt);
	_pm->Update(dt);
	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_transform->GetWorld(), _transform->GetWorldMatrix() * _parent->_transform->GetWorldMatrix());
	}
}



void GameObject::Draw(ID3D11DeviceContext* pImmediateContext)
{
	_mesh->Draw(pImmediateContext);
}