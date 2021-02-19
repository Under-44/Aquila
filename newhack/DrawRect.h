#include "includes.h"

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR colour)
{
	D3DRECT rect = { x,y,x + w,y + h };
	//pDevice->Clear(1, &rect, D3DCLEAR_TARGET, colour, 0, 0);
}
