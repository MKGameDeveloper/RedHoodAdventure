#pragma once
#include "Utilities/BoundingBox.h"
#include "Tile.h"

class IndexNumBuffer : public ShaderBuffer
{
public:
    struct Data
    {
        uint index;
        Vector3 dummy;
    };

    IndexNumBuffer() : ShaderBuffer(&data, sizeof(data))
    {
        data.index = 0;
    }

    void SetIndex(uint index) { data.index = index; }

private:
    Data data;
};

class TileMap
{
public:
    TileMap(uint width, uint height, uint spacing);
    ~TileMap();

    void Update();
    void Render();
    void GUI();

    void GenerateTileMap();
    void MapVertexBuffer();
    void UnmapVertexBuffer();

    void Save(string path);
    void Load(string path);

    class Tile* GetTile(Vector3 mPos);

private:
    uint width = 0;
    uint height = 0;
    uint spacing = 0;

    uint vertexCount = 0;
    uint indexCount = 0;

    vector<VertexTile> vertices;
    VertexBuffer* vb = nullptr;
    D3D11_MAPPED_SUBRESOURCE subResource;

    vector<uint> indices;
    IndexBuffer* ib = nullptr;

    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    InputLayout* il = nullptr;

    Matrix world = Values::Identity;
    WorldBuffer* wb = nullptr;

    IndexNumBuffer* inb = nullptr;

    vector<class Tile**> tiles;

    string FileName;
    char buf[256];

    BoundingBox::Tag tag = BoundingBox::None;
    Type type = UpPass;
    Tile::ObjectType objtype = Tile::NoneObj;
    Tile::MonsterType msttype = Tile::MudGuard;

    Vector3 mPos;
    
    string stag = " ";
    string stype = " ";

    int BrushMode = 0;
    string smode = "Normal Mode";

    int AreaMode = 1;
    string sarea = "Area Layer";

private:
    Vector2 startUV;
    Vector2 endUV;

    uint xcount;
    uint ycount;

};