//OpenGL Bible Sec 3 - Passing data to vertex shader and from stage to stage


#pragma once
#include "pch.h"
#include <GL\glew.h>
#include "shader.h"
#include "ch3.1_moving_triangle.h"

namespace sb7
{

	MovingTriangle::MovingTriangle(const std::string& name) :
		Layer::Layer(name)
	{
	}

	void MovingTriangle::Startup()
	{
		ShaderBuilder shader_builder("src/test_progs/opengl_bible/ch3/");
		m_shader = shader_builder.Vert("3.1.moving_triangle.vs").Frag("3.1.moving_triangle.fs").Build("3.1.moving_triangle_shader");
		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		m_shader->OutputInfo();
	}

	void MovingTriangle::Shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(m_shader->GetProgramID());
	}

	void MovingTriangle::OnUpdate(double now, double time_step)
	{
		glUseProgram(m_shader->GetProgramID());

		//VBO previously bound for attribute location 0,1 (grid) - need to disable first otherwise glVertexAttrib4fv() gets ignored, since openGL would be expecting a VBO to provide the attribute data instead
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		const GLfloat offset[] = { (float)glm::sin(now) * 0.5f, (float)glm::cos(now) * 0.6f, 0.0f, 0.0f };

	
		const GLfloat color[] = { (float)sin(now) * 0.5f + 0.5f,
															(float)cos(now) * 0.5f + 0.5f,
															0.0f, 1.0f };

		
		//With this call, the data sent is avaiable to each vertex shader run
		glVertexAttrib4fv(0, offset);
		//glVertexAttrib4f(0, offset[0], offset[1], offset[2], offset[3]);
		glVertexAttrib4fv(1, color);
		// Draw one triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Re-enable these attributes for the grid
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

}
