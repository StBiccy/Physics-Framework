#include "Mesh.h"



Mesh::Mesh(Geometry geometry, Material material) : _geometry(geometry), _material(material)
{
	_textureRV = nullptr;

}

Mesh::~Mesh()
{
	_textureRV = nullptr;
	_geometry.indexBuffer = nullptr;
	_geometry.vertexBuffer = nullptr;
}

void Mesh::Draw(ID3D11DeviceContext* pImmediateContext)
{
	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}

void Mesh::Update(float dt)
{
}
