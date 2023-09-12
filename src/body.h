#pragma once

#include "amuse/core.h"

#include <vector>

namespace voxel {

	class Body : public ecs::Component {
	public:
		class Box {
		public:
			Box* parent;
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scale;
			glm::vec3 pivot;

			glm::vec4 uvs[6] = {
				{ 0.0f, 1.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 1.0f, 0.0f },
			};
		};

		Transform* transform;

		gl::Shader* shader;
		gl::Texture* texture;
		gl::Mesh* mesh;
		gl::VertexBuffer* boxIndexBuffer;

		std::vector<Box*> boxes;
		std::array<glm::mat4, 10> matrices;

		void Init() override;

		void Render() override;

		Box& AddBox(const Box& box) {
			boxes.push_back(new Box(box));
			return *boxes.back();
		}

		void UpdateMatrices();

		void Bake();

		void FromJson(const char* path);
	};
}

