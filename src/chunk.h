#pragma once

#include "amuse/core.h"

#include <array>
#include <glm/glm.hpp>

#define CHUNK_SIZE 32

namespace voxel {
    struct Block {
        bool active;
        glm::vec3 color;
    };

    class Chunk {
    public:
        std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> blocks;

        Chunk() = default;
        Chunk(int x, int y, int z);
        Chunk(const glm::ivec3& position);
        ~Chunk();

        void GenerateMesh();

        void SetBlock(int x, int y, int z, const Block& block) { blocks[x][y][z] = block; }

        inline void SetPosition(int x, int y, int z);

        inline gl::Mesh& GetMesh() { return mesh; }

        inline glm::ivec3 GetPosition() const { return position; }

        inline bool IsValid() const { return isValid; }

        inline math::Bounds GetBounds() const { return bounds; }

    private:
        bool isValid = false;
        gl::Mesh mesh;
        glm::ivec3 position;
        math::Bounds bounds;
    };
}
