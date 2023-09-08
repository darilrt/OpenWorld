#pragma once

#include "amuse/core.h"

class CameraController : public ecs::Component {
	Transform* transform = nullptr;
	Camera* camera = nullptr;

	bool isDragging = false;
	float senitivity = 45.0f;
	float cameraSpeed = 25.0f;

public:

	void Start() override;

	void Update() override;
};

