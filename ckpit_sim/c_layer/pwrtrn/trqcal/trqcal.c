/* trqcal.c                                             */
/********************************************************/
/* object    | trque calcuation                         */
/* edit his  | 2026/03/10 make new ver1.0               */
/*           |                                          */
/********************************************************/
/********************************************************/
/* Header Includes                                      */
/********************************************************/
#include "../../inc/common.h"  /* common library        */
#include "../clthcrtif.h"      /* u1g_clthcrtif_crtrate */
#include "../acelcrtif.h"      /* u1g_acelcrtif_thlopn  */
#include "../../conf/config.h" /* u1g_TORQUE_MAX        */

/********************************************************/
/* External Public Variables, Constants, Macros         */
/********************************************************/
u1 u1g_trqcalif_efctrq;            /* efc trq lsb=1/256 */

/********************************************************/
/* Internal Public Variables, Constants, Macros         */
/********************************************************/

/********************************************************/
/* External Public Function Definitions                 */
/********************************************************/
/********************************************************/
/* func    | vdg_trqcalif_pwon( void )                  */
/* abst    | torque calcuation pwon function            */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_trqcalif_pwon( void )
{
    vds_trqcal_renew();
}

/********************************************************/
/* func    | vdg_trqcalif_50msm( void )                 */
/* abst    | torque calcuation 50msm function           */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_trqcalif_50msm( void )
{
    vds_trqcal_renew();
}

/********************************************************/
/* Internal Public Function Definitions                 */
/********************************************************/
/********************************************************/
/* func    | vds_trqcal_renew( void )                   */
/* abst    | renew effective trque                      */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vds_trqcal_renew( void )
{
    u1 u1t_torque;      /* temporary torque           */
    u1 u1t_torque_max;  /* temporary torque max       */
    u1 u1t_efctrq;      /* temporary effective torque */
    u1 u1t_trqrate      /* temporary torque rato      */
    u1 u1t_acel_thlopn; /* temporary accel throttle   */

    u1t_torque_max = u1g_TORQUE_MAX; /* get max torque  */
    u1t_trqrate = u1g_clthcrtif_trqrate; /* get trqrate */
    u1t_acel_thlopn = u1g_acelcrtif_thlopn; /* get acl  */

    /* calcuation temporary torque */
    u1t_torque = u1t_torque_max * u1t_acel_thlopn;

    /* calcuation temporary effective torque */
    u1t_efctrq = u1t_torque * u1t_trqrate;

    /* release effective torque */
    u1g_trqcalif_efctrq = u1t_efctrq;
}

/********************************************************/
/* EOF                                                  */
/********************************************************/

