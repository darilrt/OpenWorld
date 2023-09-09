#include "chunk.h"

#define FACE_FRONT \
    vertices.push_back({ x       , y       , z + 1.0f }); \
    vertices.push_back({ x + 1.0f, y       , z + 1.0f }); \
    vertices.push_back({ x + 1.0f, y + 1.0f, z + 1.0f }); \
    vertices.push_back({ x       , y + 1.0f, z + 1.0f }); \
    \
    normals.push_back({ 0.0f, 0.0f, 1.0f }); \
    normals.push_back({ 0.0f, 0.0f, 1.0f }); \
    normals.push_back({ 0.0f, 0.0f, 1.0f }); \
    normals.push_back({ 0.0f, 0.0f, 1.0f }); \
    \
    uvs.push_back({ 0.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 0.0f }); \
    uvs.push_back({ 0.0f, 0.0f }); \
    \
    indices.push_back({ index, index + 1, index + 2 }); \
    indices.push_back({ index, index + 2, index + 3 }); \
    \
    index += 4;

#define FACE_BACK \
    vertices.push_back({ x       , y       , z }); \
    vertices.push_back({ x + 1.0f, y       , z }); \
    vertices.push_back({ x + 1.0f, y + 1.0f, z }); \
    vertices.push_back({ x       , y + 1.0f, z }); \
    \
    normals.push_back({ 0.0f, 0.0f, -1.0f }); \
    normals.push_back({ 0.0f, 0.0f, -1.0f }); \
    normals.push_back({ 0.0f, 0.0f, -1.0f }); \
    normals.push_back({ 0.0f, 0.0f, -1.0f }); \
    \
    uvs.push_back({ 0.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 0.0f }); \
    uvs.push_back({ 0.0f, 0.0f }); \
    \
    indices.push_back({ index, index + 2, index + 1 }); \
    indices.push_back({ index, index + 3, index + 2 }); \
    \
    index += 4;

#define FACE_LEFT \
    vertices.push_back({ x       , y       , z        }); \
    vertices.push_back({ x       , y       , z + 1.0f }); \
    vertices.push_back({ x       , y + 1.0f, z + 1.0f }); \
    vertices.push_back({ x       , y + 1.0f, z        }); \
    \
    normals.push_back({ -1.0f, 0.0f, 0.0f }); \
    normals.push_back({ -1.0f, 0.0f, 0.0f }); \
    normals.push_back({ -1.0f, 0.0f, 0.0f }); \
    normals.push_back({ -1.0f, 0.0f, 0.0f }); \
    \
    uvs.push_back({ 0.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 0.0f }); \
    uvs.push_back({ 0.0f, 0.0f }); \
    \
    indices.push_back({ index, index + 1, index + 2 }); \
    indices.push_back({ index, index + 2, index + 3 }); \
    \
    index += 4;

#define FACE_RIGHT \
    vertices.push_back({ x + 1.0f, y       , z        }); \
    vertices.push_back({ x + 1.0f, y       , z + 1.0f }); \
    vertices.push_back({ x + 1.0f, y + 1.0f, z + 1.0f }); \
    vertices.push_back({ x + 1.0f, y + 1.0f, z        }); \
    \
    normals.push_back({ 1.0f, 0.0f, 0.0f }); \
    normals.push_back({ 1.0f, 0.0f, 0.0f }); \
    normals.push_back({ 1.0f, 0.0f, 0.0f }); \
    normals.push_back({ 1.0f, 0.0f, 0.0f }); \
    \
    uvs.push_back({ 0.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 0.0f }); \
    uvs.push_back({ 0.0f, 0.0f }); \
    \
    indices.push_back({ index, index + 2, index + 1 }); \
    indices.push_back({ index, index + 3, index + 2 }); \
    \
    index += 4;

