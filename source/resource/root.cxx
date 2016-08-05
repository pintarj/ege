#include <ege/resource/root.hxx>


using namespace ege::resource;


Root::Root( const std::string& path )
{
        const char* separator =

        #ifdef _WIN32
                "\\";
        #else
                "/";
        #endif

        this->path = path;

        if ( path[ path.length() - 1 ] != separator[ 0 ] )
                this->path.append( separator );
}


Root::~Root()
{

}


const std::string& Root::getPath()
{
        return path;
}
