#pragma once

#include "amuse/core.h"

#include <vector>

namespace voxel {

	class Body : public ecs::Component {
	public:
		class Box {
			Box* parent;
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
		};

		void Init() override;

		void Render() override;

		gl::Shader* shader;
		gl::Texture* texture;
		gl::Mesh mesh;

		std::vector<Box> boxes;
	};
}

