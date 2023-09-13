#include "amuse/core.h"

#include "world.h"
#include "body.h"
#include "camera_controller.h"

#include <filesystem>

class WorldScene : public ecs::System {
public:
	void Init() override {
		Screen::Get()->window->SetResizable(true);

		es::AddEventListener("WindowResize", [&](const es::Event& e) {
			Camera::active->SetViewport({
				0, 0,
				e.window.width,
				e.window.height
			});
		});

		ecs::Entity& camera = CreateEntity(
			Transform(),
			Camera(),
			CameraController()
		);

		ecs::Entity& bodyE = CreateEntity(
			Transform(),
		);

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