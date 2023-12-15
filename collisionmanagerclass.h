#pragma once
#include "colliderclass.h"

class CollisionManagerClass
{
public:
    static bool CheckCollisionSphereColliders(ColliderClass* col1, ColliderClass* col2)
    {
        XMFLOAT3 center1, center2;
        center1 = col1->GetCenter();
        center2 = col2->GetCenter();
        float distanceSquare = 
            (center1.x - center2.x) * (center1.x - center2.x) +
            (center1.y - center2.y) * (center1.y - center2.y) + 
            (center1.z - center2.z) * (center1.z - center2.z);
        
        float radiusSquare = (col1->GetRadius() + col2->GetRadius()) * (col1->GetRadius() + col2->GetRadius());
    
        if (radiusSquare > distanceSquare) return true;
        else return false;
    }
};

