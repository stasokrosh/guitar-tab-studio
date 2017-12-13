#include "stdafx.h"
#include "ViewComponent.h"


ViewComponent::ViewComponent(ViewInfo* viewInfo, Callback* clickCallback, Callback* doubleClickCallback) {
	this->viewInfo = viewInfo;
	this->clickCallBack = clickCallBack;
	this->doubleClickCallback = doubleClickCallback;
	this->width = 0;
	this->height = 0;
	this->x = 0;
	this->y = 0;
}


ViewComponent::~ViewComponent() {
	for (ViewComponent* viewComponent : this->components) {
		delete viewComponent;
	}
	if (this->clickCallBack != NULL) {
		delete this->clickCallBack;
	}
	if (this->doubleClickCallback != NULL) {
		delete this->doubleClickCallback;
	}
}

void ViewComponent::draw(HDC hdc) {
	this->selfDraw(hdc);
	for (ViewComponent* component : this->components) {
		component->draw(hdc);
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
	if (this->clickCallBack != NULL) {
		this->clickCallBack->call();
	}
}

void ViewComponent::doubleClick(USHORT x, USHORT y) {
	for (ViewComponent* component : this->components) {
		if (component->containsDot(x, y)) {
			component->doubleClick(x, y);
			return;
		}
	}
	if (this->doubleClickCallback != NULL) {
		this->doubleClickCallback->call();
	}
}

void ViewComponent::move(USHORT x, USHORT y) {
	USHORT deltaX = x - this->x;
	USHORT deltaY = y - this->y;
	this->x = x;
	this->y = y;
	for (ViewComponent* viewComponent : this->components) {
		viewComponent->move(viewComponent->getX() + deltaX, viewComponent->getY() + deltaY);
	}
}

void ViewComponent::resize(USHORT width, USHORT height) {
	this->width = width;
	this->height = height;
}

void ViewComponent::updateSize() {}

vector<ViewComponent*>* ViewComponent::getComponents() {
	return &(this->components);
}

USHORT ViewComponent::getX() {
	return this->x;
}

USHORT ViewComponent::getY() {
	return this->y;
}

USHORT ViewComponent::getWidth() {
	return this->width;
}

USHORT ViewComponent::getHeight() {
	return this->height;
}

ViewInfo * ViewComponent::getViewInfo() {
	return this->viewInfo;
}

void ViewComponent::selfDraw(HDC hdc) {}

