#pragma once

#include <d3d11.h>

namespace Pipeline
{
	namespace String
	{
		void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const size, POINT const center);
	}

	namespace Texture
	{
		void Create(struct Handle *& handle, SIZE const size, BYTE const * const data);
		void Render(struct Handle const * const & handle, RECT const area);
		void Delete(struct Handle const * const & handle);
	}

	namespace Transform
	{
		enum class Type
		{
			Formar,
			Latter
		};

		using matrix = float[4][4];

		template<Type type>
		void Update(matrix const & matrix);
	}
};

