#include <iostream>

#include <SFML/Graphics.hpp>
#include <Canvas.hpp>

//#define main WinMain

struct sfCanvasManager: sf::Drawable
{
	sfCanvasManager(float x, float y, int w, int h)
	: m_canvas(w, h)
	{
		m_texture.create(w, h);
		m_texture.update(m_canvas.get_texture());
		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin(w/2, h/2);
		this->set_pos({x, y});
	}

	void set_pixel(int x, int y, const sf::Color &c)
	{
		sf::Vector2f s = m_sprite.getScale();
		x -= m_sprite.getPosition().x - m_sprite.getOrigin().x * m_sprite.getScale().x;
		y -= m_sprite.getPosition().y - m_sprite.getOrigin().y * m_sprite.getScale().y;

		m_canvas.set_pixel(x/s.x, y/s.y, {c.r, c.g, c.b, c.a});
		m_texture.update(m_canvas.get_texture());
	}

	void scale(float s)
	{
		m_sprite.scale(s, s);
	}

	void set_pos(const sf::Vector2f &pos)
	{
		m_sprite.setPosition(pos);
	}

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		target.draw(m_sprite, states);
	}
private:
	Canvas       m_canvas;
	sf::Sprite   m_sprite;
	sf::Texture  m_texture;
};

int main()
{
	sf::RenderWindow window({500, 500}, "uwu");
	sf::Vector2u ws = window.getSize();
	sfCanvasManager canvas(ws.x/2, ws.y/2, 15, 15);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				canvas.set_pos((sf::Vector2f)window.getSize() / 2.f);
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				float zoom_amount = 1.1f;
				if (event.mouseWheel.delta > 0)
					canvas.scale(1/zoom_amount);
				if (event.mouseWheel.delta < 0)
					canvas.scale(zoom_amount);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i mp = sf::Mouse::getPosition(window);

			canvas.set_pixel(mp.x, mp.y, {0, 0, 0, 255});
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			sf::Vector2i mp = sf::Mouse::getPosition(window);

			canvas.set_pixel(mp.x, mp.y, {255, 255, 255, 255});
		}

		window.clear({100, 100, 100, 255});
		window.draw(canvas);
		window.display();
	}

	return 0;
}