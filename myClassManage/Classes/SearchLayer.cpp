#include "pch.h"
#include "SearchLayer.h"
#include "util.h"
#include "DBManager.h"
#include <iostream>
#include <sstream>

USING_NS_CC;


bool SearchLayer::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;


	return true;
}
