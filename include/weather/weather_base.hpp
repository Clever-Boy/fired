/***********************************************************************
     * File       : weather_base.hpp
     * Created    : Feb 12, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WEATHER_BASE
#define __WEATHER_BASE


namespace fired {
	struct Weather;
	struct WeatherParticle {
		sf::RectangleShape *sprite;
		sf::Vector2f        pos;
		sf::Vector2f        speed;
		sf::Vector2f        accel;
		float               scale;


		bool process(fired::World *world);
	};


	struct Weather {
		fired::World       *world;
		sf::RectangleShape *sprite;
		sf::FloatRect       weatherRect;
		sf::Vector2f        speed;
		sf::Vector2f        accel;
		float               life;
		float               wind;
		float               frequency;

		std::vector<fired::WeatherParticle*> particles;
		fired::Camera *cam;


		Weather(fired::World *_world, float _frequency, float _wind);
		virtual ~Weather();

		virtual void update();
		void render();
		void fill();
		void addParticle();
		sf::Vector2f genPos();
	};
}

#endif

