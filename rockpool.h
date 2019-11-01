


class RockPool: public Scene
{
public:

	RockPool(const char* name) : Scene(name) {}

	void Initialize()
	{
		/*
		float radius = 0.1f;

		// convex rocks
		float minSize = 0.1f;
		float maxSize = 0.5f;

		for (int i=0; i < 4; i++)
			for (int j=0; j < 2; j++)
			AddRandomConvex(10, Vec3(48*radius*0.5f + i*maxSize*2.0f, 0.0f, j*maxSize*2.0f), minSize, maxSize, Vec3(0.0f, 1.0f, 0.0f), Randf(0.0f, k2Pi));

		CreateParticleGrid(Vec3(0.0f, radius*0.5f, -1.0f), 32, 32, 32, radius*0.55f, Vec3(0.0f), 1.0f, false, 0.0f, NvFlexMakePhase(0, eNvFlexPhaseSelfCollide | eNvFlexPhaseFluid), 0.005f);
*/
		int dimx = 32;
		int dimy = 32;
		float radius = 0.07f;

		Vec3 lower, upper;
		//GetParticleBounds(lower, upper);
		lower = 1.0f;
		upper = 2.0f;

		Vec3 center = (lower + upper)*0.5f;
		center.y = 0.0f;

		float width = (upper - lower).x*0.5f;
		float edge = 0.125f;
		float height = 0.5f;

		AddBox(Vec3(0.01f, 0.7f, 0.1f), 1.2f);

		AddBox(Vec3(edge, height, width + edge * 2.0f), center + Vec3(-width - edge, height / 2.0f, 0.0f));
		AddBox(Vec3(edge, height, width + edge * 2.0f), center + Vec3(width + edge, height / 2.0f, 0.0f));

		AddBox(Vec3(width + 2.0f*edge, height, edge), center + Vec3(0.0f, height / 2.0f, -(width + edge)));
		AddBox(Vec3(width + 2.0f*edge, height, edge), center + Vec3(0.0f, height / 2.0f, width + edge));

		float fluidWidth = width;
		float fluidHeight = height * 1.25f;

		int particleWidth = int(2.0f*fluidWidth / radius);
		int particleHeight = int(fluidHeight / radius);

		CreateParticleGrid(center - Vec3(fluidWidth, 1.5f, fluidWidth), particleWidth, particleHeight, particleWidth, radius, Vec3(0.0f), 2.0f, false, 0.0f, NvFlexMakePhase(0, eNvFlexPhaseSelfCollide | eNvFlexPhaseFluid));
		count_white = particleHeight * particleWidth*particleWidth;
		color_white = Vec4(1.0f, 1.0f, 1.0f, 0.0f);
		CreateParticleGrid(center - Vec3(fluidWidth, 1.5f, fluidWidth), particleWidth, particleHeight, particleWidth, radius, Vec3(0.0f), 2.0f, false, 0.0f, NvFlexMakePhase(1, eNvFlexPhaseSelfCollide | eNvFlexPhaseFluid));
		count_grey = particleHeight * particleWidth*particleWidth;
		color_grey = Vec4(0.5f, 0.5f, 0.5f, 0.0f);

		g_solverDesc.featureMode = eNvFlexFeatureModeSimpleFluids;

		g_numSubsteps = 2;

		g_params.radius = radius;
		g_params.dynamicFriction = 0.00f;
		g_params.viscosity = 0.01f;
		g_params.numIterations = 2;
		g_params.vorticityConfinement = 75.0f;
		g_params.fluidRestDistance = radius*0.6f;
		g_params.relaxationFactor = 1.0f;
		g_params.smoothing = 0.5f;
		g_params.diffuseThreshold *= 0.25f;
		g_params.cohesion = 0.05f;

		g_maxDiffuseParticles = 64*1024;		
		g_diffuseScale = 0.5f;
		g_params.diffuseBallistic = 16;
		g_params.diffuseBuoyancy = 1.0f;
		g_params.diffuseDrag = 1.0f;

		g_emitters[0].mEnabled = false;

		g_params.numPlanes = 5;

		g_waveFloorTilt = 0.0f;
		g_waveFrequency = 1.5f;
		g_waveAmplitude = 2.0f;
		
		// draw options		
		g_drawPoints = false;
		g_drawEllipsoids = true;
		g_drawDiffuse = true;
		g_lightDistance = 1.8f;

		g_numExtraParticles = 80*1024;

		Emitter e1;
		e1.mDir = Vec3(-1.0f, 0.0f, 0.0f);
		e1.mRight = Vec3(0.0f, 0.0f, 1.0f);
		e1.mPos = Vec3(3.8f, 1.f, 1.f) ;
		e1.mSpeed = (g_params.fluidRestDistance/g_dt)*2.0f;	// 2 particle layers per-frame
		e1.mEnabled = true;

		Emitter e2;
		e2.mDir = Vec3(1.0f, 0.0f, 0.0f);
		e2.mRight = Vec3(0.0f, 0.0f, -1.0f);
		e2.mPos = Vec3(2.f, 1.f, -0.f);
		e2.mSpeed = (g_params.fluidRestDistance/g_dt)*2.0f; // 2 particle layers per-frame
		e2.mEnabled = true;

		g_emitters.push_back(e1);
		g_emitters.push_back(e2);
	}
};
