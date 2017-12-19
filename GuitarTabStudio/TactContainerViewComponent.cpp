#include "stdafx.h"
#include "TactContainerViewComponent.h"


TactContainerViewComponent::TactContainerViewComponent(ViewInfo* viewInfo, SHORT height) : ViewComponent(viewInfo, NULL, NULL) {
	this->resize(viewInfo->viewConfiguration->getPageWidth(viewInfo->scale), height);
}

void TactContainerViewComponent::addTacts(vector<ViewComponent*>* tacts) {
	this->components.clear();
	SHORT horizontalBorder = this->viewInfo->viewConfiguration->getHorizontalBorder(this->viewInfo->scale);
	SHORT verticalBorder = this->viewInfo->viewConfiguration->getVerticalBorder(this->viewInfo->scale);
	SHORT tactHeight = this->viewInfo->viewConfiguration->getTactHeight(this->viewInfo->scale);
	SHORT containerWidth = this->getWidth() - 2* horizontalBorder;
	SHORT containerHeight = this->getHeight() - verticalBorder;
	SHORT y = this->getY() + verticalBorder;
	while (y + tactHeight < containerHeight && tacts->size() != 0) {
		SHORT lineWidth = 0;
		vector<ViewComponent*> addedComponents;
		vector<ViewComponent*>::iterator iterator = tacts->begin();
		while (iterator != tacts->end() && lineWidth + (*iterator)->getWidth() < containerWidth) {
			(*iterator)->move(this->getX() + horizontalBorder + lineWidth, y);
			lineWidth += (*iterator)->getWidth();
			this->components.push_back(*iterator);
			addedComponents.push_back(*iterator);
			iterator++;
		}
		if (iterator != tacts->end()) {
			SHORT delta = (containerWidth - lineWidth) / addedComponents.size();
			UCHAR i = 0;
			for (ViewComponent* tactViewComponent : addedComponents) {
				tactViewComponent->move(tactViewComponent->getX() + i * delta, tactViewComponent->getY());
				tactViewComponent->resize(tactViewComponent->getWidth() + delta, tactViewComponent->getHeight());
				i++;
			}
		}
		addedComponents.erase(addedComponents.begin(), addedComponents.end());
		tacts->erase(tacts->begin(), iterator);
		y += tactHeight;
	}
}


TactContainerViewComponent::~TactContainerViewComponent() {}
 