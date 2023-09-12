#include "amuse/core.h"
#include "world.h"

#include <glm/gtc/type_ptr.hpp>

void voxel::World::Init() {
    transform = &entity->GetComponent<Transform>();

    shader = &Assets::Get<gl::Shader>("shaders/terrain");
    texture = &Assets::Get<gl::Texture>("textures/block.png");
    
    texture->SetFilter(gl::Texture::Filter::Nearest);
}

void voxel::World::Render() {
    shader->Bind();

    shader->SetCameraUniforms(*Camera::active);
    shader->SetSampler2D("uTexture", texture);

    for (auto& [chunkKey, chunk] : chunks) {
        if (!chunk->IsValid()) { continue; }

        transform->position = glm::vec3(chunk->GetPosition() * CHUNK_SIZE);

        glm::mat4 model = transform->GetModelMatrix();
        shader->SetUniformMatrix4fv(SHADER_UNIFORM_MODEL, glm::value_ptr(model));

        chunk->GetMesh().DrawTriangles();
    }

    shader->Unbind();
}

void voxel::World::GenerateChunk(int x, int y, int z) {
    const ChunkKey position(x, y, z);

    if (chunks.find(position) == chunks.end()) {
        chunks[position] = new Chunk(x, y, z);
    }

    Chunk& chunk = *chunks[position];

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int y = 0; y < CHUNK_SIZE; y++) {
                const glm::vec3 globalPos = glm::vec3(x, y, z) + glm::vec3(chunk.GetPosition() * CHUNK_SIZE);

                float height = (std::sin(globalPos.x * 0.05f) + std::sin(globalPos.z * 0.05f)) * 7.0f;
                uint32_t index = 0;

                if (globalPos.y < height) {
                    index = 1;

                    if (height < -10.0f) {
                        index = 2;
                    }
                }

                chunk.SetBlock(x, y, z, Block{ index });
            }
        }
    }

    chunk.GenerateMesh();
}
