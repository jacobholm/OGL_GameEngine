#if 0

#include "Entity.hpp"

bool Entity::boImport3ds(
  const char* sPath
)
{
  unsigned short
    chunkId,    // Id of the chunk
    quantity,   // Quantity of whatever the chunk holds(i.e. number of vertices or polygons)
    faceFlags;  // Certain attributes for faces(i.e. if they are visible or not)

  unsigned int
    chunkSize;  // The size of the chunk in bytes

  char
    tmpChar,  // Used to read in the name of the mesh object
    name[20]; // The name of the mesh object

  SubModel
    *pTmpMesh = 0;

  std::ifstream 
    ifs; // Declare input filestream

  ifs.open(sPath, std::ios_base::in | std::ios_base::binary); // Open the file
  if (!ifs)
    return 0; // If opening the file fails, return 0

  while(!ifs.eof()) // Loop to scan the whole file 
  {
   ifs.read((char*)&chunkId, 2);    // Read chunk id, 2 bytes
   ifs.read((char*)&chunkSize, 4);  // Read chunk size, 4 bytes

   // Process the data
   switch(chunkId)
   {
		// Temp
	  case 0xB020:
			{
				ifs.seekg(24, SEEK_CUR);
				float
					test;
				for(int i = 0; i < 100; i++)
					ifs.read((char*)&test, 4);
				break;
			}
		// Temp
		case 0xB000: // An "empty" parent chunk that must not be jumped
			break;
		// Temp
		case 0xB002: // An "empty" parent chunk that must not be jumped
			break;

    // Main chunk
    case 0x4D4D: // An "empty" parent chunk that must not be jumped
      break;

    // 3D editor chunk
    case 0x3D3D: // Another parent chunk that must not be jumped
      break;

    // Material chunk
    case 0xAFFF: // Another parent chunk that must not be jumped
      break;

    // Material name chunk
    case 0xA000: // The name of the material
    {
      material
        mat;

      int
        i = 0;
      do  // Read each character of the name until we come to the end
      {
        ifs.read(&tmpChar, 1);
        mat.sName[i] = tmpChar;
        i++;
      } while(tmpChar != '\0' && i < (16+1));

      m_materials.push_back(mat);
      break;
    }

    // Texture map chunk
    case 0xA200: // Another parent chunk that must not be jumped
      break;

    // Texturemap name
    case 0xA300: // The texturemap of the material
    {
      int
        i = 0;

      do  // Read each character of the name until we come to the end
      {
        ifs.read(&tmpChar, 1);
        m_materials.back().sFile[i] = tmpChar;
        i++;
      } while(tmpChar != '\0' && i < (12+1));
      break;
    }

    // Object chunk
    case 0x4000: // The mesh name
    {
			// Here we check the previous objects name, to see if it was a collisionbox or not
      if(pTmpMesh)  // Check if the object exists
      {
        if(strcmp(pTmpMesh->sGetName(), "colbox") == 0) // If there is a mesh, and its name
					m_collisionBoxes.push_back(*(CollisionBox*)pTmpMesh);         // is 'colbox', we push it into the collisionbox list
        else
					m_meshObjects.push_back(*(Entity*)pTmpMesh);						// If it is not the collision box
                                                        // we push it into the meshobject list
        delete pTmpMesh;  // Delete the pointer once we are finished with it
      }

      int
        i = 0;

      do  // Read each character of the name until we come to the end
      {
        ifs.read(&tmpChar, 1);
        name[i] = tmpChar;
        i++;
      } while(tmpChar != '\0' && i < 20);

			if(strcmp(name, "colbox") == 0) // The collisionbox models are named "colbox"
			{
				m_iTmpSize = chunkSize - (6 + i);
				pTmpMesh = new CollisionBox(name);
			}
			else
				pTmpMesh = new Entity(name);
      break;
    }

    // Triangular mesh chunk
    case 0x4100:  // Another parent chunk that must not be jumped
      break;

    // Vertices list chunk
    case 0x4110:  // List of vertices
    {
			Point
				point;
			std::vector<Point>
				vertList;

      ifs.read((char*)&quantity, sizeof(unsigned short));

			if(strcmp(pTmpMesh->sGetName(), "colbox") == 0)	// If it is a collisionbox, we only need 8 vertices
			{
				for (int i = 0; i < 8; i++)	// NB! RESET PIVOT IN 3DS MAX, OR THESE POINTS WILL BE WRONG
				{
					ifs.read((char*)&point[X], sizeof(float));
					ifs.read((char*)&point[Y], sizeof(float));
					ifs.read((char*)&point[Z], sizeof(float));
					//vertList.push_back(point);
					pTmpMesh->getVertices().push_back(point);
				}

				vertList = pTmpMesh->getVertices();

				// Calculate the boxs' axis and center
				Vector3f
					xVec,
					yVec,
					zVec;

				// The reason we divide the Vector3fs by 2 is that the Vector3fs originate from the center of the box,
				// making the magnitude of the Vector3fs half the extent of the box

				// X Vector3f
				xVec[X] = (vertList[3][X] - vertList[7][X])/2;
				xVec[Y] = (vertList[3][Y] - vertList[7][Y])/2;
				xVec[Z] = (vertList[3][Z] - vertList[7][Z])/2;

				// Y Vector3f
				yVec[X] = (vertList[6][X] - vertList[7][X])/2;
				yVec[Y] = (vertList[6][Y] - vertList[7][Y])/2;
				yVec[Z] = (vertList[6][Z] - vertList[7][Z])/2;

				// Z Vector3f
				zVec[X] = (vertList[5][X] - vertList[7][X])/2;
				zVec[Y] = (vertList[5][Y] - vertList[7][Y])/2;
				zVec[Z] = (vertList[5][Z] - vertList[7][Z])/2;

				// Reset point
				point[X] = 0;
				point[Y] = 0;
				point[Z] = 0;

				point[X] = 0;//xVec[X] + vertList[7].x;
				point[Y] = 0;//yVec[Y] + vertList[7].y;
				point[Z] = 0;//zVec[Z] + vertList[7].z;
				((CollisionBox*)pTmpMesh)->vSetCenter(point);	// Set center

				
				((CollisionBox*)pTmpMesh)->vSetVector3fs(xVec, yVec, zVec);	// Set the Vector3fs


				m_iTmpSize -= 12 + sizeof(unsigned short) + (sizeof(float)*24);
				ifs.seekg(m_iTmpSize, SEEK_CUR);	// Jump over the entire object chunk
				break;
			}
			else
			{
				for (int i = 0; i < quantity; i++)
				{
					 ifs.read((char*)&point[X], sizeof(float));
					 ifs.read((char*)&point[Y], sizeof(float));
					 ifs.read((char*)&point[Z], sizeof(float));
					 //vertList.push_back(point);
					 pTmpMesh->getVertices().push_back(point);
				}
			}
      break;
    }

    // Faces description chunk
    case 0x4120:  // List of faces, indices in the vertex list
    {
      ifs.read((char*)&quantity, sizeof(unsigned short)); 
      for (int i = 0; i < quantity; i++)
      {
        triangleByIndex
          triangle;
         ifs.read((char*)&triangle.a, sizeof(unsigned short));
         ifs.read((char*)&triangle.b, sizeof(unsigned short));
         ifs.read((char*)&triangle.c, sizeof(unsigned short));
         ifs.read((char*)&faceFlags, sizeof(unsigned short));
         ((Entity*)pTmpMesh)->getTriangles().push_back(triangle);
      }
      break;
    }

    case 0x4130:  // MSH_MAT_GROUP
    {
      int
        i = 0;
      char
        name[16+1];

      do  // Read each character of the name until we come to the end
      {
        ifs.read(&tmpChar, 1);
        name[i] = tmpChar;
        i++;
      } while(tmpChar != '\0' && i < (16+1));

      // Find the material
      material
        mat = findMaterial(name);

      ifs.read((char*)&mat.iNrFaces, 2);  // Read the number of faces this material covers

      mat.sIndices = new unsigned short[mat.iNrFaces];  // Initialize sIndices

      for(int i = 0; i < mat.iNrFaces; i++)
        ifs.read((char*)&mat.sIndices[i], sizeof(unsigned short));         // Read the triangle/face indices

      ((Entity*)pTmpMesh)->addMaterial(mat); // Add the material to the mesh
      break;
    }

    // Mapping coordinates list chunk
    case 0x4140:  // U, V mapping coordinates for textures
    {
      ifs.read((char*)&quantity, sizeof(unsigned short));
      for (int i = 0; i < quantity; i++)
      {
        mapcoord
          texCoord;
        ifs.read((char*)&texCoord.u, sizeof(float));
        ifs.read((char*)&texCoord.v, sizeof(float));
        ((Entity*)pTmpMesh)->getMapcoords().push_back(texCoord);
      }
      break;
    }

    default:  // If this is a chunk we do not want/need we jump to the next chunk
      ifs.seekg(chunkSize-6, SEEK_CUR);
    }
  }

	// If there are no more objects, we need to check if the last object that was imported was a collisionbox or not
  if(pTmpMesh)  // Check if the object exists
  {
    if(strcmp(pTmpMesh->sGetName(), "colbox") == 0) // If there is a mesh, and its name
			m_collisionBoxes.push_back(*(CollisionBox*)pTmpMesh);                 // is colbox, we set it as the collision box
    else
        m_meshObjects.push_back(*(Entity*)pTmpMesh);         // If it is not the collision box
                                                    // we push it into the Vector3f
    delete pTmpMesh;  // Delete the pointer once we are finished with it
  }
  ifs.close();  // Close the file stream
  return 1;   // Return ok
}

#endif