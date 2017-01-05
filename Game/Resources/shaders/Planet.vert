#version 330

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexcoord;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 fragmentTexcoord;

out vec3 fragmentPositionRelative;
out vec3 fragmentNormalRelative;

uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

void main()
{
	fragmentPosition = (modelMatrix * vec4(vertexPosition, 1.0)).xyz;
	fragmentNormal = (modelMatrix * vec4(vertexNormal, 0.0)).xyz;
	fragmentTexcoord = vertexTexcoord;

	fragmentPositionRelative = vertexPosition;
	fragmentNormalRelative = vertexNormal;
	
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);
}