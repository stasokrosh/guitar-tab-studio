#include "stdafx.h"
#include "ViewComponent.h"


ViewComponent::ViewComponent(USHORT x, USHORT y, USHORT width, USHORT height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


ViewComponent::~ViewComponent() {}

void ViewComponent::draw(HDC hdc, USHORT width, USHORT height) {
	if (width > x && height > y) {
		this->selfDraw(hdc, width, height);
	}
	for (ViewComponent* component : this->components) {
		component->draw(hdc, width, height);
	}
}

BOOL ViewComponent::containsDot(USHORT x, USHORT y) {
	return (x >= this->x) && (x <= this->x + this->width) && (y >= this->y) && (y <= this->y + this->width);
}

void ViewComponent::click(USHORT x, USHORT y) {
	for (ViewComponent* component : this->components) {
		if (component->containsDot(x, y)) {
			component->click(x, y);
			return;
		}
	}
	this->selfClick();
}

void ViewComponent::doubleClick(USHORT x, USHORT y) {
	for (ViewComponent* component : this->components) {
		if (component->containsDot(x, y)) {
			component->doubleClick(x, y);
			return;
		}
	}
	this->selfDoubleClick();
}

void ViewComponent::move(USHORT x, USHORT y) {
	this->x = x;
	this->y = y;
}

void ViewComponent::resize(USHORT width, USHORT height) {
	this->width = width;
	this->height = height;
}

