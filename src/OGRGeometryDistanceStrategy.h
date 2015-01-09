#ifndef WINZENT_SIMULATION_OGRGEOMETRYDISTANCESTRATEGY_H
#define WINZENT_SIMULATION_OGRGEOMETRYDISTANCESTRATEGY_H


#include <type_traits>

#include <QtCore>
#include <ogr_geometry.h>
//#include <boost/geometry/geometry.hpp>

#include <QtDebug>

#include "OGRPointAdapter.h"


namespace Winzent {
    namespace Simulation {
        namespace boost {

            /*!
             * \brief The distance strategy for OGRGeometry objects
             */
            class OGRGeometryDistanceStrategy
            {
            public:
                    template <typename P1, typename P2>
                    inline qreal apply(P1 const &p1, P2 const &p2) const
                    {
                        return p1.Distance(&p2);
                    }
            };


            class OGRPointToPointDistanceStrategy:
                    public OGRGeometryDistanceStrategy
            {
            };


            class OGRPointToLineStringDistanceStrategy:
                    public OGRGeometryDistanceStrategy
            {
            public:
                    template <typename P1, typename P2, typename P3>
                    inline qreal apply(P1 const &p1, P2 const &p2, P3 const &p3) const
                    {
		        return 0.0; // TODO: Implement
                    }
            };
        }
    } // namespace Simulation
} // namespace Winzent


#ifdef WINZENT_SIMULATION_BOOST_OGRCOORDINATESYSTEM_H
using Winzent::Simulation::boost::OGRCoordinateSystemTag;
#endif // WINZENT_SIMULATION_BOOST_OGRCOORDINATESYSTEM_H
using Winzent::Simulation::boost::OGRGeometryDistanceStrategy;
using Winzent::Simulation::boost::OGRPointToPointDistanceStrategy;
using Winzent::Simulation::boost::OGRPointToLineStringDistanceStrategy;


// Register the distance strategy:

namespace boost {
    namespace geometry {
        namespace strategy {
            namespace distance {
                namespace services {


                    template <>
                    struct tag<OGRPointToPointDistanceStrategy>
                    {
                        typedef strategy_tag_distance_point_point type;
                    };


                    template <typename P1, typename P2>
                    struct return_type<
                            OGRPointToPointDistanceStrategy,
                            P1,
                            P2>
                    {
                        typedef qreal type;
                    };


                    template <>
                    struct comparable_type<OGRPointToPointDistanceStrategy>
                    {
                        typedef OGRPointToPointDistanceStrategy type;
                    };


                    template <>
                    struct default_strategy<
                                point_tag,
                                point_tag,
                                OGRPoint,
                                OGRPoint,
                                OGRCoordinateSystemTag,
                                OGRCoordinateSystemTag>
                    {
                        typedef OGRPointToPointDistanceStrategy type;
                    };


                    template <>
                    struct tag<OGRPointToLineStringDistanceStrategy>
                    {
                        typedef strategy_tag_distance_point_segment type;
                    };


                    template <typename P1, typename P2>
                    struct return_type<
                            OGRPointToLineStringDistanceStrategy,
                            P1,
                            P2>
                    {
                        typedef qreal type;
                    };


                    template <>
                    struct comparable_type<
                            OGRPointToLineStringDistanceStrategy>
                    {
                        typedef OGRPointToLineStringDistanceStrategy type;
                    };


                    template <>
                    struct get_comparable<
                            OGRPointToLineStringDistanceStrategy>
                    {
                        typedef comparable_type<
                                OGRPointToLineStringDistanceStrategy>::type
                                    comparable_type;


                        static inline comparable_type apply(
                                OGRPointToLineStringDistanceStrategy const &)
                        {
                            return comparable_type();
                        }
                    };


                    template <>
                    struct default_strategy<
                                point_tag,
                                segment_tag,
                                OGRPoint,
                                OGRPoint,
                                OGRCoordinateSystemTag,
                                OGRCoordinateSystemTag>
                    {
                        typedef OGRPointToLineStringDistanceStrategy type;
                    };
                } // namespace services
            } // namespace distance
        } // namespace strategy
    } // namespace geometry
} // namespace boost


#endif // WINZENT_SIMULATION_OGRGEOMETRYDISTANCESTRATEGY_H
