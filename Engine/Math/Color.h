#pragma once
#include <cstdint>
#include <iostream>
#include <string>

namespace neu
{
	//typedef unsigned char u8_t;
	//using u8_t = unsigned char;

	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		uint8_t operator [] (size_t index) const { return (&r)[index]; } //(index == 0) ? x : y; }
		uint8_t& operator [] (size_t index) { return (&r)[index]; } //(index == 0) ? x : y; }
		
		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;

		friend std::istream& operator >> (std::istream& stream, Color& color);
	};

	
	inline std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		getline(stream, line);
		//line = { r, g, b }

		std::string str;

		//red
		str = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		color.r = (uint8_t)(stof(str) * 255);
		//line = g, b }

		//setting line to another sub section of the string to read green and blue 
		line = line.substr(line.find(",") + 1);
		
		//green
		str = line.substr(0, line.find(","));
		color.g = (uint8_t)(stof(str) * 255);
		
		//blue
		str = line.substr(line.find(",") + 1, line.find("}") - line.find(",") + 1);
		color.b = (uint8_t)(stof(str) * 255);
		
		//default alpha
		color.a = 255;
		
		return stream;
	}

}