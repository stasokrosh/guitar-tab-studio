#include "stdafx.h"
#include "TactContainerViewComponent.h"


TactContainerViewComponent::TactContainerViewComponent(ViewInfo* viewInfo, USHORT height) : ViewComponent(viewInfo, NULL, NULL) {
	this->resize(viewInfo->viewConfiguration->getPageWidth(viewInfo->scale), height);
}

void TactContainerViewComponent::addTacts(vector<ViewComponent*>* tacts) {
	this->components.clear;
	USHORT horizontalBorder = this->viewInfo->viewConfiguration->getHorizontalBorder(this->viewInfo->scale);
	USHORT verticalBorder = this->viewInfo->viewConfiguration->getVerticalBorder(this->viewInfo->scale);
	USHORT tactHeight = this->viewInfo->viewConfiguration->getTactHeight(this->viewInfo->scale);
	USHORT containerWidth = this->getWidth - 2* horizontalBorder;
	USHORT containerHeight = this->getHeight - verticalBorder;
	USHORT y = verticalBorder;
	while (y + tactHeight < containerHeight && tacts->size() != 0) {
		UCHAR lineWidth = 0;
		vector<ViewComponent*> addedComponents;
		vector<ViewComponent*>::iterator iterator = tacts->begin();
		while (lineWidth + (*iterator)->getWidth() < containerWidth && iterator != tacts->end()) {
			(*iterator)->move(lineWidth, y);
			lineWidth += (*iterator)->getWidth();
			this->components.push_back(*iterator);
			addedComponents.push_back(*iterator);
			iterator++;
		}
		if (iterator != tacts->end()) {
			USHORT delta = containerWidth / addedComponents.size();
			UCHAR i = 0;
			for (ViewComponent* tactViewComponent : addedComponents) {
				tactViewComponent->move(tactViewComponent->getX() + i * delta, tactViewComponent->getY());
				tactViewComponent->resize(tactViewComponent->getWidth() + delta, tactViewComponent->getHeight());
				i++;
			}
		}
		iterator--;
		addedComponents.clear();
		tacts->erase(tacts->begin(), iterator);
		y += tactHeight;
	}
}


TactContainerViewComponent::~TactContainerViewComponent() {}
 