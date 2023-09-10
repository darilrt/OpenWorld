#include "body.h"

#include <glm/gtc/type_ptr.hpp>

void voxel::Body::Init() {
    transform = &entity->GetComponent<Transform>();

    shader = new gl::Shader("assets/shaders/texture.vert", "assets/shaders/texture.frag");

    texture = gl::Texture::Load("assets/textures/leaves.png");
    texture->SetFilter(gl::Texture::Filter::NEAREST);

    mesh = new gl::Mesh();

    matrixIndexBuffer = new gl::VertexBuffer();

    matrices.fill(glm::mat4(1.0f));

    mesh->AddVertexBuffer(matrixIndexBuffer, gl::Type::Float, 1);
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
        mat = glm::scale(mat, box->scale);
        mat = glm::toMat4(box->rotation) * mat;
        mat = glm::translate(mat, -box->pivot);
        matrices[i] = mat;
	}
}

void voxel::Body::Bake() {
    std::vector<glm::vec3>& vertices = mesh->vertices;
    std::vector<glm::vec3>& normals = mesh->normals;
    std::vector<glm::vec2>& uvs = mesh->uvs;
    std::vector<glm::uvec3>& indices = mesh->indices;
    std::vector<int> matrixIndices;

    uint32_t index = 0;

    for (int i = 0; i < boxes.size(); i++) {
        auto& box = boxes[i];

        // Matrix

        glm::mat4 mat = glm::mat4(1.0f);
        mat = glm::rotate(mat, box->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        mat = glm::rotate(mat, box->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        mat = glm::rotate(mat, box->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        mat = glm::translate(mat, -box->pivot);
        mat = glm::translate(mat, box->position);
        mat = glm::scale(mat, box->scale);
        matrices[i] = mat;
           
        // Indices 

        matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i);
        matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i);
        matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i);
        matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i);
        matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i);
        matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i); matrixIndices.push_back(i);

        // Mesh

        vertices.push_back({ 0.0f       , 0.0f       , 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f + 1.0f });

        vertices.push_back({ 0.0f       , 0.0f       , 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f });
        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f });

        vertices.push_back({ 0.0f       , 0.0f       , 0.0f });
        vertices.push_back({ 0.0f       , 0.0f       , 0.0f + 1.0f });
        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f });

        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f       , 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f });

        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f });
        vertices.push_back({ 0.0f + 1.0f, 0.0f + 1.0f, 0.0f + 1.0f });
        vertices.push_back({ 0.0f       , 0.0f + 1.0f, 0.0f + 1.0f });

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

        uvs.push_back({ 0.0f, 1.0f });
        uvs.push_back({ 1.0f, 1.0f });
        uvs.push_back({ 1.0f, 0.0f });
        uvs.push_back({ 0.0f, 0.0f });

        uvs.push_back({ 0.0f, 1.0f });
        uvs.push_back({ 1.0f, 1.0f });
        uvs.push_back({ 1.0f, 0.0f });
        uvs.push_back({ 0.0f, 0.0f });

        uvs.push_back({ 0.0f, 1.0f });
        uvs.push_back({ 1.0f, 1.0f });
        uvs.push_back({ 1.0f, 0.0f });
        uvs.push_back({ 0.0f, 0.0f });

        uvs.push_back({ 0.0f, 1.0f });
        uvs.push_back({ 1.0f, 1.0f });
        uvs.push_back({ 1.0f, 0.0f });
        uvs.push_back({ 0.0f, 0.0f });

        uvs.push_back({ 0.0f, 1.0f });
        uvs.push_back({ 1.0f, 1.0f });
        uvs.push_back({ 1.0f, 0.0f });
        uvs.push_back({ 0.0f, 0.0f });

        uvs.push_back({ 0.0f, 1.0f });
        uvs.push_back({ 1.0f, 1.0f });
        uvs.push_back({ 1.0f, 0.0f });
        uvs.push_back({ 0.0f, 0.0f });

        indices.push_back({ index, index + 1, index + 2 });
        indices.push_back({ index, index + 2, index + 3 });

        index += 4;

        indices.push_back({ index, index + 2, index + 1 });
        indices.push_back({ index, index + 3, index + 2 });

        index += 4;

        indices.push_back({ index, index + 1, index + 2 });
        indices.push_back({ index, index + 2, index + 3 });

        index += 4;

        indices.push_back({ index, index + 2, index + 1 });
        indices.push_back({ index, index + 3, index + 2 });

        index += 4;

        indices.push_back({ index, index + 2, index + 1 });
        indices.push_back({ index, index + 3, index + 2 });

        index += 4;

        indices.push_back({ index, index + 1, index + 2 });
        indices.push_back({ index, index + 2, index + 3 });

        index += 4;
    }
    
    matrixIndexBuffer->SetData(matrixIndices.data(), matrixIndices.size() * sizeof(uint32_t), gl::VertexBuffer::Dynamic);
    mesh->Bake();
}
