#pragma once

#include "amuse/core.h"

class PlayerController : public ecs::Component {
	Transform* transform;

public:

	void Init() override;

	void Update() override;
};

