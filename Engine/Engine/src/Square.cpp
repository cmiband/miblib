#include "Square.h"

Square::Square(const math::Vector2<float>& position, float size, const math::Vector4<float>& color, VertexArray& va) : m_size(size)
{
	m_positions = new float[8] {
		position.x, position.y,
		position.x+size, position.y,
		position.x + size,position.y + size,
		position.x, position.y+size
	};

	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};

	m_vb.AddData(4 * 2 * sizeof(float), m_positions);
	
	va.AddBuffer(2, false, 2 * sizeof(float));

	m_ib.AddData(6 * sizeof(unsigned int), indices);
	m_shader.CreatePostInitialization("res/shaders/Basic.shader");
	SetColor(m_shader, color);
}

void Square::Draw(Renderer& r, VertexArray& va)
{
	va.Bind();
	m_ib.Bind();
	m_shader.Bind();

	r.Draw(va, m_ib, m_shader);
}

void Square::UnbindPropeties() const
{
	m_vb.Unbind();
	m_ib.Unbind();
	m_shader.Unbind();
}

void Square::Move(const math::Vector2<float>& vector)
{
	ChangePositionsArray(vector);
	m_vb.Bind();
	m_vb.AddData(4 * 2 * sizeof(float), m_positions);
}

void Square::ChangePositionsArray(const math::Vector2<float>& vec)
{
	m_positions[0] = m_positions[0] + vec.x;
	m_positions[1] = m_positions[1] + vec.y;
	m_positions[2] = m_positions[2] + vec.x;
	m_positions[3] = m_positions[3] + vec.y;
	m_positions[4] = m_positions[4] + vec.x;
	m_positions[5] = m_positions[5] + vec.y;
	m_positions[6] = m_positions[6] + vec.x;
	m_positions[7] = m_positions[7] + vec.y;
}

void Square::SetColor(Shader& sh,const math::Vector4<float>& c) const
{
	sh.SetUniform4f("u_Color", c);
}
