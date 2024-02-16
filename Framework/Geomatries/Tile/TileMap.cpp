#include "Framework.h"
#include "TileSet.h"
#include "Tile.h"
#include "TileMap.h"



TileMap::TileMap(uint width, uint height, uint spacing)
    : width(width), height(height), spacing(spacing), buf("")
{
    TileSet::Create();

    for (int i = 0; i < 3; i++)
    {
        tiles.push_back(new Tile*);
    }

    GenerateTileMap();

    vertices.assign(4, VertexTile());
    vertices[0].position = Values::ZeroVec3;                                // 0.0.0
    vertices[1].position = Vector3(0.0f, (float)spacing, 0.0f);             // 0.40.0
    vertices[2].position = Vector3((float)spacing, 0.0f, 0.0f);             // 40.0.0
    vertices[3].position = Vector3((float)spacing, (float)spacing, 0.0f);   // 40.40.0

    indices = { 0,1,2,2,1,3 };

    vb = new VertexBuffer();
    vb->Create(vertices, D3D11_USAGE_DYNAMIC);

    ib = new IndexBuffer();
    ib->Create(indices, D3D11_USAGE_IMMUTABLE);

    vs = new VertexShader();
    vs->Create(ShaderPath + L"Tile/VertexTile.hlsl", "VS");

    ps = new PixelShader();
    ps->Create(ShaderPath + L"Tile/VertexTile.hlsl", "PS");

    il = new InputLayout();
    il->Create(VertexTile::descs, VertexTile::count, vs->GetBlob());

    wb = new WorldBuffer();
    wb->SetWorld(world);

    inb = new IndexNumBuffer();
    inb->SetIndex(0);
}

TileMap::~TileMap()
{
    SAFE_DELETE(inb);
    SAFE_DELETE(wb);

    SAFE_DELETE(il);
    SAFE_DELETE(ps);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);

    for (Tile** t : tiles)
    {
        for (uint y = 0; y < height; y++)
            SAFE_DELETE_ARRAY(t[y]);

        SAFE_DELETE_ARRAY(t);
    }

    TileSet::Delete();
}

