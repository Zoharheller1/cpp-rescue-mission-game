#include "CollisionHandling.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Scenery.h"
#include "Player.h"
#include "Cannon.h"
#include "Guard.h"
#include "suicideBomber.h"
#include "Bullets.h"
#include "HouseWithoutPrisoner.h"
#include "HouseWithPrisoner.h"
#include "PlayerBullet.h"
#include "Prisioner.h"
#include "SimpleSolider.h"
#include "Passers.h"
#include "HeavyArtilleryBullet.h"
#include "Gate.h"
#include "PresentGun.h"
#include "Grende.h"
#include "Tank.h"
#include "Rifle.h"
#include "Helicopter.h"
#include "PresentShild.h"
#include "PresentLife.h"
#include "PresentTime.h"
#include"Spot.h"

namespace
{


    void playerSeeking(Object& obj1, Object& obj2)
    {
        DynamicActives& active = static_cast<DynamicActives&>(obj2);
        Player& player = static_cast<Player&>(obj1);

        if (!active.collision(0.07f, 10))player.SetLocation(player.performBackPosition());
    }
    void SeekingPlayer(Object& obj1, Object& obj2) { playerSeeking(obj2, obj1); }

    void playerBulletWeapon(Object& obj1, Object& obj2)
    {
        PlayerBullet& bullet = static_cast<PlayerBullet&>(obj1);
        PlayerSeeking& seeking = static_cast<PlayerSeeking&>(obj2);
        if (bullet.colide(seeking.getPosition(), Action::MEDIUMBOMBER, 0.8f))
            seeking.collision(0.f, 10);
    }
    void playerBulletActiveEnemy(Object& obj1, Object& obj2)
    {
        DynamicActives& activeEnemy = static_cast<DynamicActives&>(obj2);
        PlayerBullet& bullet = static_cast<PlayerBullet&>(obj1);
        if (bullet.colide(activeEnemy.getPosition(), Action::SMALLBOMBER, 0.3f))
        {

            activeEnemy.collision(0.2f, 10);
        }
    }
    void activeEnemyPlayerBullet(Object& obj1, Object& obj2)
    {
        playerBulletActiveEnemy(obj2, obj1);
    }

    void weaponPlayerBullet(Object& obj1, Object& obj2)
    {
        playerBulletWeapon(obj2, obj1);
    }


    void backPosition(Object& obj1, Object& obj2)
    {
        Active& active = static_cast<Active&>(obj2);
        active.SetLocation(active.performBackPosition());
    }
    void Positionback(Object& obj1, Object& obj2) { backPosition(obj2, obj1); }

    void playerSuicde(Object& obj1, Object& obj2)
    {
        suicideBomber& suicide = static_cast<suicideBomber&>(obj2);
        Player& player = static_cast<Player&>(obj1);
        if (suicide.collisionWithPlayer())
        {
            player.setSituation(0.7f);
            player.updateLife(20);
        }
    }

    void playerBulletHouse(Object& obj1, Object& obj2)
    {
        ReplacePicture& house = static_cast<ReplacePicture&>(obj2);
        Bullet& bullet = static_cast<Bullet&>(obj1);
        if (bullet.isAlive())
        {
            house.handleCollisionWithBullet();
            bullet.colide(house.getPosition(), Action::BIGBOMBER, 0.9f);
        }
    }
    void HousePlayerBullet(Object& obj1, Object& obj2) { playerBulletHouse(obj2, obj1); }

    void HousewithoutPlayer(Object& obj1, Object& obj2) { Positionback(obj1, obj2); }

    void playerHousewithout(Object& obj1, Object& obj2) { backPosition(obj2, obj1); }

    void suicdeplayer(Object& obj1, Object& obj2) { playerSuicde(obj2, obj1); }

    void playerHouse(Object& obj1, Object& obj2) { backPosition(obj2, obj1); }

    void HousePlayer(Object& obj1, Object& obj2) { backPosition(obj1, obj2); }

    void playerEnemyBullet(Object& obj1, Object& obj2)
    {
        Player& player = static_cast<Player&>(obj1);
        HeavyArtilleryBullet& bullet = static_cast<HeavyArtilleryBullet&>(obj2);
        if (bullet.colide(player.getPosition(), Action::SMALLBOMBER, 0.1f))
        {
            player.setSituation(0.1f);
            player.updateLife(12);
        }

    }
    void playerRifle(Object& obj1, Object& obj2)
    {
        Player& player = static_cast<Player&>(obj1);
        Rifle& bullet = static_cast<Rifle&>(obj2);
        if (bullet.colide(player.getPosition(), Action::SMALLBOMBER, 0.1f))
        {
            player.setSituation(0.1f);
            player.updateLife(1);
        }
    }
    void riflePlayer(Object& obj1, Object& obj2)
    {
        playerRifle(obj2, obj1);
    }

