#pragma once 
//#include "Renderer.h"
#include "Font.h"
#include <string>

// !! add necessary includes 
// !! forward declare the SDL_Texture struct 
struct SDL_Texture;

namespace neu
{
	// !! forward declare the Font, Renderer, Color and Vector2 classes 
	class Font;
	class Renderer;
	struct Color;
	struct Vector2;

	class Text
	{
	public:
		Text() = default;
		Text(Font* font) : //<!!initialize m_font with font parameter>
			m_font{ font } {};
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, const Vector2& position);

		friend class Renderer;
		
	
	private:
		Font* m_font = nullptr; //<!!initialize m_font to nullptr>
		SDL_Texture* m_texture = nullptr; //<!!initialize m_texture to nullptr>
	};
}