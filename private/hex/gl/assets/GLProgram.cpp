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
// GLProgram
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace gl
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTORS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        GLProgram::GLProgram(
                const hexString name,
                const unsigned char shaderType,
                const hexString* const sourceFile,
                const hexString* const sourceCode
        )
            :
            Shader(
                name,
                shaderType,
                sourceFile,
                sourceCode
            ),
            mShaders()
        {
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        GLProgram::~GLProgram() noexcept
        {
            handleUnload();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // Shader: PUBLIC GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void GLProgram::setShader(hexShared<Shader>& pShader)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(pShader.get() && "GLProgram::setShader: shader is null");
#endif // DEBUG

            mShaders[pShader->getShaderType()] = hexShared<hexGLShader>(
                static_cast<hexGLShader*>(pShader.get())
            );
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GLProgram: METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void GLProgram::handleUnload()
        {
            const auto end_iter(mShaders.cend());
            auto       iter(mShaders.begin());
            while (iter != end_iter)
            {
                iter->second->Unload();

                glDeleteShader(iter->second->getGLShaderID());
            }

            glDeleteProgram(mProgramID);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // Asset: PROTECTED METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool GLProgram::onLoad()
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mShaders.size() && "GLProgram::onLoad: no shaders attached");
#endif // DEBUG

            const auto end_iter(mShaders.cend());
            auto       iter(mShaders.begin());
            while (iter != end_iter)
            {
                if (!iter->second->Load())
                {
#ifdef HEX_LOGGING // LOG
                    hexString logMsg("GLProgram::onLoad: failed to load Shader #");
                    logMsg += iter->second->mName;
                    hexLog::Error(logMsg.c_str());
#endif // LOG

                    return false;
                }

                iter++;
            }

            mProgramID = glCreateProgram();

            iter = mShaders.begin();
            while (iter != end_iter)
            {
                glAttachShader(mProgramID, iter->second->getGLShaderID());
            }

            return false;
        }

        void GLProgram::onUnload()
        {
            handleUnload();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
