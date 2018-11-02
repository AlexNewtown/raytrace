#ifndef OBJECT_TEXTURE_HPP
#define OBJECT_TEXTURE_HPP

#include "Object/Color.hpp"
#include "Math/Point2D.hpp"
#include "Math/Vector2D.hpp"
#include "Math/Bivector2D.hpp"

#include <vector>
#include <memory>

namespace Object {
	class TextureBase
	{
	public:
		TextureBase(int width, int height, int numChannels, std::vector<float> &&values);

	protected:
		struct MipLevel {
			int width;
			int height;
			std::vector<float> values;
		};

		void doSample(const Math::Point2D &samplePoint, const Math::Bivector2D &sampleProjection, int numValues, float values[]) const;
		void doGradient(const Math::Point2D &samplePoint, int numValues, Math::Vector2D gradient[]) const;

		std::unique_ptr<MipLevel> createBaseLevel(int width, int height, int numChannels, std::vector<float> &&values);
		void generateMipMaps(int numChannels);

		std::vector<std::unique_ptr<MipLevel>> mMipMaps;
	};

	template <int NUM_CHANNELS>
	class Texture : public TextureBase
	{
	public:
		Texture(int width, int height, std::vector<float> &&values)
			: TextureBase(width, height, NUM_CHANNELS, std::move(values))
		{
		}

		struct Value {
			float channels[NUM_CHANNELS];
		};

		Value sample(const Math::Point2D &samplePoint, const Math::Bivector2D &sampleProjection) const
		{
			Value value;
			doSample(samplePoint, sampleProjection, NUM_CHANNELS, value.channels);

			return value;
		}

		void gradient(const Math::Point2D &samplePoint, Math::Vector2D gradient[NUM_CHANNELS]) const
		{
			doGradient(samplePoint, NUM_CHANNELS, gradient);
		}
	};
}
#endif