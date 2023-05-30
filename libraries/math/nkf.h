#ifndef NKF_H
#define NKF_H

#include <vector.h>
#include <matrix.h>
#include <defines.h>
#include <map>
#include <cmath>
#include <cassert>
#include <utility>

/*! \class NKF
*   \brief Class which solves the MLAT problem
*   This class implements the Gauss-Newton algorithm
*   for the least squares problem
*/
class NKF 
{
public:
    //! Constructor
    NKF() = default;
    //! Destructor
    ~NKF() = default;
    //! Returns the Jacobian of the least squares problem
    OurMatrix<EQUATIONS_COUNT, 3> getJacobian(OurVector<3>& position);
    //! Setter for tower coordinates
    void setTowersCoordinates(std::map<uint16_t, OurVector<3>> tower_coordinates);
    //! Setter for initial parameters
    void setInitialParams(const OurVector<3>& initial_coordinates, const OurVector<EQUATIONS_COUNT>& initial_tdoas);
    //! Method which return the solution
    OurVector<3> solve(OurVector<EQUATIONS_COUNT>& tdoas);

private:
    //! Calculates the distance between two dots
    double distance(const OurVector<3>& from, const OurVector<3>& to);
    //! Returns the Jacobian row
    OurVector<3> getJacobianRow(OurVector<3>& position, uint8_t tower_i, uint8_t tower_j);

private:
    //! Initial coordinates
    OurVector<3> _initial_coordinates;
    //! Initial TDOAS
    OurVector<EQUATIONS_COUNT> _initial_tdoas;
    //! Tower coordinates
    std::map<uint16_t, OurVector<3>> _towers_coordinates;


    OurVector<3> _state; //! (x, y, z)
	OurVector<EQUATIONS_COUNT> _observation;
	OurMatrix<3, 3> _evolution; //! Matrix F
	OurMatrix<3, 3> _covariance_state; //! Matrix P

	OurMatrix<EQUATIONS_COUNT, 3> _observation_mtx; //! Matrix H
	OurMatrix<EQUATIONS_COUNT, EQUATIONS_COUNT> _observation_error; //! Matrix R
};

#endif