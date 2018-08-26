/*********************************************************\
 * Copyright (c) 2012-2018 The Unrimp Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "RendererRuntime/Public/Resource/CompositorNode/Pass/DebugGui/CompositorInstancePassDebugGui.h"
#include "RendererRuntime/Public/Resource/CompositorNode/Pass/DebugGui/CompositorResourcePassDebugGui.h"
#include "RendererRuntime/Public/Resource/CompositorNode/CompositorNodeInstance.h"
#include "RendererRuntime/Public/Resource/CompositorWorkspace/CompositorContextData.h"
#include "RendererRuntime/Public/Resource/CompositorWorkspace/CompositorWorkspaceInstance.h"
#include "RendererRuntime/Public/DebugGui/DebugGuiManager.h"
#include "RendererRuntime/Public/Core/IProfiler.h"
#include "RendererRuntime/Public/IRendererRuntime.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace RendererRuntime
{


	//[-------------------------------------------------------]
	//[ Protected virtual RendererRuntime::ICompositorInstancePass methods ]
	//[-------------------------------------------------------]
	void CompositorInstancePassDebugGui::onFillCommandBuffer(MAYBE_UNUSED const Renderer::IRenderTarget& renderTarget, MAYBE_UNUSED const CompositorContextData& compositorContextData, MAYBE_UNUSED Renderer::CommandBuffer& commandBuffer)
	{
		#ifdef RENDERER_RUNTIME_IMGUI
			// Combined scoped profiler CPU and GPU sample as well as renderer debug event command
			const IRendererRuntime& rendererRuntime = getCompositorNodeInstance().getCompositorWorkspaceInstance().getRendererRuntime();
			RENDERER_SCOPED_PROFILER_EVENT(rendererRuntime.getContext(), commandBuffer, "Debug GUI compositor pass")

			// Fill command buffer
			DebugGuiManager& debugGuiManager = rendererRuntime.getDebugGuiManager();
			RenderableManager::Renderables& renderables = mRenderableManager.getRenderables();
			if (renderables.empty())
			{
				// Fill command buffer using fixed build in renderer configuration resources
				compositorContextData.resetCurrentlyBoundMaterialBlueprintResource();
				debugGuiManager.fillGraphicsCommandBufferUsingFixedBuildInRendererConfiguration(commandBuffer);
			}
			else
			{
				// Fill command buffer, this sets the material resource blueprint
				{
					Renderer::IVertexArrayPtr vertexArrayPtr = debugGuiManager.getFillVertexArrayPtr();
					if (vertexArrayPtr != renderables[0].getVertexArrayPtr())
					{
						renderables[0].setVertexArrayPtr(vertexArrayPtr);
					}
				}
				mRenderQueue.addRenderablesFromRenderableManager(mRenderableManager);
				if (mRenderQueue.getNumberOfDrawCalls() > 0)
				{
					mRenderQueue.fillGraphicsCommandBuffer(renderTarget, static_cast<const CompositorResourcePassDebugGui&>(getCompositorResourcePass()).getMaterialTechniqueId(), compositorContextData, commandBuffer);
				}

				// Fill command buffer using custom graphics material blueprint resource
				debugGuiManager.fillGraphicsCommandBuffer(commandBuffer);
			}
		#else
			assert(false && "ImGui support is disabled");
		#endif
	}


	//[-------------------------------------------------------]
	//[ Protected virtual RendererRuntime::CompositorInstancePassCompute methods ]
	//[-------------------------------------------------------]
	void CompositorInstancePassDebugGui::createMaterialResource(MaterialResourceId parentMaterialResourceId)
	{
		// Call the base implementation
		CompositorInstancePassCompute::createMaterialResource(parentMaterialResourceId);

		// Inside this compositor pass implementation, the renderable only exists to set the material blueprint
		mRenderableManager.getRenderables()[0].setNumberOfIndices(0);
	}


	//[-------------------------------------------------------]
	//[ Private methods                                       ]
	//[-------------------------------------------------------]
	CompositorInstancePassDebugGui::CompositorInstancePassDebugGui(const CompositorResourcePassDebugGui& compositorResourcePassDebugGui, const CompositorNodeInstance& compositorNodeInstance) :
		CompositorInstancePassCompute(compositorResourcePassDebugGui, compositorNodeInstance)
	{
		// Inside this compositor pass implementation, the renderable only exists to set the material blueprint
		RenderableManager::Renderables& renderables = mRenderableManager.getRenderables();
		if (!renderables.empty())
		{
			renderables[0].setNumberOfIndices(0);
		}
	}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // RendererRuntime