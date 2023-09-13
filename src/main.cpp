#include "amuse/core.h"

#include "world.h"
#include "body.h"
#include "camera_controller.h"

#include <filesystem>

class WorldScene : public ecs::System {
public:
	void Init() override {
		ecs::Entity& camera = CreateEntity(
			Transform(),
			Camera(),
			CameraController()
		);

		ecs::Entity& bodyE = CreateEntity(
			Transform(),
		);

		voxel::Body& body = bodyE.GetComponent<voxel::Body>();

		bodyE.GetComponent<Transform>().position = glm::vec3(0.5f, 0.0f, 0.5f);

		voxel::World& world = CreateEntity(
			Transform(),
			voxel::World()
		).GetComponent<voxel::World>();

		constexpr int WORLD_SIZE = 4;

		for (int x = -WORLD_SIZE; x < WORLD_SIZE; x++) {
			for (int z = -WORLD_SIZE; z < WORLD_SIZE; z++) {
				for (int y = -1; y < 1; y++) {
					world.GenerateChunk(x, y, z);
				}
			}
		}

	}
};

int main(int argc, char* argv[]) {
	amuse::Init(1920, 1080);

	SceneManager::AddScene<WorldScene>();

	SceneManager::SetActiveScene<WorldScene>();

	amuse::RunGame();
	return 0;
}