#include "fstream"		// Filestream
// #include <windows.h>
// #include <gl\gl.h>		// Header File For The OpenGL32 Library
// #include <gl\glu.h>		// Header File For The GLu32 Library
#include <vector>

#include "GLEngine.hpp"
#include "Math.hpp" // Math must be after GLEngine because GLEngine includes windows.h, which probably includes math which in turn is needed in Math.hpp
#include "Structs.hpp"
#include "Matrix.hpp"
#include "Texture.hpp"

#include "Model.hpp"

Model::Model(
  const char* sPath
)
{
  strcpy_s(m_sName, sizeof(m_sName), "Unknown");
  boImport3ds(sPath);

  // Initialize collision circle radius
  Vector3f
    boxExtent(m_collisionBox.m_p1, m_collisionBox.m_p2);
  boxExtent[Y] = 0; // Since we want the XZ extent
  m_fCollCircleRadius = boxExtent.fMagnitude()/2;
}

bool Model::boImport3ds(
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
#if 0
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
#endif
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

      if(strcmp(mat.sName, "colbox") != 0)
        m_materials.push_back(mat);
      break;
    }

    // Texture map chunk
    case 0xA200: // Another parent chunk that must not be jumped
      break;

    // Texturemap filename
    case 0xA300: // The texturemap of the material
    {
      int
        i = 0;
      char
        sFileName[12 + 1];

      do  // Read each character of the name until we come to the end
      {
        ifs.read(&tmpChar, 1);
        sFileName[i] = tmpChar;
        i++;
      } while(tmpChar != '\0' && i < (12+1));

      // Load texture
      if(strcmp(sFileName, "colbox") != 0)
        m_materials.back().pTexture = new Texture(sFileName, m_materials.back().sName);

      break;
    }

    // Object chunk
    case 0x4000: // The mesh name
    {
      int
        i = 0;

      do  // Read each character of the name until we come to the end
      {
        ifs.read(&tmpChar, 1);
        name[i] = tmpChar;
        i++;
      } while(tmpChar != '\0' && i < 20);

			if(strcmp(name, "colbox") != 0) // The collisionbox models are named "colbox"
				vSetName(name);
      break;
    }

    // Triangular mesh chunk
    case 0x4100:  // Another parent chunk that must not be jumped
      break;

    // Vertices list chunk
    case 0x4110:  // List of vertices
    {
			Point
        point,
				minCorner(FLT_MAX, FLT_MAX, FLT_MAX),
        maxCorner(-FLT_MAX, -FLT_MAX, -FLT_MAX);
			std::vector<Point>
				vertList;

      ifs.read((char*)&quantity, sizeof(unsigned short));

			if(strcmp(name, "colbox") == 0)	// If it is a collisionbox, we only need 8 vertices
			{
				for (int i = 0; i < 8; i++)	// NB! RESET PIVOT IN 3DS MAX, OR THESE POINTS WILL BE WRONG
				{
					ifs.read((char*)&point[X], sizeof(float));
					ifs.read((char*)&point[Y], sizeof(float));
					ifs.read((char*)&point[Z], sizeof(float));
					
          if(point[X] <= minCorner[X] && point[Y] <= minCorner[Y] && point[Z] <= minCorner[Z])
            minCorner = point;
          if(point[X] >= maxCorner[X] && point[Y] >= maxCorner[Y] && point[Z] >= maxCorner[Z])
            maxCorner = point;
				}

        m_collisionBox.m_p1 = minCorner;
        m_collisionBox.m_p2 = maxCorner;
      }
      else
      {
        for (int i = 0; i < quantity; i++)
        {
          ifs.read((char*)&point[X], sizeof(float));
          ifs.read((char*)&point[Y], sizeof(float));
          ifs.read((char*)&point[Z], sizeof(float));
          m_vertices.push_back(point);
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
         m_triangles.push_back(triangle);
      }
      break;
    }

    case 0x4130:  // MSH_MAT_GROUP
    {
      int
        i = 0;
      char
        tmpName[16+1];

      do  // Read each character of the name until we come to the end
      {
        ifs.read(&tmpChar, 1);
        tmpName[i] = tmpChar;
        i++;
      } while(tmpChar != '\0' && i < (16+1));

      // Find the material
      material
        *pMat = pFindMaterial(tmpName);

      ifs.read((char*)&(*pMat).iNrFaces, 2);  // Read the number of faces this material covers

      (*pMat).sIndices = new unsigned short[(*pMat).iNrFaces];  // Initialize sIndices

      for(int i = 0; i < (*pMat).iNrFaces; i++)
        ifs.read((char*)&(*pMat).sIndices[i], sizeof(unsigned short));         // Read the triangle/face indices

      //m_materials.push_back(mat); // Add the material to the mesh
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
        m_mapcoords.push_back(texCoord);
      }
      break;
    }

    default:  // If this is a chunk we do not want/need we jump to the next chunk
      ifs.seekg(chunkSize-6, SEEK_CUR);
    }
  }
  ifs.close();  // Close the file stream
  return 1;   // Return ok
}

