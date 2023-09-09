#pragma once

#include "amuse/core.h"

#include <array>
#include <glm/glm.hpp>

#define CHUNK_SIZE 32

namespace voxel {
    struct Block {
        uint32_t index;
    };

    class Chunk {
    public:
        std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> blocks;

        Chunk();
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

        inline bool HasBlock(int x, int y, int z) {
            if (x < 0 || x >= CHUNK_SIZE) { return false; }
            if (y < 0 || y >= CHUNK_SIZE) { return false; }
            if (z < 0 || z >= CHUNK_SIZE) { return false; }
            
            return blocks[x][y][z].index;
        }

    private:
        bool isValid = false;
        gl::Mesh mesh;
        glm::ivec3 position;
        math::Bounds bounds;

        gl::VertexBuffer dataBuffer;
    };
}
