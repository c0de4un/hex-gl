/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// HEADER
#ifndef HEX_GL_RENDERER_HPP
    #include <hex/gl/render/GLRenderer.hpp>
#endif /// !HEX_GL_RENDERER_HPP

// Include hex::core::IRendererListener
#ifndef HEX_CORE_I_RENDERER_LISTENER_HXX
    #include <hex/core/render/IRendererListener.hxx>
#endif /// !HEX_CORE_I_RENDERER_LISTENER_HXX

// Include hex::gl::GLShader
#ifndef HEX_GL_SHADER_HPP
    #include <hex/gl/assets/GLShader.hpp>
#endif /// !HEX_GL_SHADER_HPP

// Include hex::gl::GLProgram
#ifndef HEX_GL_PROGRAM_HPP
    #include <hex/gl/assets/GLProgram.hpp>
#endif /// !HEX_GL_PROGRAM_HPP

#ifdef HEX_LOGGING // LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif // LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// GLRenderer
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace gl
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        GLRenderer::GLRenderer()
            :
            RenderSystem(),
            mIsFirstFrame(true)
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("GLRenderer::constructor");
#endif // LOG
        }

        GLRenderer::~GLRenderer() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("GLRenderer::destructor");
#endif // LOG

            stopRenderer();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void GLRenderer::Initialize()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("GLRenderer::Initialize");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance.get() && "GLRenderer::Initialize: already initialized");
#endif // DEBUG

            hexLock lock(mInstanceMutex);

            if (!mInstance.get())
                mInstance.reset(static_cast<hexRenderer*>(new GLRenderer()));
        }

        void GLRenderer::Draw()
        {
            size_t listenerIndex(0);

            mIsFirstFrame = false;
            auto listener_ptr(getNextListener(listenerIndex));
            while (listener_ptr.get())
            {
                try
                {
                    if (mIsFirstFrame)
                        listener_ptr->onRenderReady();

                    listener_ptr->onRender();
                }
                catch (const std::exception& exc)
                {
                    listener_ptr->onRenderError(exc); // Copy exception
                }
                catch (...)
                {
                    std::exception err("GLRenderer::Draw: unknown error");
                    listener_ptr->onRenderError(std::move(err));
                }

                listenerIndex++;
                listener_ptr = getNextListener(listenerIndex).get();
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // IRenderer: PUBLIC METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexShared<hexShader> GLRenderer::createShader(
            const hexString name,
            const unsigned char shaderType,
            const hexString* const sourceFile,
            const hexString* const sourceCode
        ) {
            hexShader* shader(nullptr);

            if (shaderType == static_cast<unsigned char>(hexEShaderType::PROGRAM))
            {
                hexGLProgram* const glProgram_ptr( new hexGLProgram(
                    name,
                    shaderType,
                    sourceFile,
                    sourceCode
                ) );

                shader = static_cast<hexShader*>(glProgram_ptr);
            }
            else
            {
                hexGLShader* const glShader_ptr( new hexGLShader(
                    name,
                    shaderType,
                    sourceFile,
                    sourceCode
                ) );

                shader = static_cast<hexShader*>(glShader_ptr);
            }

            return hexShared<hexShader>(shader);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE.ISystem
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool GLRenderer::onStart()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("GLRenderer::onStart");
#endif // LOG

            return System::onStart();
        }

        bool GLRenderer::onResume()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("GLRenderer::onResume");
#endif // LOG

            return System::onResume();
        }

        void GLRenderer::onPause()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("GLRenderer::onPause");
#endif // LOG

            System::onPause();
        }

        void GLRenderer::onStop()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("GLRenderer::onStop");
#endif // LOG

            stopRenderer();
        }

        void GLRenderer::stopRenderer() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Debug("GLRenderer::stopRenderer");
#endif // LOG
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