void Model::vDrawModel(
  const Point &pos,
  const Vector3f rotation
)
{
  glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

  std::vector<Point>
    vertices = m_vertices;
  std::vector<mapcoord>
    mapcoords = m_mapcoords;
  std::vector<triangleByIndex>
    triangles = m_triangles;
  std::vector<material>
    materials = m_materials;
  Matrix
    transfMat;

#if 1 // Draw circle for testing

  GLfloat
    radians,
    fCosVal,
    fSinVal;

  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex3f(pos[X], 0, pos[Z]);

    for(int i = 0; i <= 360; i++)
    {
      radians = DegreesToRads(rotation[Y]+(i));

      fCosVal = cos(radians);
      fSinVal = sin(radians);
      if(i%8 == 0)
        glVertex3f(pos[X] + (fCosVal*m_fCollCircleRadius), 0, pos[Z] + (fSinVal*m_fCollCircleRadius));
    }
    
  glEnd();

  glEnable(GL_TEXTURE_2D);

#endif

#if 1
  transfMat.vRotateY(vertices, -rotation[Y], Point(0, 0, 0));

  for each(material mat in materials)
    for(unsigned int i = 0; i < mat.iNrFaces; i++)
    {
      int
        faceInd = mat.sIndices[i];  // The current face index

      glBindTexture(GL_TEXTURE_2D, mat.pTexture->iTexIDGet()); // Select Our Texture

      // Draw the model
      glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 1.0f);
        // Triangle i, vertex a/b/c

        // Vertex a
        glTexCoord2f(mapcoords[triangles[faceInd].a].u,
                      mapcoords[triangles[faceInd].a].v);
        glVertex3f(vertices[triangles[faceInd].a][X] + pos[X],
                    vertices[triangles[faceInd].a][Y] + pos[Y],
                    vertices[triangles[faceInd].a][Z] + pos[Z]);

        // Vertex b
        glTexCoord2f(mapcoords[triangles[faceInd].b].u,
                      mapcoords[triangles[faceInd].b].v);
        glVertex3f(vertices[triangles[faceInd].b][X] + pos[X],
                    vertices[triangles[faceInd].b][Y] + pos[Y],
                    vertices[triangles[faceInd].b][Z] + pos[Z]);

        // Vertec c
        glTexCoord2f(mapcoords[triangles[faceInd].c].u,
                      mapcoords[triangles[faceInd].c].v);
        glVertex3f(vertices[triangles[faceInd].c][X] + pos[X],
                    vertices[triangles[faceInd].c][Y] + pos[Y],
                    vertices[triangles[faceInd].c][Z] + pos[Z]);
      glEnd();
    }
#endif

#if 0
    lineSegment
      colBox = m_collisionBox;

    transfMat.vRotateY(colBox.m_p1, -fRotationY, Point(0, 0, 0));
    transfMat.vRotateY(colBox.m_p2, -fRotationY, Point(0, 0, 0));

    // Draw colbox
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex3f(pos[X] + colBox.m_p1[X], pos[Y] + colBox.m_p1[Y], pos[Z] + colBox.m_p1[Z]);
    glVertex3f(pos[X] + colBox.m_p2[X], pos[Y] + colBox.m_p2[Y], pos[Z] + colBox.m_p2[Z]);
    glEnd();

    glEnable(GL_TEXTURE_2D);
#endif
  glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

material *Model::pFindMaterial(
  const char* sName
)
{
  for(unsigned int i = 0; i < m_materials.size(); i++)
    if(strcmp(sName, m_materials[i].sName) == 0)
      return &m_materials[i];

  return 0;
}