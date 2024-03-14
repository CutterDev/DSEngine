#pragma once
#include <b2_world.h>

#include <memory>

#include "GameCamera.h"
#include "CommonHeaders.h"

class Scene
{
public:
    b2World* Physics;
    // Called when scene initially created. Called once.
    virtual void OnCreate(GameCamera* camera, Mouse* mouse) = 0;

    // Called when scene destroyed. Called at most once (if a scene 
    // is not removed from the game, this will never be called).
    virtual void OnDestroy() = 0;

    // Called whenever a scene is transitioned into. Can be 
    // called many times in a typical game cycle.
    virtual void OnActivate() = 0;

    // Called whenever a transition out of a scene occurs. 
    // Can be called many times in a typical game cycle.
    virtual void OnDeactivate() = 0;

    // The below functions can be overridden as necessary in our scenes.
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(float deltaTime) = 0;
};

