#pragma once

#include <gl/freeglut.h>
#include "Room.h"
#include "Player.h"
#include "Defines.h"
#include "Vector3D.h"
#include "Bin.h"
#include "AssimpSimpleModelLoader.h"

using namespace std;

static const std::string modelName = "Items.obj";

Room* room;
Player* player;
int windowWidth = 1024, windowHeight = 600;
double _level = EASY;
double cx=0;
Bin* bin;
int TIMER_MS = 10000;

AssimpSimpleModelLoader* loader;