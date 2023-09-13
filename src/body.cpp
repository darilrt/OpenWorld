#include "body.h"
#include "json.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <fstream>

void voxel::Body::Init() {
    transform = &entity->GetComponent<Transform>();

    shader = &Assets::Get<gl::Shader>("shaders/body");

    texture = &Assets::Get<gl::Texture>("textures/uvchecker.png");
    texture->SetFilter(gl::Texture::Filter::Nearest);

    boxIndexBuffer = new gl::VertexBuffer();

    matrices.fill(glm::mat4(1.0f));
}

void voxel::Body::Render() {
    shader->Bind();
    shader->SetCameraUniforms(*Camera::active);
    glm::mat4 model = transform->GetModelMatrix();
    shader->SetUniformMatrix4fv(SHADER_UNIFORM_MODEL, glm::value_ptr(model));
    shader->SetSampler2D("uTexture", texture);
    
    shader->SetUniformMatrix4fv("uMatrices", glm::value_ptr(matrices[0]), matrices.size());
    
    mesh->DrawTriangles();

    shader->Unbind();
}

void voxel::Body::UpdateMatrices() {
    for (int i = 0; i < boxes.size(); i++) {
		auto& box = boxes[i];

        glm::mat4 mat = glm::mat4(1.0f);
        mat = glm::translate(mat, box->position);
        mat = mat * glm::toMat4(box->rotation);
        mat = glm::scale(mat, box->scale);
        mat = glm::translate(mat, -box->pivot);
        matrices[i] = mat;
	}
}

void voxel::Body::Bake() {
    if (mesh != nullptr) {
        delete mesh;
    }

    mesh = new gl::Mesh();
    mesh->AddVertexBuffer(boxIndexBuffer, gl::Type::Float, 1);

    std::vector<glm::vec3>& vertices = mesh->vertices;
    std::vector<glm::vec3>& normals = mesh->normals;
    std::vector<glm::vec2>& uvs = mesh->uvs;
    std::vector<glm::uvec3>& indices = mesh->indices;
    std::vector<int> boxxIndices;

    uint32_t index = 0;

    if (boxes.size() == 0) return;

    for (int i = 0; i < boxes.size(); i++) {
        auto& box = boxes[i];

        // Indices 

        boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i);
        boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i);
        boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i);
        boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i);
        boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i);
        boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i); boxxIndices.push_back(i);

        // Mesh

        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f + 1.0f });
        vertices.push_back({ 0.0f       , 0.0f       , 0.0f + 1.0f });

        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f });
        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f });
        vertices.push_back({ 0.0f       , 0.0f       , 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f });

        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f });
        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f       , 0.0f       , 0.0f + 1.0f });
        vertices.push_back({ 0.0f       , 0.0f       , 0.0f });

        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f + 1.0f });

        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f });
        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f });

        vertices.push_back({ 0.0f       , 0.0f       , 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f + 1.0f });
        vertices.push_back({ 0.0f       , 0.0f       , 0.0f + 1.0f });

        normals.push_back({ 0.0f, 0.0f, 1.0f });
        normals.push_back({ 0.0f, 0.0f, 1.0f });
        normals.push_back({ 0.0f, 0.0f, 1.0f });
        normals.push_back({ 0.0f, 0.0f, 1.0f });

        normals.push_back({ 0.0f, 0.0f, -1.0f });
        normals.push_back({ 0.0f, 0.0f, -1.0f });
        normals.push_back({ 0.0f, 0.0f, -1.0f });
        normals.push_back({ 0.0f, 0.0f, -1.0f });

        normals.push_back({ -1.0f, 0.0f, 0.0f });
        normals.push_back({ -1.0f, 0.0f, 0.0f });
        normals.push_back({ -1.0f, 0.0f, 0.0f });
        normals.push_back({ -1.0f, 0.0f, 0.0f });

        normals.push_back({ 1.0f, 0.0f, 0.0f });
        normals.push_back({ 1.0f, 0.0f, 0.0f });
        normals.push_back({ 1.0f, 0.0f, 0.0f });
        normals.push_back({ 1.0f, 0.0f, 0.0f });

        normals.push_back({ 0.0f, 1.0f, 0.0f });
        normals.push_back({ 0.0f, 1.0f, 0.0f });
        normals.push_back({ 0.0f, 1.0f, 0.0f });
        normals.push_back({ 0.0f, 1.0f, 0.0f });

        normals.push_back({ 0.0f, -1.0f, 0.0f });
        normals.push_back({ 0.0f, -1.0f, 0.0f });
        normals.push_back({ 0.0f, -1.0f, 0.0f });
        normals.push_back({ 0.0f, -1.0f, 0.0f });

        for (int i = 0; i < 6; i++) {
            const glm::vec4 uv = box->uvs[i];

            uvs.push_back({ uv.x, uv.y });
            uvs.push_back({ uv.z, uv.y });
            uvs.push_back({ uv.z, uv.w });
            uvs.push_back({ uv.x, uv.w });
		}

        indices.push_back({ index + 2, index + 1, index });
        indices.push_back({ index + 3, index + 2, index });

        index += 4;

        indices.push_back({ index, index + 2, index + 1 });
        indices.push_back({ index, index + 3, index + 2 });

        index += 4;

        indices.push_back({ index + 2, index + 1, index });
        indices.push_back({ index + 3, index + 2, index });

        index += 4;

        indices.push_back({ index, index + 2, index + 1 });
        indices.push_back({ index, index + 3, index + 2 });

        index += 4;

        indices.push_back({ index + 1, index + 2, index });
        indices.push_back({ index + 2, index + 3, index });

        index += 4;

        indices.push_back({ index, index + 1, index + 2 });
        indices.push_back({ index, index + 2, index + 3 });

        index += 4;
    }
    
    UpdateMatrices();

    boxIndexBuffer->SetData(boxxIndices.data(), boxxIndices.size() * sizeof(uint32_t), gl::VertexBuffer::Dynamic);
    mesh->Bake();
}

