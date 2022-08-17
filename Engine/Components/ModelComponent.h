#pragma once
#include "RenderComponent.h"

namespace neu
{
	class Model;

	class ModelComponent : public RenderComponent
	{
	public:
		ModelComponent() = default;

		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

	public:
		std::shared_ptr<Model> m_model;
	};
}