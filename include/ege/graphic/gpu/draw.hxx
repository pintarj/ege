

#ifndef EGE_GRAPHIC_GPU_DRAW_HXX
#define EGE_GRAPHIC_GPU_DRAW_HXX


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace draw
                        {
                                enum class Mode
                                {
                                                POINTS = 0x0,
                                                LINES = 0x1,
                                                LINE_LOOP = 0x2,
                                                LINE_STRIP = 0x3,
                                                TRIANGLES = 0x4,
                                                TRIANGLE_STRIP = 0x5,
                                                TRIANGLE_FAN = 0x6
                                };

                                void arrays( Mode mode, unsigned int offset, unsigned int count );
                        }
                }
        }
}


#endif
