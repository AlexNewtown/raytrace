#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include "Object/Forwards.hpp"
#include "Trace/Forwards.hpp"

#include "Render/Thread.hpp"
#include "Render/PrerenderThread.hpp"

#include <set>

#include <windows.h>

namespace Render {

class Engine
{
public:
	class Listener {
	public:
		virtual void onRenderDone() = 0;
		virtual void onRenderStatus(const char *message) = 0;
		virtual void onPrerenderDone() = 0;
	};

	Engine(const Object::Scene &scene);
	~Engine();

	bool rendering() const;

	void startPrerender(unsigned char *bits, Listener *listener);
	void startRender(unsigned char *bits, Listener *listener);
	bool threadDone(Thread *thread);
	void prerenderThreadDone();
	void setSettings(const Trace::Tracer::Settings &settings);

	Trace::Tracer createTracer();
	Trace::Tracer::Settings &settings();

private:
	void getBlock(int block, int &x, int &y, int &w, int &h);
	int widthInBlocks();
	int heightInBlocks();

	const Object::Scene &mScene;
	Trace::Tracer::Settings mSettings;
	Trace::Tracer::RenderData mRenderData;
	unsigned char *mBits;
	Listener *mListener;
	bool mRendering;
	DWORD mStartTime;
	CRITICAL_SECTION mCritSec;
	std::set<std::unique_ptr<Thread>> mThreads;
	std::unique_ptr<PrerenderThread> mPrerenderThread;
	int mNumActiveThreads;
	int mBlocksStarted;
};

}

#endif