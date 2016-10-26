

#ifndef EGE_GRAPHIC_GPU_FRAME_BUFFER_HXX
#define EGE_GRAPHIC_GPU_FRAME_BUFFER_HXX


#include <ege/graphic/gpu/context.hxx>
#include <ege/graphic/gpu/object.hxx>
#include <ege/graphic/gpu/texture/texture-rectangle.hxx>
#include <ege/graphic/gpu/sampler.hxx>


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
                                        unsigned int getWidth() const;
                                        unsigned int getHeight() const;
                                        void bindAsDrawTarget() const;

                                        static void blit( const FrameBuffer& destination, const FrameBuffer& source,
                                                unsigned int dstX0, unsigned int dstY0, unsigned int dstX1, unsigned int dstY1,
                                                unsigned int srcX0, unsigned int srcY0, unsigned int srcX1, unsigned int srcY1,
                                                sampler::Filter filter );
                        };
                }
        }
}


#endif
