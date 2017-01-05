#pragma once

#include <vector>

class Noise
{
public:
	Noise(unsigned int seed);
	~Noise();

	float noise(float x, float y) const;
	float noise(float x, float y, float z) const;

	float octaves(float x, float y, float z, unsigned int octaves, float frequency, float persistance) const;
	float octavesAbs(float x, float y, float z, unsigned int octaves, float frequency, float persistance) const;
protected:
	static float fade(float t);
	static float lerp(float t, float a, float b);
private:
	std::vector<int> m_p;
};