void TileMap::Update()
{
    mPos = Mouse::Get()->GetPosition() * 2;
    Tile* tile = GetTile(mPos);

    if (tile)
    {
        inb->SetIndex(tile->GetIndex());

        switch (tile->GetTag())
        {
        case BoundingBox::None:
            stag = "None";
            break;
        case BoundingBox::Player:
            stag = "Player";
            break;
        case BoundingBox::BackFloor:
            stag = "BackFloor";
            break;
        case BoundingBox::Floor:
            stag = "Floor";
            break;
        case BoundingBox::Monster:
            stag = "Monster";
            break;
        case BoundingBox::Object:
            stag = "Object";
            break;
        default:
            break;
        }

        if (tile->GetTag() != BoundingBox::Object)
        {
            switch (tile->GetType())
            {
            case NonePass:
                stype = "NonePass";
                break;
            case Pass:
                stype = "Pass";
                break;
            case UpPass:
                stype = "UpPass";
                break;
            case LeftSide:
                stype = "LeftSide";
                break;
            case LeftSideUp:
                stype = "LeftSideUp";
                break;
            case LeftSideDown:
                stype = "LeftSideDown";
                break;
            case RightSide:
                stype = "RightSide";
                break;
            case RightSideUp:
                stype = "RightSideUp";
                break;
            case RightSideDown:
                stype = "RightSideDown";
                break;
            case Up_Half:
                stype = "Up_Half";
                break;
            case Down_Half:
                stype = "Down_Half";
                break;

            default:
                break;
            }

        }
        else
        {
            switch (tile->GetObj())
            {
                case Tile::RightMoveFloor:
                    stype = "RightMoveFloor";
                    break;
                case Tile::LeftMoveFloor:
                    stype = "LeftMoveFloor";
                    break;
                case Tile::Portal:
                    stype = "Portal"; 
                case Tile::LeftRightFloor:
                        stype = "LeftRightFloor";
                case Tile::RightUpFloor:
                    stype = "RightUpFloor";
                    break;
                case Tile::LeftUpFloor:
                    stype = "LeftUpFloor";
                    break;
                case Tile::UpDownFloor:
                    stype = "UpDownFloor";
                    break;
                case Tile::BigTree1:
                    stype = "BigTree1";
                    break;
                case Tile::BigTree2:
                    stype = "BigTree2";
                    break;
                case Tile::BigTree3:
                    stype = "BigTree3";
                    break;
                case Tile::SmallTree1:
                    stype = "SmallTree1";
                    break;
                case Tile::SmallTree2:
                    stype = "SmallTree2";
                    break;
                case Tile::SmallTree3:
                    stype = "SmallTree3";
                    break;
                case Tile::Root1:
                    stype = "Root1";
                    break;
                case Tile::Root2:
                    stype = "Root2";
                    break;
                case Tile::Root3:
                    stype = "Root3";
                    break;
                case Tile::Shop:
                    stype = "Shop";
                    break; 
                case Tile::UpgradeNPC:
                    stype = "UpgradeNPC";
                    break;

                
                    break;
                default:
                    break;
            }
        }
       
    }

    if (Keyboard::Get()->Down(VK_F7))
    {
        BrushMode++;
        switch (BrushMode)
        {
        case 0:
        {
            smode = "Normal Mode";
            break;
        }
        case 1:
        {
            smode = "Tag Mode";
            break;
        }
        case 2:
        {
            smode = "Bounding Mode";
            break;
        }
        case 3:
        {
            smode = "Tag & Bounding Mode";
            break;
        }
        case 4:
        {
            smode = "Texture Mode";
            break;
        }
        case 5:
        {
            smode = "Draw_UV Mode";
            break;
        }
        default:
            BrushMode = 0;
            smode = "Normal Mode";
            break;
        }
            
    }


    if (Keyboard::Get()->Down(VK_F8))
    {
        AreaMode++;
        switch (AreaMode)
        {
        case 0:
        {
            sarea = "Back Layer";
            break;
        }
        case 1:
        {
            sarea = "Area Layer";
            break;
        }
        case 2:
        {
            sarea = "Front Layer";
            break;
        }
        default:
            AreaMode = 0;
            sarea = "Back Layer";
            break;
        }

    }

    if (Keyboard::Get()->Down('Q'))
    {
        startUV = TileSet::Get()->selectedStartUV;
    }

    if (Mouse::Get()->Press(0))
    {
        if (tile)
        {
            switch (BrushMode)
            {
            case 0:
            {
                tile->SetColor(Values::Red);
                startUV = TileSet::Get()->selectedStartUV;
                endUV = startUV + TileSet::Get()->texelTileSize;
                tile->SetStartUV(TileSet::Get()->selectedStartUV);
                tile->SetEndUV(endUV);

                tile->SetTag(tag);
                if (tile->GetTag() != BoundingBox::Object && tile->GetTag() != BoundingBox::Monster)
                {
                    tile->SetType(type);
                }
                else if(tile->GetTag() == BoundingBox::Object)
                {
                    tile->SetObj(objtype);
                }
                else
                {
                    tile->SetMonster(msttype);
                }

                break;
            }

            case 1:
            {
                tile->SetTag(tag);
                   
                break;
            }
            case 2:
            {
                tile->SetType(type);

                break;
            }
            case 3:
            {
                tile->SetTag(tag);
                if (tile->GetTag() != BoundingBox::Object && tile->GetTag() != BoundingBox::Monster)
                {
                    tile->SetType(type);
                }
                else if (tile->GetTag() == BoundingBox::Object)
                {
                    tile->SetObj(objtype);
                }
                else
                {
                    tile->SetMonster(msttype);
                }

                break;
            }
            case 4:
            {
                tile->SetColor(Values::Red);
                startUV = TileSet::Get()->selectedStartUV;
                endUV = startUV + TileSet::Get()->texelTileSize;
                tile->SetStartUV(TileSet::Get()->selectedStartUV);
                tile->SetEndUV(endUV);

                break;
            }
            case 5:
            {
                tile->SetColor(Values::Red);
                endUV = TileSet::Get()->selectedStartUV + TileSet::Get()->texelTileSize;

                int x_count = ((endUV.x - startUV.x) / TileSet::Get()->texelTileSize.x) + 0.5f;;
                int y_count = ((startUV.y - endUV.y + (TileSet::Get()->texelTileSize.y * 2)) / TileSet::Get()->texelTileSize.y)+0.5f;


                for (int y = 0; y < y_count; y++)
                {
                    for (int x = 0; x < x_count; x++)
                    {
                        tiles[AreaMode][ycount + y][xcount + x].SetStartUV(startUV + Vector2{ x * TileSet::Get()->texelTileSize.x ,-y * TileSet::Get()->texelTileSize.y});
                        tiles[AreaMode][ycount + y][xcount + x].SetEndUV((tiles[AreaMode][ycount + y][xcount + x].GetStartUV() + TileSet::Get()->texelTileSize));
                        tiles[AreaMode][ycount + y][xcount + x].SetTag(BoundingBox::BackFloor);
                    }
                }
                
                break;
            }
            default:
                break;
            }
            
        }
    }

    if (Mouse::Get()->Press(1))
    {
        if (tile)
        {
            tile->SetColor(Values::Black);
            Vector2 startUV = Values::ZeroVec2;
            Vector2 endUV = Values::ZeroVec2;
            tile->SetStartUV(startUV);
            tile->SetEndUV(endUV);

            tile->SetTag(BoundingBox::None);
            tile->SetType(UpPass);
        }
    }

    if (Keyboard::Get()->Down(VK_F5))
        Save(TilePath + FileName + ".txt");

    if (Keyboard::Get()->Down(VK_F6))
        Load(TilePath + FileName + ".txt"); 
    
    
}

