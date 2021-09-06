#include <vector>

namespace
{
    template< typename T >
    struct Object
    { 
        T m_obj;
        bool m_use = false;
    };
}

template< typename T >
using ObjectsContainer = std::vector< Object< T > >;

template< typename T >
class ObjectPool
{
public:
    ObjectPool( size_t size = 1 );
    ~ObjectPool( ) = default;
    T* get_obj( );
    void release_obj( T* );
    void reserve( size_t );
    void resize( size_t );
    size_t size( );

private:
    ObjectsContainer< T > m_objects;
};

template< typename T >
ObjectPool< T >::ObjectPool( size_t size )
:m_objects( size )
{
}

template< typename T >
T* ObjectPool< T >::get_obj( )
{
    for ( auto& obj : m_objects )
    {
        if ( !obj.m_use )
        {
            obj.m_use = true;
            return obj.m_obj;
        }
    }

    Object< T > new_obj;
    new_obj.m_obj = T( );
    new_obj.m_use = true;
    m_objects.push_back( new_obj );

    return new_obj;
}

template< typename T >
void ObjectPool< T >::release_obj( T* object )
{
    for ( auto& obj : m_objects )
    {
        if ( obj.m_obj == object )
        {
            obj.m_use = false;
            break;
        }
    }
    
}

template< typename T >
void ObjectPool< T >::reserve( size_t size )
{
    m_objects.reserve( size );
}

template< typename T >
void ObjectPool< T >::resize( size_t size )
{
    m_objects.resize( size );
}

template< typename T>
size_t ObjectPool< T >::size( )
{
    return m_objects.size( );
}
