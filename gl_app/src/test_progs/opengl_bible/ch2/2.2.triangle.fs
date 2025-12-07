//OpenGL Bible sec 2 - drawing a triangle

#version 450 core

out vec4 color;

   /*
    Note:  gl_FragCoord coords will correspond to the glViewport() setup, with (0,0) at the bottom right.  

    GLFW mouse coords will have the y value flipped compared to gl_FragCoord. i.e. (0,0) will be a the top left
   */ 

void main()
{
    color = vec4(0.0, 0.8, 1.0, 1.0);
}
