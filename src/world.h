#pragma once

#include "amuse/core.h"
#include "chunk.h"

#include <map>

namespace voxel {

	typedef std::tuple<int, int, int> ChunkKey;

	class World : public ecs::Component {
		Transform* transform;

		gl::Shader* shader;
		gl::Texture* texture;

	public:
		std::map<ChunkKey, Chunk*> chunks;
		
		void Init() override;

		void Render() override;

        void GenerateChunk(int x, int y, int z);

        inline Chunk& GetChunk(int x, int y, int z) { return *chunks[ChunkKey(x, y, z)]; }
	};
}