#include "TextRenderer.h"
#include "TransformComponent.h"
#include "Entity.h"

TextRenderer::TextRenderer(sf::Vector2f _position, sf::Font& _font, sf::String _text, int _characterSize, sf::Color _color) : text(_font) {
	text.setPosition(_position);
	text.setString(_text);
	text.setCharacterSize(_characterSize);
	text.setFillColor(_color);
	text.setOrigin(text.getLocalBounds().getCenter());
}

sf::Text& TextRenderer::getText() {
	return text;
}

void TextRenderer::setText(sf::String _text) {
	text.setString(_text);
}

void TextRenderer::update(float _deltaTime) {

}

void TextRenderer::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
	_target.draw(text, _states);
}