void TileMap::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    ps->SetShader();

    DC->PSSetShaderResources(0, 1, &TileSet::Get()->tileSRV);

    for (uint i = 0; i < 3; i++)
    {
        for (uint y = 0; y < height; y++)
        {
            for (uint x = 0; x < width; x++)
            {
                Tile& tile = tiles[i][y][x];

                MapVertexBuffer();
                {
                    for (VertexTile& v : vertices)
                    {
                        v.color = tile.GetColor();
                        v.index = tile.GetIndex();
                    }

                    vertices[0].uv = Vector2(tile.GetStartUV().x, tile.GetEndUV().y);
                    vertices[1].uv = tile.GetStartUV();
                    vertices[2].uv = tile.GetEndUV();
                    vertices[3].uv = Vector2(tile.GetEndUV().x, tile.GetStartUV().y);

                    vertices[0].uv2 = Vector2(0, 1);
                    vertices[1].uv2 = Vector2(0, 0);
                    vertices[2].uv2 = Vector2(1, 1);
                    vertices[3].uv2 = Vector2(1, 0);
                }
                UnmapVertexBuffer();

                world = DXMath::Translation(tile.GetPosition());
                wb->SetWorld(world);
                wb->SetVSBuffer(0);
                inb->SetPSBuffer(0);
                DC->DrawIndexed(ib->GetCount(), 0, 0);
            }
        }
    }

    
}

