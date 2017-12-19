#include "stdafx.h"
#include "ViewComponent.h"


ViewComponent::ViewComponent(ViewInfo* viewInfo, Callback* clickCallback, Callback* doubleClickCallback) {
	this->viewInfo = viewInfo;
	this->clickCallBack = clickCallback;
	this->doubleClickCallback = doubleClickCallback;
	this->width = 0;
	this->height = 0;
	this->x = 0;
	this->y = 0;
}


ViewComponent::~ViewComponent() {
	this->components.clear();
	if (this->clickCallBack != NULL) {
		delete this->clickCallBack;
	}
	if (this->doubleClickCallback != NULL) {
		delete this->doubleClickCallback;
	}
}

void ViewComponent::draw(HDC hdc, SHORT width, SHORT height) {
	if (this->isVisible(width, height)){
		this->selfDraw(hdc);
		for (ViewComponent* component : this->components) {
			component->draw(hdc, width, height);
		}
	}
}

BOOL ViewComponent::containsDot(SHORT x, SHORT y) {
	return (x >= this->x) && (x <= this->x + this->width) && (y >= this->y) && (y <= this->y + this->height);
}

void ViewComponent::click(SHORT x, SHORT y) {
	for (ViewComponent* component : this->components) {
		if (component->containsDot(x, y)) {
			component->click(x, y);
		}
	}
	if (this->clickCallBack != NULL) {
		this->clickCallBack->call();
	}
}

void ViewComponent::doubleClick(SHORT x, SHORT y) {
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

void ViewComponent::move(SHORT x, SHORT y) {
	SHORT deltaX = x - this->x;
	SHORT deltaY = y - this->y;
	this->x = x;
	this->y = y;
	for (ViewComponent* viewComponent : this->components) {
		viewComponent->move(viewComponent->getX() + deltaX, viewComponent->getY() + deltaY);
	}
}

void ViewComponent::resize(SHORT width, SHORT height) {
	this->width = width;
	this->height = height;
}

void ViewComponent::updateSize() {}

vector<ViewComponent*>* ViewComponent::getComponents() {
	return &(this->components);
}

SHORT ViewComponent::getX() {
	return this->x;
}

SHORT ViewComponent::getY() {
	return this->y;
}

SHORT ViewComponent::getWidth() {
	return this->width;
}

SHORT ViewComponent::getHeight() {
	return this->height;
}

ViewInfo * ViewComponent::getViewInfo() {
	return this->viewInfo;
}

void ViewComponent::selfDraw(HDC hdc) {}

BOOL ViewComponent::isVisible(SHORT width, SHORT height) {
	if (this->getX() > width || this->getX() + this->getWidth() < 0) {
		return FALSE;
	}
	if (this->getY() > height || this->getY() + this->getHeight() < 0) {
		return FALSE;
	}
	return TRUE;
}

