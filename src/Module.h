#pragma once

class Engine;

struct Module {
	virtual ~Module() = default;

	//Called once after SDL is up but before run()
	virtual bool init(Engine* engine) = 0;
	// Called each frame before render()
	virtual void update(Engine& engine, float dt) = 0;
	// Called each frame after update()
	virtual void render(Engine& engine) = 0;
	// Called on Shutdown
	virtual void shutdown(Engine& engine) = 0;
};