/*********************************************************\
 * Copyright (c) 2012-2019 The Unrimp Team
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
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


#ifdef RENDERER_RUNTIME_GRAPHICS_DEBUGGER


	//[-------------------------------------------------------]
	//[ Includes                                              ]
	//[-------------------------------------------------------]
	#include <Renderer/Public/Renderer.h>


	//[-------------------------------------------------------]
	//[ Namespace                                             ]
	//[-------------------------------------------------------]
	namespace RendererRuntime
	{


		//[-------------------------------------------------------]
		//[ Classes                                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Abstract graphics debugger interface
		*/
		class IGraphicsDebugger
		{


		//[-------------------------------------------------------]
		//[ Public methods                                        ]
		//[-------------------------------------------------------]
		public:
			[[nodiscard]] inline bool getCaptureNextFrame() const
			{
				return mCaptureNextFrame;
			}

			inline void captureNextFrame()
			{
				mCaptureNextFrame = true;
			}


		//[-------------------------------------------------------]
		//[ Public virtual RendererRuntime::IGraphicsDebugger methods ]
		//[-------------------------------------------------------]
		public:
			/**
			*  @brief
			*    Return whether or not the graphics debugger instance is properly initialized
			*
			*  @return
			*    "true" if the graphics debugger instance is properly initialized, else "false"
			*/
			[[nodiscard]] virtual bool isInitialized() const = 0;

			/**
			*  @brief
			*    Start frame capture
			*
			*  @param[in] nativeWindowHandle
			*    Native window handle
			*/
			virtual void startFrameCapture(Renderer::handle nativeWindowHandle) = 0;

			/**
			*  @brief
			*    End frame capture
			*
			*  @param[in] nativeWindowHandle
			*    Native window handle
			*/
			virtual void endFrameCapture(Renderer::handle nativeWindowHandle) = 0;


		//[-------------------------------------------------------]
		//[ Protected methods                                     ]
		//[-------------------------------------------------------]
		protected:
			inline IGraphicsDebugger() :
				mCaptureNextFrame(false)
			{
				// Nothing here
			}

			inline virtual ~IGraphicsDebugger()
			{
				// Nothing here
			}

			explicit IGraphicsDebugger(const IGraphicsDebugger&) = delete;
			IGraphicsDebugger& operator=(const IGraphicsDebugger&) = delete;

			inline void resetCaptureNextFrame()
			{
				mCaptureNextFrame = false;
			}


		//[-------------------------------------------------------]
		//[ Private data                                          ]
		//[-------------------------------------------------------]
		private:
			bool mCaptureNextFrame;


		};


	//[-------------------------------------------------------]
	//[ Namespace                                             ]
	//[-------------------------------------------------------]
	} // RendererRuntime


#endif