void ParseBox(voxel::Body& body, nlohmann::json object, voxel::Body::Box* parent=nullptr) {
    if (object.contains("hide")) {
        if (object["hide"].get<bool>()) {
			return;
		}
    }

    voxel::Body::Box& box = body.AddBox({
        nullptr,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    });

    box.parent = parent;
    
    if (object.contains("position")) {
        box.position = {
            object["position"][0].get<float>(),
            object["position"][1].get<float>(),
            object["position"][2].get<float>() 
        };
    }

    if (object.contains("scale")) {
        box.scale = {
            object["scale"][0].get<float>(), 
            object["scale"][1].get<float>(), 
            object["scale"][2].get<float>() 
        };
    }

    if (object.contains("rotation")) {
        box.rotation = glm::rotate(box.rotation, glm::radians(object["rotation"][0].get<float>()), glm::vec3(1.0f, 0.0f, 0.0f));
        box.rotation = glm::rotate(box.rotation, glm::radians(object["rotation"][1].get<float>()), glm::vec3(0.0f, 1.0f, 0.0f));
        box.rotation = glm::rotate(box.rotation, glm::radians(object["rotation"][2].get<float>()), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    if (object.contains("pivot")) {
        box.pivot = {
            object["pivot"][0].get<float>(), 
            object["pivot"][1].get<float>(), 
            object["pivot"][2].get<float>() 
        };
    }

    if (object.contains("children")) {
        for (auto& child : object["children"]) {
            ParseBox(body, child, &box);
        }
    }

    if (object.contains("uv")) {
        int size = object["uv"].size() >= 6 ? 6 : object["uv"].size();
        for (int i = 0; i < size; i++) {
            box.uvs[i] = {
				object["uv"][i][0].get<float>(),
				object["uv"][i][1].get<float>(),
				object["uv"][i][2].get<float>(),
				object["uv"][i][3].get<float>()
			};
		}
    }
}

void voxel::Body::FromJson(const char* path) {
    boxes.clear();
    
    std::ifstream file(path);

    nlohmann::json jsonObject;
    try {
        jsonObject = nlohmann::json::parse(file);
    }
    catch (nlohmann::json::parse_error& e) {
        debug::Log("Failed to parse json file: " + std::string(path) + "\n");
        debug::Log(e.what() + std::string("\n"));
		return;
	}

    file.close();

    if (jsonObject.contains("texture")) {
        texture = &Assets::Get<gl::Texture>(jsonObject["texture"].get<std::string>());
        texture->SetFilter(gl::Texture::Filter::Nearest);
    }
    
    if (jsonObject.contains("body")) {
        for (auto& box : jsonObject["body"]) {
			ParseBox(*this, box);
		}
	}

    Bake();
}