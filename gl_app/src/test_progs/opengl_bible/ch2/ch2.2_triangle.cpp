//OpenGL Bible sec 2 - drawing a point

#include "pch.h"
#include <GL/glew.h>
#include "shader.h"
#include "ch2.2_triangle.h"

namespace sb7
{
	TriangleTest::TriangleTest(const std::string& name) :
		Layer::Layer(name)
	{
	}

	void TriangleTest::Startup()
	{
		ShaderBuilder shader_builder("src/test_progs/opengl_bible/ch2/");
		m_shader = shader_builder.Vert("2.2.triangle.vs").Frag("2.2.triangle.fs").Build("2.2.triangle_shader");

		//VAO is always needed - it is an object that represents the *Vertex Fetch* stage of the pipeline and used to supply input to the vertex shader.  Still need this even if there is no input to vertex shader.  VAO aintains all state related to input to the pupeline
		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		m_shader->OutputInfo();
	}

	void TriangleTest::Shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(m_shader->GetProgramID());
	}

	void TriangleTest::OnUpdate(double now, double time_step)
	{
		glUseProgram(m_shader->GetProgramID());

		//Sends vertices into the pipeline (Vertex fetch) see sv7 loc 1159
		//Vertex shader is executed for every vertex defined
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

}

