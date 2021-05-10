#include "DataStructure/Graph.h"
namespace Core
{

}

Core::DataStructure::Graph::Graph(LowRenderer::Model* model, float radius, vec3 localCenter, Core::Maths::vec4 color)
{
	m_model = model;
	m_radius = radius;
	m_localCenter = localCenter;
	m_color = color;
	m_parent = nullptr;
	m_modelScale = vec3{ 1.f, 1.f, 1.f };
}

Core::DataStructure::Graph::~Graph()
{
	m_children.clear();
}

void Core::DataStructure::Graph::AddChild(Graph* scene)
{
	m_children.push_back(scene);
	scene->m_parent = this;
}

void Core::DataStructure::Graph::Update(float msec)
{
	if (m_parent)
	{
		m_worldTransform = m_parent->m_worldTransform * m_transform;
	}
	else
	{ // Root node , world transform is local transform !
		m_worldTransform = m_transform;
	}
	for (auto i = m_children.begin(); i != m_children.end(); ++i)
	{
		(*i)->Update(msec);
	}
}

void Core::DataStructure::Graph::Draw()
{
	if (m_model)
	{
		m_model->Draw();
	}
}
