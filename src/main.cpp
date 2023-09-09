#include "amuse/core.h"

#include "world.h"
#include "camera_controller.h"

class WorldScene : public ecs::System {
public:
	void Init() override {
		ecs::Entity& camera = CreateEntity(
			Transform(),
			Camera(),
			CameraController()
		);

		voxel::World& world = CreateEntity(
			Transform(),
			voxel::World()
		).GetComponent<voxel::World>();

		#define WORLD_SIZE 4

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