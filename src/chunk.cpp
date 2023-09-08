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

voxel::Chunk::Chunk(int x, int y, int z) {
    SetPosition(x, y, z);
}

voxel::Chunk::Chunk(const glm::ivec3& position) : position(position) {
    SetPosition(position.x, position.y, position.z);
}

voxel::Chunk::~Chunk() {}

void voxel::Chunk::GenerateMesh() {
    std::vector<glm::vec3>& vertices = mesh.vertices;
    std::vector<glm::vec3>& normals = mesh.normals;
    std::vector<glm::vec2>& uvs = mesh.uvs;
    std::vector<glm::u32vec3>& indices = mesh.indices;

    unsigned int index = 0;

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int y = 0; y < CHUNK_SIZE; y++) {
                const Block& block = blocks[x][y][z];

                if (!block.active) { continue; }

                if ((x > 0 && !blocks[x - 1][y][z].active) || (x == 0)) { FACE_LEFT; }
                if ((x < CHUNK_SIZE - 1 && !blocks[x + 1][y][z].active) || (x == CHUNK_SIZE - 1)) { FACE_RIGHT; }

                if ((y > 0 && !blocks[x][y - 1][z].active) || (y == 0)) { FACE_BOTTOM; }
                if ((y < CHUNK_SIZE - 1 && !blocks[x][y + 1][z].active) || (y == CHUNK_SIZE - 1)) { FACE_TOP; }

                if ((z > 0 && !blocks[x][y][z - 1].active) || (z == 0)) { FACE_BACK; }
                if ((z < CHUNK_SIZE - 1 && !blocks[x][y][z + 1].active) || (z == CHUNK_SIZE - 1)) { FACE_FRONT; }
            }
        }
    }

    mesh.Bake();
    isValid = true;
}

inline void voxel::Chunk::SetPosition(int x, int y, int z) {
    position = glm::ivec3(x, y, z);

    const glm::vec3 worldPosition = glm::vec3(x, y, z) * (float)CHUNK_SIZE;

    bounds.SetMin(worldPosition);
    bounds.SetMax(worldPosition + glm::vec3(CHUNK_SIZE));
}
