#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in float _camPos;

void main()
{
    FragColor = vec4(ourColor.x+_camPos, ourColor.y+_camPos, ourColor.z+_camPos, 1.0);
}