    void playerPresentShild(Object& obj1, Object& obj2)
    {
        Player& player = static_cast<Player&>(obj1);
        player.ShildBegin();
        PresentShild& shild = static_cast<PresentShild&>(obj2);
        shild.deadObject();
    }
    void presentShildPlayer(Object& obj1, Object& obj2)
    {
        playerPresentShild(obj2, obj1);
    }



    void EnemyBulletPlayer(Object& obj1, Object& obj2) { playerEnemyBullet(obj2, obj1); }

    void  playerPrisoner(Object& obj1, Object& obj2)
    {
        PlayerSeeking& prisioner = static_cast<PlayerSeeking&>(obj2);
        Player& player = static_cast<Player&>(obj1);

        if (prisioner.collision(0.f, 1)) player.addPrisioner();
    }

    void  PrisionerPlayer(Object& obj1, Object& obj2) { playerPrisoner(obj2, obj1); }

    void grendeGate(Object& obj1, Object& obj2)
    {
        PlayerBullet& playerBullet = static_cast<PlayerBullet&>(obj1);
        Gate& gate = static_cast<Gate&>(obj2);
        gate.handleCollisionWithBullet();
        playerBullet.colide(gate.getPosition(), Action::DEAD, 0.8f);
    }

    void playerPresentGun(Object& obj1, Object& obj2)
    {
        PresentGun& presentGun = static_cast<PresentGun&>(obj2);
        presentGun.deadObject();
        Player& player = static_cast<Player&>(obj1);
        player.addGrendes();
    }

    void presentGunPlayer(Object& obj1, Object& obj2)
    {
        playerPresentGun(obj2, obj1);
    }
    void bulletWithStatic(Object& obj1, Object& obj2)
    {
        Bullet& bullet = static_cast<Bullet&>(obj1);
        bullet.collision(0.f, 1);
    }
    void staticWithBullet(Object& obj1, Object& obj2) { bulletWithStatic(obj2, obj1); }
    void grendeWeapon(Object& obj1, Object& obj2)
    {
        Grende& bullet = static_cast<Grende&>(obj1);
        DynamicActives& active = static_cast<DynamicActives&>(obj2);
        if (bullet.colide(active.getPosition(), Action::DEAD, 0.8f))
        {
            active.collision(0.f, 25);
        }
    }

    void weaponGrende(Object& obj1, Object& obj2) { grendeWeapon(obj2, obj1); }
    void killPlayer(Object& obj1, Object& obj2)
    {
        Player& player = static_cast<Player&>(obj1);
        player.updateLife(0.09);
    }
    void playerKilled(Object& obj1, Object& obj2) { killPlayer(obj2, obj1); }


    void gateGrende(Object& obj1, Object& obj2) { grendeGate(obj2, obj1); }

    void Object1Object2(Object& obj1, Object& obj2)
    {
        DynamicActives& active = static_cast<DynamicActives&>(obj1);
        Object& Obj = static_cast<Object&>(obj2);

        active.returnBack(Obj);
    }
    void Object2Object1(Object& obj1, Object& obj2) { Object1Object2(obj2, obj1); }
    void returnBack(Object& obj1, Object& obj2)
    {
        Player& player = static_cast<Player&>(obj1);
        Object& object = static_cast<Object&>(obj2);
        player.returnBack(object);
    }
    void beckReturn(Object& obj1, Object& obj2) { returnBack(obj2, obj1); }

    void playerPresentTime(Object& obj1, Object& obj2)
    {
        PresentGun& presentGun = static_cast<PresentGun&>(obj2);
        presentGun.deadObject();
        Player& player = static_cast<Player&>(obj1);
        player.addTime();

    }
    void presentTimePlayer(Object& obj1, Object& obj2)
    {
        playerPresentTime(obj2, obj1);
    }
    void playerPresentLife(Object& obj1, Object& obj2)
    {
        Player& player = static_cast<Player&>(obj1);
        player.addLife();
        PresentLife& life = static_cast<PresentLife&>(obj2);
        life.deadObject();
    }
    void presentLifePlayer(Object& obj1, Object& obj2)
    {
        playerPresentLife(obj2, obj1);
    }

    void playerSpot(Object& obj1, Object& obj2)
    {
        Player& player = static_cast<Player&>(obj1);
        player.spotPosition();
    }
    void spotPlayer(Object& obj1, Object& obj2) { playerSpot(obj2, obj1); }


