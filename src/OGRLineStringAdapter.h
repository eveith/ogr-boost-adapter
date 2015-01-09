#ifndef OGRLINESTRINGTOBOOSTADAPTER_H
#define OGRLINESTRINGTOBOOSTADAPTER_H


#include <ogr_geometry.h>

#include <boost/range.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>

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
            typedef OGRPointCollectionIter<
                    const OGRLineString,
                    const OGRPoint>
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
range_begin(OGRLineString const &l)
{
    return Winzent::Simulation::boost::OGRLineStringConstIterator(l);
}


inline Winzent::Simulation::boost::OGRLineStringConstIterator
range_end(OGRLineString const &l)
{
    auto iter = range_begin(l);
    iter += l.getNumPoints();
    return iter;
}


namespace boost {
    namespace geometry {
        namespace traits {


            template<>
            struct tag<OGRLineString>
            {
                typedef linestring_tag type;
            };
        }
    }
}


#endif // OGRLINESTRINGTOBOOSTADAPTER_H
