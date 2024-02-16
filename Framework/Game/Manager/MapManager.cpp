#include "Framework.h"
#include "MapManager.h"


MapManager::MapManager()
{
    spacing = 40;
    width = (MapWidth) / spacing;
    height = (MapHeight) / spacing;

    fs.push_back(vector<FootHolder*>());
    fs.push_back(vector<FootHolder*>());
    fs.push_back(vector<FootHolder*>());

    TileSet::Create();

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
    vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

    ps = new PixelShader();
    ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");

    il = new InputLayout();
    il->Create(VertexTile::descs, VertexTile::count, vs->GetBlob());

    wb = new WorldBuffer();
    wb->SetWorld(world);

    FirstPoint = { 0,0,0 };
    SecondPoint = { 0,0,0 };
}


void MapManager::Destroy()
{
    SAFE_DELETE(portal);

    for (auto m : ms)
    {
        SAFE_DELETE(m);
    }

    for (auto f : fs)
        for (auto a : f)
            SAFE_DELETE(a);

    SAFE_DELETE(wb);

    SAFE_DELETE(il);
    SAFE_DELETE(ps);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);


    TileSet::Delete();
}

void MapManager::OnIsActive()
{
    if (!(_activeState[0] == OFF) || !(_activeState[1] == ON))
        return;

    {
        // 활성화할 시 사용할 코드

    }

    _activeState[0] = ON;
}

void MapManager::Update()
{
    deltaTime = Time::Get()->WorldDelta();

    for (auto a : fs[1])
    {
        if(a->GetCollision() != nullptr || a->GetTag() == BoundingBox::Object)
            a->Update();
    }

    allmonsterdie = true;

    for (auto m : ms)
    {
        m->Update();

        if (!m->IsDie())
            allmonsterdie = false;
    }

    // 몬스터가 모두 죽을때 실행될 코드
    {
        if (portal != nullptr)
        {
            if (allmonsterdie && !isClear)
            {
                Sounds::Get()->Play("paper2", 1.0f);
                isClear = true;
                portal->SetOn();
            }

            portal->Update();

            if (portal->IsNext())
                isNext = true;
            else
                isNext = false;
        }
    }

    

    BackGroundSight();
}

void MapManager::Render()
{
   
    Vector3 cmpos = Camera::Get()->GetPosition();
    Vector2 cmsize = Camera::Get()->GetCameraSize();


    for (auto fl : fs)
    {
        for (FootHolder* f : fl)
        {
            if (f->GetPos().x >= cmpos.x - 40 && f->GetPos().x <= cmpos.x + cmsize.x && f->GetPos().y >= cmpos.y - 40 && f->GetPos().y <= cmpos.y + cmsize.y)
            {
                if (f->GetTag() != BoundingBox::Object)
                {
                    vb->SetIA();
                    ib->SetIA();
                    il->SetIA();
                    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

                    vs->SetShader();
                    ps->SetShader();

                    DC->PSSetShaderResources(0, 1, &TileSet::Get()->tileSRV);

                    MapVertexBuffer();
                    {
                        for (VertexTile& v : vertices)
                        {
                            v.color = f->GetColor();
                        }

                        vertices[0].uv = Vector2(f->GetStartUV().x, f->GetEndUV().y);
                        vertices[1].uv = f->GetStartUV();
                        vertices[2].uv = f->GetEndUV();
                        vertices[3].uv = Vector2(f->GetEndUV().x, f->GetStartUV().y);

                        vertices[0].uv2 = Vector2(0, 1);
                        vertices[1].uv2 = Vector2(0, 0);
                        vertices[2].uv2 = Vector2(1, 1);
                        vertices[3].uv2 = Vector2(1, 0);
                    }
                    UnmapVertexBuffer();

                    world = DXMath::Translation(f->GetPos());
                    wb->SetWorld(world);
                    wb->SetVSBuffer(0);
                    DC->DrawIndexed(ib->GetCount(), 0, 0);
                }
                else if (f->GetTag() == BoundingBox::Object)
                {
                    f->Render();
                }
            }
            
        }
       
    }

    //// 이거 콜리젼 렌더니까 나중에 지워버리면 됩니다.
    //for (auto a : fs[1])
    //{
    //    if (a->GetCollision() != nullptr)
    //        a->Render();
    //}
    
    for (Monster* m : ms)
    {
        m->Render();
    }

    if(portal != nullptr)
        portal->Render();
}

