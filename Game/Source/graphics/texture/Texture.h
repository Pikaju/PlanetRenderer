#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	void load(const char* file);

	void init();
	void cleanup();

	void bind(unsigned int slot = 0) const;
	void unbind(unsigned int slot = 0) const;
private:
	unsigned int m_id;
	int m_width;
	int m_height;
	unsigned int m_target;
};

