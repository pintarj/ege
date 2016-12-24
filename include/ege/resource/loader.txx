

template < typename R >
bool ege::resource::Loader< R >::isCompleted() const
{
        return getCompletion() == 1.0;
}


template < typename R >
std::future< void > ege::resource::Loader< R >::asyncComplete( std::function< void() > const& callback )
{
        return std::async( std::launch::async, [ this, callback ] () { this->complete( callback ); } );
}
