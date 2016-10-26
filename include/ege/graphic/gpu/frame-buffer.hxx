

#ifndef EGE_GRAPHIC_GPU_FRAME_BUFFER_HXX
#define EGE_GRAPHIC_GPU_FRAME_BUFFER_HXX


#include <ege/graphic/gpu/context.hxx>
#include <ege/graphic/gpu/object.hxx>
#include <ege/graphic/gpu/texture/texture-rectangle.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace frameBuffer
                        {
                                void setClearColor( float r, float g, float b, float a );
                                void clearColorBuffer();
                                void clearColorBuffer( float r, float g, float b, float a );
                        }

                        class Context;

                        class FrameBuffer: public Object
                        {
                                friend Context;

                                private:
                                        unsigned int width;
                                        unsigned int height;
                                        const Texture* colorBuffer;

                                        FrameBuffer( unsigned int id );

                                public:
                                        FrameBuffer();
                                        virtual ~FrameBuffer();
                                        bool isDefault() const;
                                        void attachColorBuffer( const texture::TextureRectangle& texture );
                                        void detachColorBuffer();
                                        void bindAsDrawTarget() const;
                        };
                }
        }
}


#endif
