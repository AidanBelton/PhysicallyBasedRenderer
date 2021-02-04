#include "Mesh.h"
MeshData::MeshData()
{
    glGenBuffers(3,VBO);
    glGenVertexArrays(1,&VAO);
}

MeshData::~MeshData()
{
    DeleteCPUData();
    DeleteGPUData();
}

void MeshData::LoadGPUData()
{
            GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
        };
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
}
void MeshData::LoadCPUData()
{
    V = new vec3[8];
    V[0] = vec3(1,-1,-1);
    V[1] = vec3(1,-1,1);
    V[2] = vec3(-1,-1,1);
    V[3] = vec3(-1,-1,-1);
    V[4] = vec3(1,1,-1);
    V[5] = vec3(1,1,1);
    V[6] = vec3(-1,1,1);
    V[7] = vec3(-1,1,-1);
}
void MeshData::DeleteGPUData()
{
    glDeleteBuffers(3,VBO);
    glDeleteVertexArrays(1,&VAO);
}
void MeshData::DeleteCPUData()
{
    delete[] V;
    delete[] N;
    delete[] T;
}

void MeshData::Draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshDataContainer::MeshDataContainer()
{
    Data = new MeshData();
    Data->LoadCPUData();
    Data->LoadGPUData();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mesh::Mesh(string F, MeshDataContainer* MD)
:File(F), Container(MD)
{

}

void Mesh::Draw()
{
    Container->Draw();
}
