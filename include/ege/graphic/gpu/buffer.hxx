

#ifndef EGE_GRAPHIC_GPU_BUFFER_HXX
#define EGE_GRAPHIC_GPU_BUFFER_HXX


#include <ege/graphic/gpu/object.hxx>
#include <initializer_list>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        class Buffer;

                        namespace buffer
                        {
                                namespace map
                                {
                                        class Range;
                                }

                                namespace usage
                                {
                                        enum class Frequency
                                        {
                                                STREAM,
                                                STATIC,
                                                DYNAMIC
                                        };

                                        enum class Nature
                                        {
                                                DRAW,
                                                READ,
                                                COPY
                                        };
                                }
                        }

                        class Buffer: public Object
                        {
                                friend buffer::map::Range;

                                private:
                                        unsigned int size;
                                        buffer::usage::Frequency usageFrequency;
                                        buffer::usage::Nature usageNature;
                                        unsigned int usageCacheFlag;
                                        buffer::map::Range* mappedRange;

                                public:
                                        Buffer( unsigned int size, buffer::usage::Frequency frequency, buffer::usage::Nature nature, const void* data = nullptr );
                                        virtual ~Buffer();
                                        void reallocate( unsigned int size, buffer::usage::Frequency frequency, buffer::usage::Nature nature, const void* data = nullptr );
                                        void reallocate( unsigned int size, const void* data = nullptr );
                                        void invalidateData();
                                        unsigned int getSize() const;
                                        bool isMapped() const;
                                        buffer::map::Range& getMappedRange() const;
                        };

                        namespace buffer
                        {

                                namespace map
                                {
                                        enum class WriteAccess
                                        {
                                                FLUSH_EXPLICIT = 0x0010,
                                                UNSYNCHRONIZED = 0x0020,
                                                INVALIDATE_RANGE = 0x0004
                                        };

                                        enum class ReadAccess
                                        {
                                                UNSYNCHRONIZED = 0x0020
                                        };

                                        class Range
                                        {
                                                protected:
                                                        const unsigned int access;
                                                        Buffer& buffer;

                                                        Range( Buffer& buffer, unsigned int offset, unsigned int length, unsigned int access );
                                                public:
                                                        const unsigned int offset;
                                                        const unsigned int length;

                                                        virtual ~Range();
                                        };

                                        class WriteRange: public Range
                                        {
                                                private:
                                                        WriteRange( Buffer& buffer, unsigned int offset, unsigned int length, unsigned int access );

                                                public:
                                                        void* const mappedMemory;
                                                        const bool flushExplicit;

                                                        WriteRange( Buffer& buffer, unsigned int offset, unsigned int length, std::initializer_list< WriteAccess > writeAccess = {} ):
                                                                WriteRange( buffer, offset, length, [ writeAccess ] ()
                                                                {
                                                                        unsigned int accessFlag = 0;

                                                                        for ( auto bit : writeAccess )
                                                                                accessFlag |= ( unsigned int ) bit;

                                                                        return accessFlag;
                                                                } () ) {}

                                                        WriteRange( Buffer& buffer, std::initializer_list< WriteAccess > writeAccess = {} ):
                                                                WriteRange( buffer, 0, buffer.getSize(), writeAccess ) {}

                                                        virtual ~WriteRange() {};
                                                        void flush( unsigned int offset, unsigned int length ) const;
                                        };

                                        class ReadRange: public Range
                                        {
                                                private:
                                                        ReadRange( Buffer& buffer, unsigned int offset, unsigned int length, unsigned int access );

                                                public:
                                                        const void* const mappedMemory;

                                                        ReadRange( Buffer& buffer, unsigned int offset, unsigned int length, std::initializer_list< ReadAccess > readAccess = {} ):
                                                                ReadRange( buffer, offset, length, [ readAccess ] ()
                                                                {
                                                                        unsigned int accessFlag = 0;

                                                                        for ( auto bit : readAccess )
                                                                                accessFlag |= ( unsigned int ) bit;

                                                                        return accessFlag;
                                                                } () ) {}

                                                        ReadRange( Buffer& buffer, std::initializer_list< ReadAccess > readAccess = {} ):
                                                                ReadRange( buffer, 0, buffer.getSize(), readAccess ) {}

                                                        virtual ~ReadRange() {};
                                        };
                                }
                        }
                }
        }
}


#endif
