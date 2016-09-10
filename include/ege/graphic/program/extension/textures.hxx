

#ifndef EGE_GRAPHIC_PROGRAM_EXTENSION_TEXTURES_HXX
#define EGE_GRAPHIC_PROGRAM_EXTENSION_TEXTURES_HXX


#include <ege/graphic/program/extension.hxx>


namespace ege
{
        namespace graphic
        {
                namespace program
                {
                        namespace extension
                        {
                                class Textures: Extension
                                {
                                        private:
                                                size_t* texturesLocation;

                                        protected:
                                                Textures( gpu::Program& program, const char** textureNames, size_t count );
                                                virtual ~Textures();

                                        public:
                                                void uniformTextureAt( size_t index, size_t value );
                                };
                        }
                }
        }
}


#endif