#define FACE_TOP \
    vertices.push_back({ x       , y + 1.0f, z        }); \
    vertices.push_back({ x + 1.0f, y + 1.0f, z        }); \
    vertices.push_back({ x + 1.0f, y + 1.0f, z + 1.0f }); \
    vertices.push_back({ x       , y + 1.0f, z + 1.0f }); \
    \
    normals.push_back({ 0.0f, 1.0f, 0.0f }); \
    normals.push_back({ 0.0f, 1.0f, 0.0f }); \
    normals.push_back({ 0.0f, 1.0f, 0.0f }); \
    normals.push_back({ 0.0f, 1.0f, 0.0f }); \
    \
    uvs.push_back({ 0.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 0.0f }); \
    uvs.push_back({ 0.0f, 0.0f }); \
    \
    indices.push_back({ index, index + 2, index + 1 }); \
    indices.push_back({ index, index + 3, index + 2 }); \
    \
    index += 4;

#define FACE_BOTTOM \
    vertices.push_back({ x       , y       , z        }); \
    vertices.push_back({ x + 1.0f, y       , z        }); \
    vertices.push_back({ x + 1.0f, y       , z + 1.0f }); \
    vertices.push_back({ x       , y       , z + 1.0f }); \
    \
    normals.push_back({ 0.0f, -1.0f, 0.0f }); \
    normals.push_back({ 0.0f, -1.0f, 0.0f }); \
    normals.push_back({ 0.0f, -1.0f, 0.0f }); \
    normals.push_back({ 0.0f, -1.0f, 0.0f }); \
    \
    uvs.push_back({ 0.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 1.0f }); \
    uvs.push_back({ 1.0f, 0.0f }); \
    uvs.push_back({ 0.0f, 0.0f }); \
    \
    indices.push_back({ index, index + 1, index + 2 }); \
    indices.push_back({ index, index + 2, index + 3 }); \
    \
    index += 4;

voxel::Chunk::Chunk() {
    mesh.AddVertexBuffer(&dataBuffer, gl::Type::Float, 3);
}

voxel::Chunk::Chunk(int x, int y, int z) {
    SetPosition(x, y, z);
    mesh.AddVertexBuffer(&dataBuffer, gl::Type::Float, 3);
}

voxel::Chunk::Chunk(const glm::ivec3& position) : position(position) {
    SetPosition(position.x, position.y, position.z);
    mesh.AddVertexBuffer(&dataBuffer, gl::Type::Float, 3);
}

voxel::Chunk::~Chunk() {}

#define COLOR \
    colors.push_back(currentColor); \
    colors.push_back(currentColor); \
    colors.push_back(currentColor); \
    colors.push_back(currentColor);

void voxel::Chunk::GenerateMesh() {
    std::vector<glm::vec3>& vertices = mesh.vertices;
    std::vector<glm::vec3>& normals = mesh.normals;
    std::vector<glm::vec2>& uvs = mesh.uvs;
    std::vector<glm::u32vec3>& indices = mesh.indices;
    std::vector<glm::vec3> colors;

    unsigned int index = 0;

    glm::vec3 currentColor = glm::vec3(1.0f);

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int y = 0; y < CHUNK_SIZE; y++) {
                const Block& block = blocks[x][y][z];

                if (!block.index) { continue; }

                switch (block.index) {
                    case 1: currentColor = glm::vec3(0.102f, 0.631f, 0.259f); break;
                    case 2: currentColor = glm::vec3(0.106f, 0.192f, 0.549f); break;
                }

                if (!HasBlock(x - 1, y, z)) { FACE_LEFT; COLOR; }
                if (!HasBlock(x + 1, y, z)) { FACE_RIGHT; COLOR; }
                if (!HasBlock(x, y - 1, z)) { FACE_BOTTOM; COLOR; }
                if (!HasBlock(x, y + 1, z)) { FACE_TOP; COLOR; }
                if (!HasBlock(x, y, z - 1)) { FACE_BACK; COLOR; }
                if (!HasBlock(x, y, z + 1)) { FACE_FRONT; COLOR; }
            }
        }
    }

    dataBuffer.SetData(colors.data(), colors.size() * sizeof(glm::vec3));
    mesh.Bake();
    isValid = true;
}

inline void voxel::Chunk::SetPosition(int x, int y, int z) {
    position = glm::ivec3(x, y, z);

    const glm::vec3 worldPosition = glm::vec3(x, y, z) * (float)CHUNK_SIZE;

    bounds.SetMin(worldPosition);
    bounds.SetMax(worldPosition + glm::vec3(CHUNK_SIZE));
}
