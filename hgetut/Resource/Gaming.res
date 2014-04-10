Include "Resource\\Script\\Player.res"
Include "Resource\\Script\\MissileRes.res"
Include "Resource\\Script\\Helicopter.res"
Include "Resource\\Script\\Score.res"
Include "Resource\\Script\\MiniMap.res"
Include "Resource\\Script\\Building.res"
Include "Resource\\Script\\BackGround.res"

Stream Stage1Music
{
	filename="Resource\\Sound\\Stage1.mp3"
}

Stream Stage2Music
{
	filename="Resource\\Sound\\Stage2.mp3"
}

Stream Dead
{
	filename="Resource\\Sound\\Dead.mp3"
}

Stream Heil
{
	filename="Resource\\Sound\\Heil.mp3"
}

Texture GameOverTex
{
	filename="Resource\\Image\\GameOver.png"
}

Sprite GameOverSpr
{
	texture=GameOverTex
	rect=0,0,1920,768
}