void TileMap::GUI()
{
    TileSet::Get()->GUI();

    ImGui::Begin("FileName");
    {

        ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
        FileName = buf;

        ImGui::Text(FileName.c_str());

    }
    ImGui::End();

    ImGui::Begin("Tag");
    {
        ImGui::RadioButton("None", (int*)&tag, 0);
        ImGui::RadioButton("Player", (int*)&tag, 1);
        ImGui::RadioButton("Monster", (int*)&tag, 2);
        ImGui::RadioButton("BackFloor", (int*)&tag, 4);
        ImGui::RadioButton("Floor", (int*)&tag, 5);
        ImGui::RadioButton("Object", (int*)&tag, 6);
    }
    ImGui::End();


    if (tag != BoundingBox::Object && tag != BoundingBox::Monster)
    {
        ImGui::Begin("Bounding Mode");
        {
            ImGui::RadioButton("NonePass", (int*)&type, 0);
            ImGui::RadioButton("Pass", (int*)&type, 1);
            ImGui::RadioButton("UpPass", (int*)&type, 2);
            ImGui::RadioButton("LeftSide", (int*)&type, 3);
            ImGui::RadioButton("LeftSideUp", (int*)&type, 5);
            ImGui::RadioButton("LeftSideDown", (int*)&type, 4);
            ImGui::RadioButton("RightSide", (int*)&type, 6);
            ImGui::RadioButton("RightSideUp", (int*)&type, 8);
            ImGui::RadioButton("RightSideDown", (int*)&type, 7);
            ImGui::RadioButton("Up_Half", (int*)&type, 15);
            ImGui::RadioButton("Down_Half", (int*)&type, 16);
        }
        ImGui::End();
    }
    else if(tag == BoundingBox::Object)
    {
        ImGui::Begin("Object Type");
        {
            ImGui::RadioButton("RightMoveFloor", (int*)&objtype, 1);
            ImGui::RadioButton("LeftMoveFloor", (int*)&objtype, 2);
            ImGui::RadioButton("Portal", (int*)&objtype, 3);
            ImGui::RadioButton("LeftRightFloor", (int*)&objtype, 4);
            ImGui::RadioButton("RightUpFloor", (int*)&objtype, 5);
            ImGui::RadioButton("LeftUpFloor", (int*)&objtype, 6);
            ImGui::RadioButton("UpDownFloor", (int*)&objtype, 7);
            ImGui::RadioButton("BigTree1", (int*)&objtype, 8);
            ImGui::RadioButton("BigTree2", (int*)&objtype, 9);
            ImGui::RadioButton("BigTree3", (int*)&objtype, 10);
            ImGui::RadioButton("SmallTree1", (int*)&objtype, 11);
            ImGui::RadioButton("SmallTree2", (int*)&objtype, 12);
            ImGui::RadioButton("SmallTree3", (int*)&objtype, 13);
            ImGui::RadioButton("Root1", (int*)&objtype, 14);
            ImGui::RadioButton("Root2", (int*)&objtype, 15);
            ImGui::RadioButton("Root3", (int*)&objtype, 16);
            ImGui::RadioButton("Shop", (int*)&objtype, 17);
            ImGui::RadioButton("UpgradeNPC", (int*)&objtype, 18);
        }
        ImGui::End();
    }
    else
    {
        int a = msttype;

        ImGui::Begin("Monster Type");
        {
            ImGui::Text("msttype : %d", a);
            ImGui::RadioButton("Bringer", (int*)&msttype, 0);
            ImGui::RadioButton("MudGuard", (int*)&msttype, 1);
            ImGui::RadioButton("BombDroid", (int*)&msttype, 2);
            ImGui::RadioButton("ShadowMage", (int*)&msttype, 3);
            ImGui::RadioButton("ShadowStalker", (int*)&msttype, 4);
        }
        ImGui::End();
    }
    


    ImGui::Begin("Tile Info");
    {
        ImGui::Text("Tag : %s\nType : %s", stag.c_str(), stype.c_str());
    }
    ImGui::End();

    ImGui::Begin("Brush Mode");
    {
        ImGui::Text("Layer : %s", sarea.c_str());
        ImGui::Text("Brush Mode : %s", smode.c_str());
    }
    ImGui::End();
}

void TileMap::GenerateTileMap()
{
    if (width == 0 || height == 0 || spacing == 0)
        assert(false);

    for (uint i = 0; i < 3; i++)
    {
        tiles[i] = new Tile * [height];
        int index = 0;

        for (uint y = 0; y < height; y++)
        {
            tiles[i][y] = new Tile[width];
            for (uint x = 0; x < width; x++)
            {
                tiles[i][y][x].SetPosition(Vector3((float)(x * spacing), (float)(y * spacing), 0.0f));
                tiles[i][y][x].SetIndex(index++);
            }
        }
    }

    
}

