Texture MissileTex
{
	filename="Resource\\Image\\Missile2.png"
}

Sprite MissileSpr
{
	texture=MissileTex
	rect=0,0,30,17
}

Animation MisFiring
{
	texture=MissileTex
	rect=0,17,37,19
	frames=3
	fps=30
	mode=LOOP
}

Texture MissileExplosion
{
	filename="Resource\\Image\\MissileExplosion.png"
}

Animation MisExp
{
	texture=MissileExplosion
	rect=0,0,256,315
	frames=10
	fps=30
	mode=LOOP
}

Sound MisExSound
{
	filename="Resource\\Sound\\bomb.wav"
}