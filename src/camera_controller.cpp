#include "camera_controller.h"

#include <iostream>
#include <glm/glm.hpp>

void CameraController::Start() {
    REQUIRE_COMPONENT(Transform);
    REQUIRE_COMPONENT(Camera);

    transform = &entity->GetComponent<Transform>();
    transform->position = glm::vec3(0.0f, 0.0f, 3.0f);
    transform->rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));

	camera = &entity->GetComponent<Camera>();
    camera->SetPerspective(45.0f, 0.1f, 500.0f);
    camera->SetActive();

    isDragging = false;
}

void CameraController::Update() {
    if (Input::GetMouseButtonDown(MouseButton::Right)) {
		isDragging = true;
		Cursor::SetRelativeCursorMode(true);
	}

    if (Input::GetMouseButtonUp(MouseButton::Right)) {
        isDragging = false;
        Cursor::SetRelativeCursorMode(false);
    }

    if (isDragging) {
        const glm::vec2 delta = Input::GetMouseDelta() * senitivity;
        const glm::vec2 newRot = glm::radians(glm::vec2(delta.y, delta.x)) * Input::DeltaTime();

        transform->rotation = glm::rotate(transform->rotation, newRot.x, glm::vec3(1.0f, 0.0f, 0.0f) * transform->rotation);
        transform->rotation = glm::rotate(transform->rotation, newRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	}

    glm::vec3 direction(0.0f);
    direction.x += Input::GetKey(KeyCode::D) - Input::GetKey(KeyCode::A);
    direction.y += Input::GetKey(KeyCode::W) - Input::GetKey(KeyCode::S);
    direction.z += Input::GetKey(KeyCode::Space) - Input::GetKey(KeyCode::LeftShift);

    if (glm::dot(direction, direction) >= 0.001f) {
        direction = glm::normalize(direction) * Input::DeltaTime() * cameraSpeed;

        const glm::mat4 inverted = glm::inverse(camera->GetViewMatrix());
        const glm::vec3 forward = -glm::normalize(glm::vec3(inverted[2]));
        const glm::vec3 right = -glm::normalize(-glm::vec3(inverted[0]));
        const glm::vec3 up = glm::normalize(glm::vec3(inverted[1]));

        transform->position += forward * direction.y;
        transform->position += right * direction.x;
        transform->position += up * direction.z;
    }
}
