//OpenGL Bible sec 2 - drawing a point

#include "pch.h"
#include <GL/glew.h>
#include "shader.h"
#include "ch2.1_point.h"

namespace sb7
{
	PointTest::PointTest(const std::string& name) :
		Layer::Layer(name)
	{
	}

	void PointTest::Startup()
	{
		ShaderBuilder shader_builder("src/test_progs/opengl_bible/ch2/");
		m_shader = shader_builder.Vert("2.1.point.vs").Frag("2.1.point.fs").Build("2.1.point_shader");

		//VAO is always needed - it is an object that represents the *Vertex Fetch* stage of the pipeline and used to supply input to the vertex shader.  Still need this even if there is no input to vertex shader.  VAO aintains all state related to input to the pupeline
		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		m_shader->OutputInfo();
	}

	void PointTest::Shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(m_shader->GetProgramID());
	}

	void PointTest::OnUpdate(double now, double time_step)
	{
		glUseProgram(m_shader->GetProgramID());
		glPointSize(20.0f); //sb7 loc 1969 value supplied can be at least 64.0

		//Sends vertices into the pipeline (Vertex fetch) see sv7 loc 1159
		//Vertex shader is executed for every vertex defined
		glDrawArrays(GL_POINTS, 0, 1);
	}
}

