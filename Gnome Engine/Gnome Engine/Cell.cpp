#include "StdAfx.h"
#include "Cell.h"


Cell::Cell(void)
{
}


Cell::~Cell(void)
{
}

ColorChar Cell::getColorChar(void)
{
	ColorChar retVal = ColorChar();
	retVal.color += ground;
	return retVal;
}