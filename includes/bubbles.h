#ifndef _BUBBLES_H_
#define _BUBBLES_H_

typedef struct Bubble
{
	int xPos;
	int yPos;
	int radius;
} Bubble;

void generateBubbles(Bubble *bubbles);
void drawBubble(int centerX, int centerY, int radius);

#endif /* _BUBBLES_H_ */