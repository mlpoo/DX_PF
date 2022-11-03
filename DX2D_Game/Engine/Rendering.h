#pragma once
#include "vector.h"

namespace Rendering
{
	class Camera final
	{
	public:
		void Set() const;

	public:
		vector<2> Length   = { 1280, 720 };
		float     Angle    = { 0 };
		vector<2> Location = { 0 , 0 };
	};

	namespace Image
	{
		class Component final
		{
		public :
			void Draw();

		public :
			char const * Content = nullptr;

		public:
			vector<2> Length   = { 0 , 0 };
			float     Angle    = { 0 };
			vector<2> Location = { 0 , 0 };
		};
	}

	namespace Animation
	{
		class Component final
		{
		public:
			void Draw();

		public:
			char const * Content = nullptr;

			float Playback   = 0;
			float Duration   = 0;
			bool  Repeatable = false;

		public:
			vector<2> Length   = { 0 , 0 };
			float     Angle    = { 0 };
			vector<2> Location = { 0 , 0 };
		};
	}
};

