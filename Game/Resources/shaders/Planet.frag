#version 330

in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 fragmentTexcoord;

in vec3 fragmentPositionRelative;
in vec3 fragmentNormalRelative;

layout (location = 0) out vec4 pixelColor;

uniform sampler2D textureGrass;
uniform sampler2D textureRock;
uniform sampler2D textureSnow;

void main()
{
	float lighting = dot(-fragmentNormal, normalize(vec3(1.0, 1.0, -1.0)));

	vec3 grass = texture(textureGrass, fragmentTexcoord).xyz;
	vec3 stone = texture(textureRock, fragmentTexcoord).xyz;
	vec3 snow = texture(textureSnow, fragmentTexcoord).xyz;
	float l = length(fragmentPositionRelative) - 1024.0;
	vec3 gs = mix(grass, snow, clamp(l - 8.0, 0.0, 1.0));
	float angle = -dot(fragmentNormalRelative, normalize(fragmentPosition));
	vec3 t = mix(stone, gs, clamp(angle * angle * angle * angle * 2.0, 0.0, 1.0));

	pixelColor = vec4(t * lighting, 1.0);
}