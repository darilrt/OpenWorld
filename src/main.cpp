#include "amuse/core.h"

#include "world.h"
#include "body.h"
#include "camera_controller.h"

#include <filesystem>

class BodyController : public ecs::Component {
public:
	voxel::Body* body;
	voxel::Body::Box* box;
	std::filesystem::file_time_type lastModified;

	void Init() override {
		body = &entity->GetComponent<voxel::Body>();

		body->FromJson("assets/models/testmodel.json");

		io::FileWatcher::OnFileChange("assets/models/testmodel.json", [&]() {
			body->FromJson("assets/models/testmodel.json");
			debug::Log("Reloaded model");
		});
	}

	void Update() override {
		body->UpdateMatrices();
	}
};

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
			voxel::Body(),
			BodyController()
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