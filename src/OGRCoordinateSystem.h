#ifndef WINZENT_SIMULATION_BOOST_OGRCOORDINATESYSTEM_H
#define WINZENT_SIMULATION_BOOST_OGRCOORDINATESYSTEM_H


#include <boost/geometry/geometry.hpp>


namespace Winzent {
    namespace Simulation {
        namespace boost {

            struct OGRCoordinateSystem
            {
            };


            struct OGRCoordinateSystemTag
            {
            };
        } // namespace boost
    } // namespace Simulation
} // namespace Winzent


using Winzent::Simulation::boost::OGRCoordinateSystem;
using Winzent::Simulation::boost::OGRCoordinateSystemTag;


namespace boost {
    namespace geometry {
        namespace traits {

            template<>
            struct cs_tag<OGRCoordinateSystem>
            {
                typedef OGRCoordinateSystemTag type;
            };
        }
    }
}


#endif // WINZENT_SIMULATION_BOOST_OGRCOORDINATESYSTEM_H
