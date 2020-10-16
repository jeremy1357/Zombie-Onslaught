#include "LevelManager.h"
#include <fstream>
#include <iostream>


LevelManager::LevelManager() {
	// Empty
}

void LevelManager::init(
	const std::string& projectDirectory, 
	SpriteRenderer& renderer, 
	TextureCache& textureCache) 
{
	m_renderer = &renderer;
	m_textureCache = &textureCache;
	m_projectDirectory = projectDirectory + "Resources\\Maps\\";
	std::string mapPath = m_projectDirectory + "map1.txt";
	std::vector <unsigned char> mapData;

	std::ifstream file(mapPath, std::ios::binary | std::ios::in);

	if (file.fail()) {
		perror(mapPath.c_str());
		return;
	}
	file.seekg(0, std::ios::end);
	// Get the size of the file
	int fileSize = file.tellg();
	// Seek back to beginning
	file.seekg(0, std::ios::beg);
	// Make sure we dont count the file header in the file size
	fileSize -= file.tellg();
	// Resize the given buffer to the filesize
	mapData.resize(fileSize);
	file.read((char*)&(mapData[0]), fileSize);
	file.close();

	int row = 0;
	m_mapData.push_back(std::vector<char>());
	for (size_t i = 0; i < mapData.size(); i++) {
		if (mapData[i] == '\n') {
			row += 1;
			m_mapData.push_back(std::vector<char>());
		}
		m_mapData[row].push_back(mapData[i]);
	}
	

	std::string imageDirectory = projectDirectory + "Resources\\Textures\\";

	GLuint poundTexture = m_textureCache->get_texture_id(imageDirectory + "Ground_01.png");
	GLuint grassTexture = m_textureCache->get_texture_id(imageDirectory + "Dirt_01.png");

	m_textureLookup.insert(std::make_pair('#', poundTexture));
	m_textureLookup.insert(std::make_pair('-', grassTexture));


	char c;

}

void LevelManager::render(glm::vec2 playerPosition, glm::vec2 windowDimensions) {
	if (m_needsRender) {
		//m_needsRender = false;
		// Verify that the renderer has been properly initialized with a non-nullptr value
		if (m_renderer == nullptr) {
			return;
		}

		glm::vec2 tileCenter(0.0f, 0.0f);
		for (auto& x : m_mapData) {
			for (auto& y : x) {
				switch (y) {
				case '#':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('#'));
					break;
				case '-':
					m_renderer->add_static_sprite_to_batch(tileCenter, get_texture_ID('-'));
					break;

				default:
					break;
					// Maybe add a texture showing ERROR
				}
				tileCenter.y += 1.0f;
			}
			tileCenter.x += 1.0f;
			tileCenter.y = 0.0f;
		}
	}

	// Go through the 2D vector and render each tile. 
	// Go of the logic that a tile in location of 0 0 (in the vector)
	// should be rendered at position x=0, y=0.
	// If 2D vector position is at 5 7, the position would be at
	// x = 5 * (width of tile) and y = 7 * (height of tile)
	// The offset variables account for the size of each tile to correctly
	// align the tile.
	//for (size_t x = 0; x < m_mapData.size(); x++) {
	//	for (size_t y = 0; y < m_mapData[x].size(); y++) {
	//		glm::vec2 tileCenter = glm::vec2(x, y);
	//		
	//		// Determine what the current character is and render its associated texture
	//		switch (m_mapData[x][y]) {
	//		case '#':
	//			m_renderer->add_sprite_to_batch(tileCenter, get_texture_ID('#'));
	//			break;
	//		case '-':
	//			m_renderer->add_sprite_to_batch(tileCenter, get_texture_ID('-'));
	//			break;

	//		default:
	//			break;
	//			// Maybe add a texture showing ERROR
	//		}
	//	}
	//}
}

void LevelManager::update() {

}

GLuint LevelManager::get_texture_ID(const char& key)
{
	std::map<char, GLuint>::iterator it = m_textureLookup.find(key);
	if (it != m_textureLookup.end()) {
		return it->second;
	}
	return 0;
}