Texture PlayerTex
{
	filename="Resource\\Image\\player.png"
}

Animation Stand
{
	texture=PlayerTex
	rect=0,0,64,64
	frames=2
	fps=2.0
	hotspot=32,32
	mode=FORWARD,LOOP
}

Animation Run
{
	texture=PlayerTex
	rect=0,64,64,64
	frames=5
	fps=30.0
	hotspot=32,32
	mode=FORWARD,LOOP
}

Animation JumpUp
{
	texture=PlayerTex
	rect=0,128,64,64
	frames=4
	fps=30.0
	hotspot=32,32
	mode=FORWARD,LOOP
}

Animation Jumping
{
	texture=PlayerTex
	rect=0,192,64,64
	frames=1
	fps=30.0
	hotspot=32,32
	mode=FORWARD,LOOP
}

Animation JumpDown
{
	texture=PlayerTex
	rect=0,256,64,64
	frames=3
	fps=30.0
	hotspot=32,32
	mode=FORWARD,LOOP
}

Animation Dead
{
	texture=PlayerTex
	rect=0,320,64,64
	frames=7
	fps=30.0
	hotspot=32,32
	mode=FORWARD,LOOP
}

Texture ParticleTex
{
	filename="Resource\\Image\\pi.png"
}

Sprite ParticleSpr{
	Texture=ParticleTex
	recr=0,0,32,32
	hotspot=16,16
}

Particle piParticle
{
	filename="Resource\\particle1.psi
	sprite=ParticleSpr
}