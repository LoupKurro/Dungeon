/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 19th 2017
File : mapInfo.h
Goal : Object serving as a gateway for the informations of the map
**********************************************************/
#pragma once
#include <string>
#include "position.h"

struct mapInfo
{
	position player;
	int dimX, dimY;
	string linkMap;
};