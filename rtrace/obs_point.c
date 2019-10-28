
/*********************************************************************
 * The Open Group Base Specifications Issue 6
 * IEEE Std 1003.1, 2004 Edition
 *
 *    An XSI-conforming application should ensure that the feature
 *    test macro _XOPEN_SOURCE is defined with the value 600 before
 *    inclusion of any header. This is needed to enable the
 *    functionality described in The _POSIX_C_SOURCE Feature Test
 *    Macro and in addition to enable the XSI extension.
 *
 *********************************************************************/
#define _XOPEN_SOURCE 600

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <complex.h>

#include "v.h"

int intersect( cplex_type res[2],
                vec_type *sign,
                vec_type *loc,
                vec_type *axi,
                vec_type *obs_p,
                vec_type *obs_v );

int main ( int argc, char **argv)
{

    int intersect_cnt = 0;
    cplex_type intersections[2];

    vec_type tmp[3];

    /* We must first define where our observation plane is in R3
     * as a point and a normal direction. The obs_normal direction 
     * will be the direction of all rays that we trace. */
    vec_type obs_origin, obs_normal;

    /* The observation plane has its own coordinate system and 
     * thus we have x_prime_vec and y_prime_vec as ortogonal
     * and normalized vectors */
    vec_type x_prime_vec, y_prime_vec;

    /* To locate a given point on the observation plane we will
     * need scalar distances away from the observation plane
     * center along the directions x_prime_vec and y_prime_vec */
    double x_prime, y_prime;

    /* All of the above merely allows us to compute a starting
     * point for our ray to trace along the direction of the
     * vector obs_normal. */
    vec_type obs_point;

    /* Test case will be an observation plane at ( 12, 0, 0 ) */
    cplex_vec_set( &obs_origin, 12.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* Observation direction is along negative i_hat basis vector */
    cplex_vec_set( &obs_normal, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* we arbitrarily choose the x_prime_vec and y_prime_vec */
    /* x_prime_vec is < 0, 1, 0 > */
    cplex_vec_set( &x_prime_vec, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);

    /* y_prime_vec is < 0, 0, 1 > */
    cplex_vec_set( &y_prime_vec, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /* A test point to begin with on the observation plane */
    x_prime = 1.7;
    y_prime = -2.0;

    /* All of the above allows us to compute a starting point on
     * the observation plane in R3 and in the coordinate system
     * of the observation object.
     *
     * obs_point = x_prime * x_prime_vec 
     *           + y_prime * y_prime_vec
     *           + obs_origin
     *
     */
    cplex_vec_scale( tmp,   &x_prime_vec, x_prime );
    cplex_vec_scale( tmp+1, &y_prime_vec, y_prime );

    cplex_vec_add( tmp+2, tmp, tmp+1);
    cplex_vec_add( tmp, tmp+2, &obs_origin );

    cplex_vec_copy( &obs_point, tmp );

    printf("INFO : obs_point = ");
    cplex_vec_print( &obs_point );
    printf("\n");


    /* At this moment we have the observation point and the direction
     * of the plane within obs_normal. What we need is to pass all
     * this to an object_intercept function that will determine a
     * k index value on the ray trace line.
     *
     * See page 6 of the note on github at :
     *     https://github.com/blastwave/lastmiles/
     *            rtrace/math_notes/notes_006.png
     *
     * So clearly we need :
     *
     *     Our L0 point is obs_point, sign_data, object_location,
     *     semi_major_axi, ray_direction.
     *
     *     At the moment for this test we shall use : 
     *
     *         sign_data = < 1, 1, 1 >
     *
     *         object_location = < 0, 0, 0 >
     *
     *         semi_major_axi = < 5, 2, 6 >
     *
     *         ray_direct = obs_normal where this must be a
     *                           normalized vector
     *
     * */
    vec_type sign_data, object_location, semi_major_axi, ray_direct;

    /* Within the set of signs Sx, Sy, and Sz we do not care about
     * the complex component and merely want the real. The same
     * may be said for object_location, semi_major_axi and the
     * direction of our ray ray_direct */
    cplex_vec_set( &sign_data, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    cplex_vec_set( &object_location, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    cplex_vec_set( &semi_major_axi, 5.0, 0.0, 2.0, 0.0, 6.0, 0.0);
    cplex_vec_copy( &ray_direct, &obs_normal );


    intersect_cnt = intersect ( intersections, &sign_data,
                                &object_location, &semi_major_axi,
                                &obs_point, &obs_normal );

    printf ("INFO : we have %i intersection points.\n", intersect_cnt);


    return ( EXIT_SUCCESS );

}

int intersect( cplex_type res[2],
                vec_type *sign,
                vec_type *loc,
                vec_type *axi,
                vec_type *obs_p,
                vec_type *obs_v )
{

    /* computer the intersection points between our line and the
     * analytic surface described and return an integer count
     * of the real intersections. */

    vec_type tmp[9];

    /* we shall form the complex cooefficients of a quadratic */
    cplex_type A, B, C;




    return ( 0 );

}

