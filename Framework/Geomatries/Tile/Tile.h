#pragma once
#include "Utilities/BoundingBox.h"



class Tile
{
public:
    enum ObjectType
    {
        NoneObj,
        RightMoveFloor,
        LeftMoveFloor,
        Portal,
        LeftRightFloor,
        RightUpFloor,
        LeftUpFloor,
        UpDownFloor,
        BigTree1,
        BigTree2,
        BigTree3,
        SmallTree1,
        SmallTree2,
        SmallTree3,
        Root1,
        Root2,
        Root3,
        Shop,
        UpgradeNPC,

    };

    enum MonsterType
    {
        Bringer = 0,
        MudGuard,
        BombDroid,
        ShadowMage,
        ShadowStalker,

    };

public:
    void SetPosition(Vector3 position) { this->position = position; }
    void SetStartUV(Vector2 startUV) { this->startUV = startUV; }
    void SetEndUV(Vector2 endUV) { this->endUV = endUV; }
    void SetColor(Color color) { this->color = color; }
    void SetIndex(uint index) { this->index = index; }
    void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

    void SetType(Type type) { this->type = type; }
    void SetTag(BoundingBox::Tag tag) { this->tag = tag; }
    void SetObj(ObjectType objtype) { this-> objtype = objtype; }
    void SetMonster(MonsterType msttype) { this-> msttype = msttype; }


    Vector3 GetPosition() { return position; }
    Vector2 GetStartUV() { return startUV; }
    Vector2 GetEndUV() { return endUV; }
    Color GetColor() { return color; }
    uint GetIndex() { return index; }

    Type GetType() { return type; }
    BoundingBox::Tag GetTag() { return tag; }
    ObjectType GetObj() { return objtype; }
    MonsterType GetMonster() { return msttype; }


    ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
    Vector3 position = Values::ZeroVec3;
    Color color = Values::Black;

    Type type = UpPass;
    BoundingBox::Tag tag = BoundingBox::None;
    ObjectType objtype = NoneObj;
    MonsterType msttype = MudGuard;

    Vector2 startUV = Values::ZeroVec2;
    Vector2 endUV = Values::ZeroVec2;

    ID3D11ShaderResourceView* srv = nullptr;

    uint index = -1;
};