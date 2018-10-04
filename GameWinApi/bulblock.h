#pragma once
#include "block.h"
#include "bullet.h"

class bulblock : public block
{
	bullet *mybul;
public:
	bulblock(void);
	void clear(void);
	void create(class bullet *temppoint);
	void destroy();
};
