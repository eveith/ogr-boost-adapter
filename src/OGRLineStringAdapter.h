#ifndef OGRLINESTRINGTOBOOSTADAPTER_H
#define OGRLINESTRINGTOBOOSTADAPTER_H


#include <ogr_geometry.h>

#include <boost/range.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>
#include <boost/geometry/geometries/register/multi_linestring.hpp>

#include "boost/OGRPointAdapter.h"
#include "boost/OGRPointCollectionIterator.h"



namespace  Winzent {
    namespace Simulation {
        namespace boost {

            /*!
             * \brief An iterator for OGRLineString objects
             */
            typedef OGRPointCollectionIter<OGRLineString, OGRPoint>
                    OGRLineStringIterator;

            /*!
             * \brief A const-access iterator for OGRLineString objects
             */
            typedef OGRPointCollectionIter<const OGRLineString, OGRPoint>
                    OGRLineStringConstIterator;
        } // namespace boost
    } // namespace Simulation
} // namespace Winzent


namespace boost {
    template <>
    struct range_iterator<OGRLineString>
    {
        typedef Winzent::Simulation::boost::OGRLineStringIterator type;
    };


    template <>
    struct range_const_iterator<OGRLineString>
    {
        typedef Winzent::Simulation::boost::OGRLineStringConstIterator type;
    };
}


inline Winzent::Simulation::boost::OGRLineStringIterator
range_begin(OGRLineString &l)
{
    return Winzent::Simulation::boost::OGRLineStringIterator(l);
}


inline Winzent::Simulation::boost::OGRLineStringIterator
range_end(OGRLineString &l)
{
    auto iter = range_begin(l);
    iter += l.getNumPoints();
    return iter;
}


inline Winzent::Simulation::boost::OGRLineStringConstIterator
range_begin(const OGRLineString &l)
{
    return Winzent::Simulation::boost::OGRLineStringConstIterator(l);
}


inline Winzent::Simulation::boost::OGRLineStringConstIterator
range_end(const OGRLineString &l)
{
    auto iter = range_begin(l);
    iter += l.getNumPoints();
    return iter;
}


namespace boost {
    namespace geometry {
        namespace traits {


            template<>
            struct tag<OGRLineString *>
            {
                typedef linestring_tag type;
            };


            template<>
            struct tag<OGRLineString>
            {
                typedef linestring_tag type;
            };
        } // namespace traits
    } // namespace geometry
} // namespace boost



#endif // OGRLINESTRINGTOBOOSTADAPTER_H
