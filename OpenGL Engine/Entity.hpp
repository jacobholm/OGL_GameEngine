#ifndef ENTITY_H
#define ENTITY_H

class CollisionBox;

// An entity is an actual object in the game(wall, weapon, tree etc..)
class Entity : public Model
{
	std::vector<mapcoord>
		m_mapcoords;  // UV Texture mapping coordinates.
	                // NB! The vertices and mapcoords list are in sync(i.e. vertices[i] have mapcoords[i])

  CollisionBox  // NB! To be removed, should only use regular Model class instance
		m_mainCollisionMesh;  // The main collision mesh encompassing the entire model
  std::vector<CollisionBox>
    m_collisionMeshes;    // All "sub" collision meshes, e.g. for the arms, legs etc of a player
  std::vector<Texture>
    m_textures;           // All the textures assigned to the model

public:

  bool boImport3ds(   // Import a 3ds model
    const char* sPath // The complete path to the file
  );                  // Returns a bool indicating whether the load was successful or not

	std::vector<mapcoord>& getMapcoords( // Return the mapcoords Vector3f
	)
	{
		return m_mapcoords;
	}

	

	std::vector<Texture>& getTextures(
		)
	{
		return m_textures;
	}

	void vAddTexture(
		Texture texture
	)
	{
		m_textures.push_back(texture);
	}
};

#endif