void TileMap::MapVertexBuffer()
{
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TileMap::UnmapVertexBuffer()
{
    memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
    DC->Unmap(vb->GetResource(), 0);
}

void TileMap::Save(string path)
{
    ofstream fout(path);

    fout << to_string(width) << ' ' << to_string(height) << ' ' << to_string(spacing)
        << ' ' << "tag" << ' ' << "type" << endl;

    
    for (uint y = 0; y < height; y++)
    {
        
        for (uint x = 0; x < width; x++)
        {
            for (uint i = 0; i < 3; i++)
            {
                Tile& tile = tiles[i][y][x];
                string output;
                output += to_string(tile.GetStartUV().x) + ' ' + to_string(tile.GetStartUV().y) + ' ';
                output += to_string(tile.GetEndUV().x) + ' ' + to_string(tile.GetEndUV().y) + ' ';

                output += to_string(float(tile.GetTag())) + ' ';

                if (tile.GetTag() != BoundingBox::Object && tile.GetTag() != BoundingBox::Monster)
                {
                    output += to_string(float(tile.GetType())) + ' ';
                }
                else if(tile.GetTag() == BoundingBox::Object)
                {
                    output += to_string(float(tile.GetObj())) + ' ';
                }
                else
                {
                    output += to_string(float(tile.GetMonster())) + ' ';
                }

                fout << output;
            }
            fout << endl;
        }
    }
    
}

void TileMap::Load(string path)
{
    ifstream fin(path);

    // Read Width, Height, Spacing
    {
        if (fin.fail())
        {
            cout << "Wrong File" << endl;
            return;
        }

        for (Tile** t : tiles)
        {
            for (uint y = 0; y < height; y++)
                SAFE_DELETE_ARRAY(t[y]);

            SAFE_DELETE_ARRAY(t);
        }

        char temp[256];

        fin.getline(temp, 256);
        string t = "";

        for (int i = 0; i < 256; i++)
        {
            // 받아온 파일에서 (빈칸 또는 NULL) 값이 아니라면 string 타입의 t에 자료 값을 저장한다
            if (temp[i] != ' ' && temp[i] != '\0')
                t += temp[i];
            else
            {
                // 만약 width, height, spacing이 입력되지 않은 상태라면 저장된 값으로 대체하는 코드
                if (width == 0)
                {
                    width = stoi(t); // string을 int로 바꿔줌
                    t.clear();
                }
                else if (height == 0)
                {
                    height = stoi(t);
                    t.clear();
                }
                else if (spacing == 0)
                {
                    spacing = stoi(t);
                }
                continue;
            }
        }

        if (width == 0 || height == 0 || spacing == 0)
            assert(false);



        // width와 height 만큼의 2차원 배열을 생성후 tile 오브젝트를 생성
        tiles[0] = new Tile * [height];
        tiles[1] = new Tile * [height];
        tiles[2] = new Tile * [height];
        int count = 0;

        for (uint y = 0; y < height; y++)
        {
            tiles[0][y] = new Tile[width];
            tiles[1][y] = new Tile[width];
            tiles[2][y] = new Tile[width];

            for (uint x = 0; x < width; x++)
            {
                // 입력된 spacing * spacing 크기의 정사각형 Tile 위치를 설정
                float vx = (float)(x * spacing);
                float vy = (float)(y * spacing);
                // 현재의 tile에 위에서 설정한 위치로 position을 설정
                tiles[0][y][x].SetPosition(Vector3(vx, vy, 0.0f));
                tiles[1][y][x].SetPosition(Vector3(vx, vy, 0.0f));
                tiles[2][y][x].SetPosition(Vector3(vx, vy, 0.0f));
                // 각 타일마다 index를 부여
                tiles[0][y][x].SetIndex(count);
                tiles[1][y][x].SetIndex(count);
                tiles[2][y][x].SetIndex(count++);

                fin.getline(temp, 256);
                Vector2 uv;
                string t = "";

                BoundingBox::Tag _tag;

                int flag = 0;
                for (int i = 0; i < 256; i++)
                {
                    if ((i + 1) % 9 == 0)
                    {
                        switch (flag)
                        {
                            case 0:
                            {
                                uv.x = stof(t);
                                ++flag;
                                break;
                            }
                            case 1:
                            {
                                uv.y = stof(t);
                                ++flag;
                                tiles[0][y][x].SetStartUV(uv);
                                break;
                            }
                            case 2:
                            {
                                uv.x = stof(t);
                                ++flag;
                                break;
                            }
                            case 3:
                            {
                                uv.y = stof(t);
                                ++flag;
                                tiles[0][y][x].SetEndUV(uv);
                                break;
                            }
                            case 4:
                            {
                                _tag = BoundingBox::Tag(stof(t));
                                ++flag;
                                tiles[0][y][x].SetTag(_tag);
                                break;
                            }
                            case 5:
                            {
                                ++flag;
                                if (_tag != BoundingBox::Object && _tag != BoundingBox::Monster)
                                {
                                    tiles[0][y][x].SetType(Type(stof(t)));
                                }
                                else if (_tag == BoundingBox::Object)
                                {
                                    tiles[0][y][x].SetObj(Tile::ObjectType(stof(t)));
                                }
                                else
                                {
                                    tiles[0][y][x].SetMonster(Tile::MonsterType(stof(t)));
                                }
                                break;

                            }
                            case 6:
                            {
                                uv.x = stof(t);
                                ++flag;
                                break;
                            }
                            case 7:
                            {
                                uv.y = stof(t);
                                ++flag;
                                tiles[1][y][x].SetStartUV(uv);
                                break;
                            }
                            case 8:
                            {
                                uv.x = stof(t);
                                ++flag;
                                break;
                            }
                            case 9:
                            {
                                uv.y = stof(t);
                                ++flag;
                                tiles[1][y][x].SetEndUV(uv);
                                break;
                            }
                            case 10:
                            {
                                _tag = BoundingBox::Tag(stof(t));
                                ++flag;
                                tiles[1][y][x].SetTag(_tag);
                                break;
                            }
                            case 11:
                            {
                                ++flag;
                                if (_tag != BoundingBox::Object && _tag != BoundingBox::Monster)
                                {
                                    tiles[1][y][x].SetType(Type(stof(t)));
                                }
                                else if (_tag == BoundingBox::Object)
                                {
                                    tiles[1][y][x].SetObj(Tile::ObjectType(stof(t)));
                                }
                                else
                                {
                                    tiles[1][y][x].SetMonster(Tile::MonsterType(stof(t)));
                                }
                                break;
                                break;

                            }
                            case 12:
                            {
                                uv.x = stof(t);
                                ++flag;
                                break;
                            }
                            case 13:
                            {
                                uv.y = stof(t);
                                ++flag;
                                tiles[2][y][x].SetStartUV(uv);
                                break;
                            }
                            case 14:
                            {
                                uv.x = stof(t);
                                ++flag;
                                break;
                            }
                            case 15:
                            {
                                uv.y = stof(t);
                                ++flag;
                                tiles[2][y][x].SetEndUV(uv);
                                break;
                            }
                            case 16:
                            {
                                _tag = BoundingBox::Tag(stof(t));
                                ++flag;
                                tiles[2][y][x].SetTag(_tag);
                                break;
                            }
                            case 17:
                            {
                                ++flag;
                                if (_tag != BoundingBox::Object && _tag != BoundingBox::Monster)
                                {
                                    tiles[2][y][x].SetType(Type(stof(t)));
                                }
                                else if (_tag == BoundingBox::Object)
                                {
                                    tiles[2][y][x].SetObj(Tile::ObjectType(stof(t)));
                                }
                                else
                                {
                                    tiles[2][y][x].SetMonster(Tile::MonsterType(stof(t)));
                                }
                                break;
                                break;

                            }

                        }
                        t.clear();
                        continue;

                    }
                    else
                    {
                        t += temp[i];

                    }
                }

            }
        }

    }

}

Tile* TileMap::GetTile(Vector3 mPos)
{
    uint x = (int)mPos.x / spacing;
    uint y = (int)mPos.y / spacing;

    xcount = x;
    ycount = y;

    if (x < 0 || x >= width || y < 0 || y >= height)
        return nullptr;

    return &tiles[AreaMode][y][x];
}