void MapManager::PostRender()
{
    for (auto fl : fs)
    {
        for (FootHolder* f : fl)
        {
            if (f->GetTag() != BoundingBox::Object)
                continue;

            f->PostRender();
        }
    }
    if (isClear)
    {
        Text::Get()->BeginDraw();
        {
            wstring str = L"Portal is open!";
            float size = 40;
            Vector2 pos = Vector2(510, 50);
            Text::Get()->RenderText(str, pos, Color(1, 1, 1, NoticeTime), size, true);
        }
        Text::Get()->EndDraw();


        if (NoticeTime > 0.f)
            NoticeTime -= deltaTime * 0.2f;
    }
    
}


void MapManager::BackGroundSight()
{
    Vector3 position = Camera::Get()->GetPosition();

    for (auto m : map)
    {
        float x, y, z;

        x = (MapSize.x - m->GetSize().x) / (MapSize.x - Camera::Get()->GetCameraSize().x) * position.x;
        y = position.y;
        z = 0.f;

        m->Update({ x, y, z }, m->GetSize(), 0.f);
    }
}

void MapManager::MapVertexBuffer()
{
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void MapManager::UnmapVertexBuffer()
{
    memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
    DC->Unmap(vb->GetResource(), 0);
}

void MapManager::CreateObject(Tile::ObjectType type, Vector3 position, int num)
{
    
    switch (Tile::ObjectType(type))
    {
        case Tile::NoneObj:
        {

            break;
        }
        case Tile::RightMoveFloor:
        {
            CrystalMoveFloor* a = new CrystalMoveFloor({ position.x + 20.f, position.y + 50.f, 0.f }, 1.f);
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::LeftMoveFloor:
        {
            CrystalMoveFloor* a = new CrystalMoveFloor({ position.x + 20.f, position.y + 50.f, 0.f }, -1.f);
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::Portal:
        {
            Portal* a = new Portal({ position.x + 20.f, position.y, 0.f }, -1.f);
            a->SetTag(BoundingBox::Object);

            portal = a;

            break;
        }
        case Tile::LeftRightFloor:
        {
            MoveFloor* a = new MoveFloor({ position.x + 20.f, position.y + 25.f, 0.f }, 1.f);
            a->SetTag(BoundingBox::Object);

            PUSH_Floor(fs[num], a);

            break;
        }
        case Tile::RightUpFloor:
        {
            CrystalUpDownFloor* a = new CrystalUpDownFloor({ position.x + 20.f, position.y + 50.f, 0.f }, 1.f);
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::LeftUpFloor:
        {
            CrystalUpDownFloor* a = new CrystalUpDownFloor({ position.x + 20.f, position.y + 50.f, 0.f }, -1.f);
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::UpDownFloor:
        {
            UpDownFloor* a = new UpDownFloor({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::BigTree1:
        {
            BigTree1* a = new BigTree1({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::BigTree2:
        {
            BigTree2* a = new BigTree2({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::BigTree3:
        {
            BigTree3* a = new BigTree3({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::SmallTree1:
        {
            SmallTree1* a = new SmallTree1({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::SmallTree2:
        {
            SmallTree2* a = new SmallTree2({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::SmallTree3:
        {
            SmallTree3* a = new SmallTree3({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::Root1:
        {
            Root1* a = new Root1({ position.x + 20.f, position.y + 20.f, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::Root2:
        {
            Root2* a = new Root2({ position.x + 20.f, position.y + 20.f, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::Root3:
        {
            Root3* a = new Root3({ position.x + 20.f, position.y + 20.f, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        } 
        case Tile::Shop:
        {
            Shop* a = new Shop({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        case Tile::UpgradeNPC:
        {
            UpgradeNPC* a = new UpgradeNPC({ position.x + 20.f, position.y, 0.f });
            a->SetTag(BoundingBox::Object);
            PUSH_Floor(fs[num], a);
            break;
        }
        default:
            break;
    }

        
}

void MapManager::LoadMap(string path)
{
    ifstream fin(path);

    // Read Width, Height, Spacing
    {
        if (fin.fail())
        {
            cout << "Wrong File" << endl;
            return;
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

        int count = 0;

        for (uint y = 0; y < height; y++)
        {
            for (uint x = 0; x < width; x++)
            {
                // 입력된 spacing * spacing 크기의 정사각형 Tile 위치를 설정
                float vx = (float)(x * spacing);
                float vy = (float)(y * spacing);
                fin.getline(temp, 256);

                Vector2 suv[3] = {};
                Vector2 euv[3] = {};

                string t;

                BoundingBox::Tag _tag[3] = {};
                Type _type[3] = {};
                Tile::ObjectType objtype[3] = {};
                Tile::MonsterType msttype[3] = {};

                int flag = 0;
                for (int i = 0; i < 256; i++)
                {
                    if ((i + 1) % 9 == 0)
                    {
                        switch (flag)
                        {
                            case 0:
                            {
                                suv[0].x = stof(t);
                                ++flag;
                                break;
                            }
                            case 1:
                            {
                                suv[0].y = stof(t);
                                ++flag;
                                break;
                            }
                            case 2:
                            {
                                euv[0].x = stof(t);
                                ++flag;
                                break;
                            }
                            case 3:
                            {
                                euv[0].y = stof(t);
                                ++flag;
                                break;
                            }
                            case 4:
                            {
                                _tag[0] = BoundingBox::Tag(stof(t));
                                ++flag;
                                break;
                            }
                            case 5:
                            {
                                if (_tag[0] != BoundingBox::Object && _tag[0] != BoundingBox::Monster)
                                {
                                    _type[0] = Type(stof(t));
                                }
                                else if (_tag[0] == BoundingBox::Object)
                                {
                                    objtype[0] = Tile::ObjectType(stof(t));
                                }
                                else
                                {
                                    msttype[0] = Tile::MonsterType(stof(t));
                                }
                                ++flag;
                                break;

                            }
                            case 6:
                            {
                                suv[1].x = stof(t);
                                ++flag;
                                break;
                            }
                            case 7:
                            {
                                suv[1].y = stof(t);
                                ++flag;
                                break;
                            }
                            case 8:
                            {
                                euv[1].x = stof(t);
                                ++flag;
                                break;
                            }
                            case 9:
                            {
                                euv[1].y = stof(t);
                                ++flag;
                                break;
                            }
                            case 10:
                            {
                                _tag[1] = BoundingBox::Tag(stof(t));
                                ++flag;
                                break;
                            }
                            case 11:
                            {
                                if (_tag[1] != BoundingBox::Object && _tag[1] != BoundingBox::Monster)
                                {
                                    _type[1] = Type(stof(t));
                                }
                                else if(_tag[1] == BoundingBox::Object)
                                {
                                    objtype[1] = Tile::ObjectType(stof(t));
                                }
                                else
                                {
                                    msttype[1] = Tile::MonsterType(stof(t));
                                }
                                ++flag;
                                break;

                            }
                            case 12:
                            {
                                suv[2].x = stof(t);
                                ++flag;
                                break;
                            }
                            case 13:
                            {
                                suv[2].y = stof(t);
                                ++flag;
                                break;
                            }
                            case 14:
                            {
                                euv[2].x = stof(t);
                                ++flag;
                                break;
                            }
                            case 15:
                            {
                                euv[2].y = stof(t);
                                ++flag;
                                break;
                            }
                            case 16:
                            {
                                _tag[2] = BoundingBox::Tag(stof(t));
                                ++flag;
                                break;
                            }
                            case 17:
                            {
                                if (_tag[2] != BoundingBox::Object && _tag[2] != BoundingBox::Monster)
                                {
                                    _type[2] = Type(stof(t));
                                }
                                else if (_tag[2] == BoundingBox::Object)
                                {
                                    objtype[2] = Tile::ObjectType(stof(t));
                                }
                                else
                                {
                                    msttype[2] = Tile::MonsterType(stof(t));
                                }
                                ++flag;
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

                for (int i = 0; i < 3; i++)
                {
                    switch (i)
                    {
                        case 0:
                        {
                            switch (_tag[i])
                            {
                                case BoundingBox::Object:
                                {
                                    CreateObject(objtype[i], { vx, vy, 0.f }, i);
                                    break;
                                }
                                default:
                                {
                                    if ((euv[i] != Values::ZeroVec2))
                                    {
                                        BackFloor* back = new BackFloor({ vx, vy, 0.f }, { (float)spacing, (float)spacing, 1.f }, 0.f);

                                        back->SetStartUV(suv[i]);
                                        back->SetEndUV(euv[i]);

                                        PUSH_Floor(fs[i], back);
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                            
                        
                        case 1:
                        {
                            switch (_tag[i])
                            {
                                case BoundingBox::BackFloor:
                                {
                                    BackFloor* back = new BackFloor({ vx, vy, 0.f }, { (float)spacing, (float)spacing, 1.f }, 0.f);

                                    back->SetStartUV(suv[i]);
                                    back->SetEndUV(euv[i]);

                                    PUSH_Floor(fs[i], back);

                                    break;
                                }
                                case BoundingBox::Player:
                                {
                                    FirstPoint = { vx, vy, 0.f };
                                    break;
                                }
                                case BoundingBox::Monster:
                                {
                                    switch (Tile::MonsterType(msttype[i]))
                                    {
                                        case Tile::Bringer:
                                        {
                                            Bringer* m = new Bringer({ vx, vy, 0.f }, 0.f);
                                            PUSH_Monster(m);
                                            break;
                                        }
                                        case Tile::MudGuard:
                                        {
                                            MudGuard* m = new MudGuard({ vx, vy, 0.f }, 0.f);
                                            PUSH_Monster(m);
                                            break;
                                        }
                                        case Tile::BombDroid:
                                        {
                                            BombDroid* m = new BombDroid({ vx, vy, 0.f }, 0.f);
                                            PUSH_Monster(m);
                                            break;
                                        }
                                        case Tile::ShadowMage:
                                        {
                                            ShadowMage* m = new ShadowMage({ vx, vy, 0.f }, 0.f);
                                            PUSH_Monster(m);
                                            break;
                                        }
                                        case Tile::ShadowStalker:
                                        {
                                            ShadowStalker* m = new ShadowStalker({ vx, vy, 0.f }, 0.f);
                                            PUSH_Monster(m);
                                            break;
                                        }
                                        default:
                                            break;
                                        }

                                    break;
                                }
                                case BoundingBox::Item:
                                {

                                    break;
                                }
                                case BoundingBox::Floor:
                                {
                                    Floor* fl = new Floor({ vx, vy, 0.f }, { (float)spacing, (float)spacing, 1.f }, 0.f, _type[i]);

                                    fl->SetStartUV(suv[i]);
                                    fl->SetEndUV(euv[i]);

                                    PUSH_Floor(fs[i], fl);

                                    break;
                                }
                                case BoundingBox::Object:
                                {

                                    CreateObject(objtype[i], { vx, vy, 0.f }, i);
                                    break;
                                }
                                default:
                                {

                                    break;
                                }
                            }
                            break;
                        }
                        case 2:
                        {
                            switch (_tag[i])
                            {
                                case BoundingBox::Object:
                                {
                                    CreateObject(objtype[i], { vx, vy, 0.f }, i);
                                    break;
                                }
                                default:
                                {
                                    if ((euv[i] != Values::ZeroVec2))
                                    {
                                        BackFloor* back = new BackFloor({ vx, vy, 0.f }, { (float)spacing, (float)spacing, 1.f }, 0.f);

                                        back->SetStartUV(suv[i]);
                                        back->SetEndUV(euv[i]);

                                        PUSH_Floor(fs[i], back);
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    
                       
                    
                }
                
                


            }
        }
    }
}

// Map Off 역할
void MapManager::Init()
{
    Sounds::Get()->Stop(MusicName);

    for (auto fl : fs)
    {
        for (auto f : fl)
            f->Init();
    }

    for (auto m : ms)
        m->Init();

    if (portal != nullptr)
    {
        portal->Init();
    }

    deltaTime = 0.f;
    NoticeTime = 1.f;
    isClear = false;
}

void MapManager::MapOn()
{
    Sounds::Get()->Play(MusicName, 0.1f);

    for (auto fl : fs)
    {
        for (auto f : fl)
            f->OnActive();
    }

    for (auto m : ms)
        m->OnActive();

    if (portal != nullptr)
    {
        portal->OnActive();
    }
}