    using HitFunctionPtr = void (*)(Object&, Object&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;



        phm[Key(typeid(suicideBomber), typeid(Grende))] = &weaponGrende;//
        phm[Key(typeid(Grende), typeid(suicideBomber))] = &grendeWeapon;

        phm[Key(typeid(Player), typeid(Gate))] = &Positionback;//
        phm[Key(typeid(Gate), typeid(Player))] = &backPosition;

        phm[Key(typeid(Player), typeid(Helicopter))] = &Positionback;//
        phm[Key(typeid(Helicopter), typeid(Player))] = &backPosition;

        phm[Key(typeid(Tank), typeid(Tank))] = &Object1Object2;//
        phm[Key(typeid(Tank), typeid(Tank))] = &Object2Object1;

        phm[Key(typeid(SimpleSolider), typeid(Helicopter))] = &Object1Object2;//
        phm[Key(typeid(Helicopter), typeid(SimpleSolider))] = &Object2Object1;

        phm[Key(typeid(Tank), typeid(Helicopter))] = &Object1Object2;//
        phm[Key(typeid(Helicopter), typeid(Tank))] = &Object2Object1;

        phm[Key(typeid(Passers), typeid(Helicopter))] = &Object1Object2;//
        phm[Key(typeid(Helicopter), typeid(Passers))] = &Object2Object1;

        phm[Key(typeid(SimpleSolider), typeid(Gate))] = &Object1Object2;//
        phm[Key(typeid(Gate), typeid(SimpleSolider))] = &Object2Object1;

        phm[Key(typeid(SimpleSolider), typeid(Scenery))] = &Object1Object2;//
        phm[Key(typeid(Scenery), typeid(SimpleSolider))] = &Object2Object1;

        phm[Key(typeid(SimpleSolider), typeid(HouseWithoutPrisoner))] = &Object1Object2;//
        phm[Key(typeid(HouseWithoutPrisoner), typeid(SimpleSolider))] = &Object2Object1;

        phm[Key(typeid(SimpleSolider), typeid(HouseWithPrisoner))] = &Object1Object2;//
        phm[Key(typeid(HouseWithPrisoner), typeid(SimpleSolider))] = &Object2Object1;

        phm[Key(typeid(suicideBomber), typeid(HouseWithoutPrisoner))] = &Object1Object2;//
        phm[Key(typeid(HouseWithoutPrisoner), typeid(suicideBomber))] = &Object2Object1;

        phm[Key(typeid(suicideBomber), typeid(HouseWithPrisoner))] = &Object1Object2;//
        phm[Key(typeid(HouseWithPrisoner), typeid(suicideBomber))] = &Object2Object1;

        phm[Key(typeid(Passers), typeid(HouseWithoutPrisoner))] = &Object1Object2;//
        phm[Key(typeid(HouseWithoutPrisoner), typeid(Passers))] = &Object2Object1;

        phm[Key(typeid(Passers), typeid(HouseWithPrisoner))] = &Object1Object2;//
        phm[Key(typeid(HouseWithPrisoner), typeid(Passers))] = &Object2Object1;

        phm[Key(typeid(Tank), typeid(HouseWithoutPrisoner))] = &Object1Object2;//
        phm[Key(typeid(HouseWithoutPrisoner), typeid(Tank))] = &Object2Object1;

        phm[Key(typeid(Tank), typeid(HouseWithPrisoner))] = &Object1Object2;//
        phm[Key(typeid(HouseWithPrisoner), typeid(Tank))] = &Object2Object1;

        phm[Key(typeid(Tank), typeid(Scenery))] = &Object1Object2;//
        phm[Key(typeid(Scenery), typeid(Tank))] = &Object2Object1;

        phm[Key(typeid(Tank), typeid(Cannon))] = &Object1Object2;//
        phm[Key(typeid(Cannon), typeid(Tank))] = &Object2Object1;

        phm[Key(typeid(Gate), typeid(Tank))] = &Object2Object1;//
        phm[Key(typeid(Tank), typeid(Gate))] = &Object1Object2;

        phm[Key(typeid(Player), typeid(Cannon))] = &returnBack;
        phm[Key(typeid(Cannon), typeid(Player))] = &beckReturn;

        phm[Key(typeid(Player), typeid(Tank))] = &killPlayer;//
        phm[Key(typeid(Tank), typeid(Player))] = &playerKilled;

        phm[Key(typeid(Player), typeid(HeavyArtilleryBullet))] = &playerEnemyBullet;///life player -12
        phm[Key(typeid(HeavyArtilleryBullet), typeid(Player))] = &EnemyBulletPlayer;

        phm[Key(typeid(PlayerBullet), typeid(Cannon))] = &playerBulletWeapon;//life cannon -10
        phm[Key(typeid(Cannon), typeid(PlayerBullet))] = &weaponPlayerBullet;

        phm[Key(typeid(PlayerBullet), typeid(Tank))] = &playerBulletWeapon;//life cannon -10
        phm[Key(typeid(Tank), typeid(PlayerBullet))] = &weaponPlayerBullet;

        phm[Key(typeid(Grende), typeid(Cannon))] = &grendeWeapon;
        phm[Key(typeid(Cannon), typeid(Grende))] = &weaponGrende;

        phm[Key(typeid(Grende), typeid(Tank))] = &grendeWeapon;
        phm[Key(typeid(Tank), typeid(Grende))] = &weaponGrende;

        phm[Key(typeid(Grende), typeid(Passers))] = &grendeWeapon;
        phm[Key(typeid(Passers), typeid(Grende))] = &weaponGrende;

        phm[Key(typeid(Grende), typeid(SimpleSolider))] = &grendeWeapon;
        phm[Key(typeid(SimpleSolider), typeid(Grende))] = &weaponGrende;

        phm[Key(typeid(Player), typeid(suicideBomber))] = &playerSuicde;//life player -20
        phm[Key(typeid(suicideBomber), typeid(Player))] = &suicdeplayer;

        phm[Key(typeid(suicideBomber), typeid(Scenery))] = &Object1Object2;//backPosition/////////////////////////////////
        phm[Key(typeid(Scenery), typeid(suicideBomber))] = &Object2Object1;

        phm[Key(typeid(suicideBomber), typeid(Tank))] = &Object1Object2;//backPosition/////////////////////////////////
        phm[Key(typeid(Tank), typeid(suicideBomber))] = &Object2Object1;

        phm[Key(typeid(SimpleSolider), typeid(Tank))] = &Object1Object2;//backPosition/////////////////////////////////
        phm[Key(typeid(Tank), typeid(SimpleSolider))] = &Object2Object1;

        phm[Key(typeid(Passers), typeid(Tank))] = &Object1Object2;//
        phm[Key(typeid(Tank), typeid(Passers))] = &Object2Object1;

        phm[Key(typeid(Tank), typeid(Guard))] = &Object1Object2;//
        phm[Key(typeid(Guard), typeid(Tank))] = &Object2Object1;

        phm[Key(typeid(SimpleSolider), typeid(Cannon))] = &Object1Object2;//
        phm[Key(typeid(Cannon), typeid(SimpleSolider))] = &Object2Object1;

        // phm[Key(typeid(Passers), typeid(Tank))] = &Object1Object2;//
         //phm[Key(typeid(Tank), typeid(Passers))] = &Object2Object1;

        phm[Key(typeid(Passers), typeid(Cannon))] = &Object1Object2;//
        phm[Key(typeid(Cannon), typeid(Passers))] = &Object2Object1;

        phm[Key(typeid(suicideBomber), typeid(Gate))] = &Object1Object2;//
        phm[Key(typeid(Gate), typeid(suicideBomber))] = &Object2Object1;

        phm[Key(typeid(Player), typeid(Scenery))] = &Positionback;//backPosition
        phm[Key(typeid(Scenery), typeid(Player))] = &backPosition;

        //////////////////////////////////////////////////////////////////////

        phm[Key(typeid(Player), typeid(Guard))] = &playerSeeking;//life guard -10
        phm[Key(typeid(Guard), typeid(Player))] = &SeekingPlayer;

        phm[Key(typeid(Player), typeid(HouseWithPrisoner))] = &playerHouse;//
        phm[Key(typeid(HouseWithPrisoner), typeid(Player))] = &HousePlayer;

        phm[Key(typeid(PlayerBullet), typeid(HouseWithPrisoner))] = &playerBulletHouse;//
        phm[Key(typeid(HouseWithPrisoner), typeid(PlayerBullet))] = &HousePlayerBullet;

        phm[Key(typeid(Grende), typeid(HouseWithPrisoner))] = &playerBulletHouse;//
        phm[Key(typeid(HouseWithPrisoner), typeid(Grende))] = &HousePlayerBullet;

        phm[Key(typeid(PlayerBullet), typeid(HouseWithoutPrisoner))] = &playerBulletHouse;//
        phm[Key(typeid(HouseWithoutPrisoner), typeid(PlayerBullet))] = &HousePlayerBullet;

        phm[Key(typeid(Player), typeid(HouseWithoutPrisoner))] = &playerHousewithout;//
        phm[Key(typeid(HouseWithoutPrisoner), typeid(Player))] = &HousewithoutPlayer;


        phm[Key(typeid(Grende), typeid(HouseWithoutPrisoner))] = &playerBulletHouse;//
        phm[Key(typeid(HouseWithoutPrisoner), typeid(Grende))] = &HousePlayerBullet;

        phm[Key(typeid(Player), typeid(Prisioner))] = &playerPrisoner;//life Prisioner -1
        phm[Key(typeid(Prisioner), typeid(Player))] = &PrisionerPlayer;

        phm[Key(typeid(Player), typeid(SimpleSolider))] = &playerSeeking;//
        phm[Key(typeid(SimpleSolider), typeid(Player))] = &SeekingPlayer;

        phm[Key(typeid(Player), typeid(Passers))] = &playerSeeking;//life Passers -1
        phm[Key(typeid(Passers), typeid(Player))] = &SeekingPlayer;

        phm[Key(typeid(Scenery), typeid(Passers))] = &Object2Object1;//
        phm[Key(typeid(Passers), typeid(Scenery))] = &Object1Object2;

        phm[Key(typeid(Gate), typeid(Passers))] = &Object2Object1;//
        phm[Key(typeid(Passers), typeid(Gate))] = &Object1Object2;

        phm[Key(typeid(Grende), typeid(Gate))] = &grendeGate;/////////////////
        phm[Key(typeid(Gate), typeid(Grende))] = &gateGrende;

        phm[Key(typeid(PlayerBullet), typeid(Gate))] = &bulletWithStatic;///////////////////
        phm[Key(typeid(Gate), typeid(PlayerBullet))] = &staticWithBullet;

        phm[Key(typeid(Grende), typeid(Scenery))] = &bulletWithStatic;/////////////////
        phm[Key(typeid(Scenery), typeid(Grende))] = &bulletWithStatic;

        phm[Key(typeid(PlayerBullet), typeid(Scenery))] = &bulletWithStatic;/////////////////
        phm[Key(typeid(Scenery), typeid(PlayerBullet))] = &bulletWithStatic;

        phm[Key(typeid(HeavyArtilleryBullet), typeid(Scenery))] = &bulletWithStatic;/////////////////
        phm[Key(typeid(Scenery), typeid(HeavyArtilleryBullet))] = &bulletWithStatic;

        phm[Key(typeid(Rifle), typeid(Scenery))] = &bulletWithStatic;/////////////////
        phm[Key(typeid(Scenery), typeid(Rifle))] = &bulletWithStatic;

        phm[Key(typeid(PlayerBullet), typeid(Passers))] = &playerBulletActiveEnemy;
        phm[Key(typeid(Passers), typeid(PlayerBullet))] = &activeEnemyPlayerBullet;

        phm[Key(typeid(PlayerBullet), typeid(suicideBomber))] = &playerBulletActiveEnemy;
        phm[Key(typeid(suicideBomber), typeid(PlayerBullet))] = &activeEnemyPlayerBullet;

        phm[Key(typeid(PlayerBullet), typeid(SimpleSolider))] = &playerBulletActiveEnemy;
        phm[Key(typeid(SimpleSolider), typeid(PlayerBullet))] = &activeEnemyPlayerBullet;

        phm[Key(typeid(PlayerBullet), typeid(Guard))] = &playerBulletActiveEnemy;
        phm[Key(typeid(Guard), typeid(PlayerBullet))] = &activeEnemyPlayerBullet;

        phm[Key(typeid(Player), typeid(PresentGun))] = &playerPresentGun;
        phm[Key(typeid(PresentGun), typeid(Player))] = &presentGunPlayer;

        phm[Key(typeid(Player), typeid(Rifle))] = &playerRifle;///life player -12
        phm[Key(typeid(Rifle), typeid(Player))] = &riflePlayer;

        phm[Key(typeid(Player), typeid(PresentShild))] = &playerPresentShild;
        phm[Key(typeid(PresentShild), typeid(Player))] = &presentShildPlayer;

        phm[Key(typeid(Player), typeid(PresentLife))] = &playerPresentLife;
        phm[Key(typeid(PresentLife), typeid(Player))] = &presentLifePlayer;

        phm[Key(typeid(Player), typeid(PresentTime))] = &playerPresentTime;
        phm[Key(typeid(PresentTime), typeid(Player))] = &presentTimePlayer;

        phm[Key(typeid(Player), typeid(Spot))] = &playerSpot;
        phm[Key(typeid(Spot), typeid(Player))] = &spotPlayer;

        return phm;
    }
    //...

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace



void processCollision(Object& object1, Object& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
  
    if (phf) { phf(object1, object2); }
}
