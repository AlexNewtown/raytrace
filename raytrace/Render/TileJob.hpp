#ifndef RENDER_TILE_JOB_HPP
#define RENDER_TILE_JOB_HPP

#include "Render/Job.hpp"
#include "Render/Framebuffer.hpp"

namespace Render {
	class TileJob : public Job
	{
	public:
		TileJob(Framebuffer &framebuffer, std::function<void(int, int, Framebuffer&, Sampler&)> &&pixelFunc);

		std::unique_ptr<Job::Task> getNextTask();

	private:
		Framebuffer &mFramebuffer;
		int mNextTile;
		std::function<void(int, int, Framebuffer &, Sampler&)> mPixelFunc;
	};
}
#endif