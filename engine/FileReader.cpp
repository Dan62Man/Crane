#include "FileReader.h"

map<string, Material*> materials;

FileReader::FileReader(const char* fileName)
{
    file = fopen(fileName, "rb");
}

FileReader::~FileReader()
{
    fclose(file);
    cout << "Closed file.ovo and destroyed FILE_READER object" << endl;
}

Node* FileReader::read()
{
    if (file == nullptr)
    {
        cout << "ERROR: unable to open file" << endl;
        return nullptr;
    }

    Node* root = recursiveLoading();
    return root;
}

Node* FileReader::recursiveLoading()
{
    // Configure stream (2 decimals + Avoid scientific notation):
    cout.precision(2);
    cout << fixed;

    // Parse chuncks:	
    unsigned int chunkId, chunkSize;

    fread(&chunkId, sizeof(unsigned int), 1, file);
    fread(&chunkSize, sizeof(unsigned int), 1, file);

    // Load whole chunk into memory
    char* data = new char[chunkSize];
    if (fread(data, sizeof(char), chunkSize, file) != chunkSize) {
        cout << "ERROR: unable to read from file" << endl;
        fclose(file);
        delete[] data;
    }

    // Parse chunk information according to its type:
    unsigned int position = 0;

    switch ((OvObject::Type)chunkId)
    {

        case OvObject::Type::OBJECT:
        {
            unsigned int versionId;
            memcpy(&versionId, data + position, sizeof(unsigned int));
            position += sizeof(unsigned int);
            return recursiveLoading();
        }
        break;


        case OvObject::Type::NODE:
        {
           // Node name:
            char nodeName[FILENAME_MAX];
            strcpy(nodeName, data + position);
            position += (unsigned int)strlen(nodeName) + 1;

            // Node matrix:
            glm::mat4 matrix;
            memcpy(&matrix, data + position, sizeof(glm::mat4));
            position += sizeof(glm::mat4);

            // Nr. of children nodes:
            unsigned int children;
            memcpy(&children, data + position, sizeof(unsigned int));
            position += sizeof(unsigned int);
            
            // Optional target node, [none] if not used:
            char targetName[FILENAME_MAX];
            strcpy(targetName, data + position);
            position += (unsigned int)strlen(targetName) + 1;

            Node* node = new Node(nodeName, matrix);
            
            cout << "[NODE] : " << node->getName() << " , id: " << node->getId() << " , size: " << chunkSize << endl;
            
            recursiveLoadingChildren(node, children);

            return node;
        }


        case OvObject::Type::MESH:
        case OvObject::Type::SKINNED:
        {
            // Both standard and skinned meshes are handled through this case:
            bool isSkinned = false;
            if ((OvObject::Type)chunkId == OvObject::Type::SKINNED)
                isSkinned = true;

            // Mesh name:
            char meshName[FILENAME_MAX];
            strcpy(meshName, data + position);
            position += (unsigned int)strlen(meshName) + 1;

            // Mesh matrix:
            glm::mat4 matrix;
            memcpy(&matrix, data + position, sizeof(glm::mat4));
            position += sizeof(glm::mat4);

            // Mesh nr. of children nodes:
            unsigned int children;
            memcpy(&children, data + position, sizeof(unsigned int));
            position += sizeof(unsigned int);

            // Optional target node, or [none] if not used:
            char targetName[FILENAME_MAX];
            strcpy(targetName, data + position);
            position += (unsigned int)strlen(targetName) + 1;

            // Mesh subtype (see OvMesh SUBTYPE enum):
            unsigned char subtype;
            memcpy(&subtype, data + position, sizeof(unsigned char));
            char subtypeName[FILENAME_MAX];
            switch ((OvMesh::Subtype)subtype)
            {
            case OvMesh::Subtype::DEFAULT: strcpy(subtypeName, "standard"); break;
            case OvMesh::Subtype::NORMALMAPPED: strcpy(subtypeName, "normal-mapped"); break;
            case OvMesh::Subtype::TESSELLATED: strcpy(subtypeName, "tessellated"); break;
            default: strcpy(subtypeName, "UNDEFINED");
            }
            position += sizeof(unsigned char);
            
            // Material name, or [none] if not used:
            char materialName[FILENAME_MAX];
            strcpy(materialName, data + position);
            position += (unsigned int)strlen(materialName) + 1;

            // Mesh bounding sphere radius:
            float radius;
            memcpy(&radius, data + position, sizeof(float));
            position += sizeof(float);

            // Mesh bounding box minimum corner:
            glm::vec3 bBoxMin;
            memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
            position += sizeof(glm::vec3);

            // Mesh bounding box maximum corner:
            glm::vec3 bBoxMax;
            memcpy(&bBoxMax, data + position, sizeof(glm::vec3));
            position += sizeof(glm::vec3);

            // Optional physics properties:
            unsigned char hasPhysics;
            memcpy(&hasPhysics, data + position, sizeof(unsigned char));
            position += sizeof(unsigned char);
            if (hasPhysics)
            {
                struct PhysProps
                {
                    // Pay attention to 16 byte alignement (use padding):      
                    unsigned char type;
                    unsigned char contCollisionDetection;
                    unsigned char collideWithRBodies;
                    unsigned char hullType;

                    // Vector data:
                    glm::vec3 massCenter;

                    // Mesh properties:
                    float mass;
                    float staticFriction;
                    float dynamicFriction;
                    float bounciness;
                    float linearDamping;
                    float angularDamping;
                    unsigned int nrOfHulls;
                    unsigned int _pad;

                    // Pointers:
                    void* physObj;
                    void* hull;
                };

                PhysProps mp;
                memcpy(&mp, data + position, sizeof(PhysProps));
                position += sizeof(PhysProps);

                // Custom hull(s) used?
                if (mp.nrOfHulls)
                {
                    for (unsigned int c = 0; c < mp.nrOfHulls; c++)
                    {
                        // Hull number of vertices:
                        unsigned int nrOfVertices;
                        memcpy(&nrOfVertices, data + position, sizeof(unsigned int));
                        position += sizeof(unsigned int);

                        // Hull number of faces:
                        unsigned int nrOfFaces;
                        memcpy(&nrOfFaces, data + position, sizeof(unsigned int));
                        position += sizeof(unsigned int);

                        // Hull centroid:
                        glm::vec3 centroid;
                        memcpy(&centroid, data + position, sizeof(glm::vec3));
                        position += sizeof(glm::vec3);

                        // Iterate through hull vertices:
                        for (unsigned int c = 0; c < nrOfVertices; c++)
                        {
                            // Vertex coords:    
                            glm::vec3 vertex;
                            memcpy(&vertex, data + position, sizeof(glm::vec3));
                            position += sizeof(glm::vec3);
                        }

                        // Iterate through hull faces:
                        for (unsigned int c = 0; c < nrOfFaces; c++)
                        {
                            unsigned int face[3];
                            memcpy(face, data + position, sizeof(unsigned int) * 3);
                            position += sizeof(unsigned int) * 3;
                        }
                    }
                }
            }

            Mesh* mesh = new Mesh(meshName, matrix, materials[materialName]);

            vector<vector<Vertex*>> LODVectorVertex;
            vector<Vertex*> vertexList;
            std::map<unsigned int, Vertex*> allVertex;

            // Nr. of LODs:
            unsigned int LODs;
            memcpy(&LODs, data + position, sizeof(unsigned int));
            position += sizeof(unsigned int);

            // For each LOD...:
            vector<unsigned int> verticesPerLOD(LODs); 
            for (unsigned int l = 0; l < LODs; l++)
            {
                // Nr. of vertices:
                unsigned int vertices, faces;
                memcpy(&vertices, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);
                verticesPerLOD[l] = vertices;

                // ...and faces:
                memcpy(&faces, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);

                // Interleaved and compressed vertex/normal/UV/tangent data:                    
                for (unsigned int c = 0; c < vertices; c++)
                {
                    // Vertex coords:    
                    glm::vec3 vertex;
                    memcpy(&vertex, data + position, sizeof(glm::vec3));
                    position += sizeof(glm::vec3);

                    // Vertex normal:
                    unsigned int normalData;
                    memcpy(&normalData, data + position, sizeof(unsigned int));
                    position += sizeof(unsigned int);

                    // Texture coordinates:
                    unsigned int textureData;
                    memcpy(&textureData, data + position, sizeof(unsigned int));
                    position += sizeof(unsigned int);

                    // Tangent vector:
                    unsigned int tangentData;
                    memcpy(&tangentData, data + position, sizeof(unsigned int));
                    position += sizeof(unsigned int);

                    allVertex[c] = new Vertex(vertex, glm::unpackSnorm3x10_1x2(normalData), glm::unpackHalf2x16(textureData));
                }

                // Faces:
                for (unsigned int c = 0; c < faces; c++)
                {
                    // Face indexes:
                    unsigned int face[3];
                    memcpy(face, data + position, sizeof(unsigned int) * 3);
                    position += sizeof(unsigned int) * 3;

                    vertexList.push_back(allVertex[face[0]]);
					vertexList.push_back(allVertex[face[1]]);
					vertexList.push_back(allVertex[face[2]]);
                }
            }

            LODVectorVertex.push_back(vertexList);
            vector<Vertex*> firstLODVertex = LODVectorVertex[0];
            for (int v = 0; v < firstLODVertex.size(); v++) {
                mesh->addVertex(firstLODVertex[v]);
            }

            // Extra information for skinned meshes:
            if (isSkinned)
            {
                // Initial mesh pose matrix:               
                glm::mat4 poseMatrix;
                memcpy(&poseMatrix, data + position, sizeof(glm::mat4));
                position += sizeof(glm::vec4);

                // Bone list:
                unsigned int nrOfBones;
                memcpy(&nrOfBones, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);

                // For each bone...:
                for (unsigned int c = 0; c < nrOfBones; c++)
                {
                    // Bone name:
                    char boneName[FILENAME_MAX];
                    strcpy(boneName, data + position);
                    position += (unsigned int)strlen(boneName) + 1;

                    // Initial bone pose matrix (already inverted):
                    glm::mat4 boneMatrix;
                    memcpy(&boneMatrix, data + position, sizeof(glm::mat4));
                    position += sizeof(glm::mat4);
                }

                // For each LOD...:
                for (unsigned int l = 0; l < LODs; l++)
                {
                    // Per vertex bone weights and indexes:               
                    for (unsigned int c = 0; c < verticesPerLOD[l]; c++)
                    {
                        // Bone indexes:
                        unsigned int boneIndex[4];
                        memcpy(boneIndex, data + position, sizeof(unsigned int) * 4);
                        position += sizeof(unsigned int) * 4;

                        // Bone weights:
                        unsigned short boneWeightData[4];
                        memcpy(boneWeightData, data + position, sizeof(unsigned short) * 4);
                        position += sizeof(unsigned short) * 4;
                    }
                }
            }

            recursiveLoadingChildren(mesh, children);

            cout << "[MESH] : " << mesh->getName() << " , id: " << mesh->getId() << " , size: " << chunkSize << " , [MATERIAL] : " << materialName << endl;

            return mesh;
        }


        case OvObject::Type::LIGHT:
        {
            // Light name:
            char lightName[FILENAME_MAX];
            strcpy(lightName, data + position);
            position += (unsigned int)strlen(lightName) + 1;

            // Light matrix:
            glm::mat4 matrix;
            memcpy(&matrix, data + position, sizeof(glm::mat4));
            position += sizeof(glm::mat4);

            // Nr. of children nodes:
            unsigned int children;
            memcpy(&children, data + position, sizeof(unsigned int));
            position += sizeof(unsigned int);

            // Optional target node name, or [none] if not used:
            char targetName[FILENAME_MAX];
            strcpy(targetName, data + position);
            position += (unsigned int)strlen(targetName) + 1;

            // Light subtype (see OvLight SUBTYPE enum):
            unsigned char subtype;
            memcpy(&subtype, data + position, sizeof(unsigned char));
            char subtypeName[FILENAME_MAX];
            switch ((OvLight::Subtype)subtype)
            {
            case OvLight::Subtype::DIRECTIONAL: strcpy(subtypeName, "directional"); break;
            case OvLight::Subtype::OMNI: strcpy(subtypeName, "omni"); break;
            case OvLight::Subtype::SPOT: strcpy(subtypeName, "spot"); break;
            default: strcpy(subtypeName, "[UNDEFINED]");
            }
            position += sizeof(unsigned char);

            // Light color:
            glm::vec3 color;
            memcpy(&color, data + position, sizeof(glm::vec3));
            position += sizeof(glm::vec3);

            // Influence radius:
            float radius;
            memcpy(&radius, data + position, sizeof(float));
            position += sizeof(float);

            // Direction:
            glm::vec3 direction;
            memcpy(&direction, data + position, sizeof(glm::vec3));
            position += sizeof(glm::vec3);

            // Cutoff:
            float cutoff;
            memcpy(&cutoff, data + position, sizeof(float));
            position += sizeof(float);

            // Exponent:
            float spotExponent;
            memcpy(&spotExponent, data + position, sizeof(float));
            position += sizeof(float);

            // Cast shadow flag:
            unsigned char castShadows;
            memcpy(&castShadows, data + position, sizeof(unsigned char));
            position += sizeof(unsigned char);

            // Volumetric lighting flag:
            unsigned char isVolumetric;
            memcpy(&isVolumetric, data + position, sizeof(unsigned char));
            position += sizeof(unsigned char);

            
            Light* light = nullptr;
            
            switch ((OvLight::Subtype)subtype) {
                case OvLight::Subtype::DIRECTIONAL:
                {
                    light = new DirectionalLight(lightName, matrix, color);
                    break;
                }
                case OvLight::Subtype::OMNI:
                {
                    light = new OmniLight(lightName, matrix, color, cutoff);
                    break;
                }
                case OvLight::Subtype::SPOT:
                {
                    light = new SpotLight(lightName, matrix, color, cutoff, direction);
                    break;
                }
                default:
                {
                    cout << "Subtype not found: light ignored" << endl;
                }
            }
           
            if (light != nullptr && light->getIsAvailable())
            {
                cout << "[LIGHT] : " << light->getName() << " , id: " << light->getId() << " , size: " << chunkSize << endl;
                recursiveLoadingChildren(light, children);
            }

            return light;
        }


        case OvObject::Type::MATERIAL:
        {
            // Material name:
            char materialName[FILENAME_MAX];
            strcpy(materialName, data + position);
            position += (unsigned int)strlen(materialName) + 1;

            // Material term colors, starting with emissive:
            glm::vec3 emission;
            memcpy(&emission, data + position, sizeof(glm::vec3));
            position += sizeof(glm::vec3);

            // Albedo:
            glm::vec3 albedo;
            memcpy(&albedo, data + position, sizeof(glm::vec3));
            position += sizeof(glm::vec3);

            // Roughness factor:
            float roughness;
            memcpy(&roughness, data + position, sizeof(float));
            position += sizeof(float);

            // Metalness factor:
            float metalness;
            memcpy(&metalness, data + position, sizeof(float));
            position += sizeof(float);

            // Transparency factor:
            float alpha;
            memcpy(&alpha, data + position, sizeof(float));
            position += sizeof(float);

            // Albedo texture filename, or [none] if not used:
            char textureName[FILENAME_MAX];
            strcpy(textureName, data + position);
            position += (unsigned int)strlen(textureName) + 1;

            // Normal map filename, or [none] if not used:
            char normalMapName[FILENAME_MAX];
            strcpy(normalMapName, data + position);
            position += (unsigned int)strlen(normalMapName) + 1;

            // Height map filename, or [none] if not used:
            char heightMapName[FILENAME_MAX];
            strcpy(heightMapName, data + position);
            position += (unsigned int)strlen(heightMapName) + 1;

            // Roughness map filename, or [none] if not used:
            char roughnessMapName[FILENAME_MAX];
            strcpy(roughnessMapName, data + position);
            position += (unsigned int)strlen(roughnessMapName) + 1;

            // Metalness map filename, or [none] if not used:
            char metalnessMapName[FILENAME_MAX];
            strcpy(metalnessMapName, data + position);
            position += (unsigned int)strlen(metalnessMapName) + 1;

            string none = "[none]";
            int lengthToCompare = none.length();

            Texture* texture = nullptr;
            if (std::strncmp(textureName, none.c_str(), lengthToCompare) != 0)
            {
                texture = new Texture(textureName);
                texture->LoadBitmapFromFile();
            }

            Material* material = new Material(materialName, emission, albedo, roughness, texture);
            materials[materialName] = material;

            cout << "[MATERIAL] : " << materialName << " , id: " << material->getId() << " , size: " << chunkSize << " , [TEXTURE] : " << textureName << endl;

            return recursiveLoading();
        }

        default:
            cout << "UNKNOWN]" << endl;
            cout << "ERROR: corrupted or bad data in file " << endl;
            fclose(file);
            delete[] data;
            return nullptr;
    }
}

void FileReader::recursiveLoadingChildren(Node* parent, int nrOfChildren) {
   if (nrOfChildren > 0) {
        if (parent->getNumberOfChildren() < nrOfChildren) {
            Node* childNode = recursiveLoading();
            parent->attachChild(childNode);
            recursiveLoadingChildren(parent, nrOfChildren);
        }
    }
}