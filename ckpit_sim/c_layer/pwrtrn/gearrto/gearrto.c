/* gearrto.c                                            */
/********************************************************/
/* object    | gearrto                                  */
/* edit his  | 2026/03/03 make new ver1.0               */
/*           |                                          */
/********************************************************/
/********************************************************/
/* Header Includes                                      */
/********************************************************/
#include "../../inc/common.h"     /* common library     */
#include "../../conf/gearconf.h"  /* u1g_GEAR_NEUTRAL,  */
                                  /* u1g_GEAR_MAX       */
#include "../gearcrtif.h"         /* u1g_gearcrtif_shft */
#include "../gearrtoif.h"         /* self header        */ 

/********************************************************/
/* External Public Variables, Consants, Macros          */
/********************************************************/
u1 u1g_gearrtoif_ratio;      /* rate  lsb=10/256, osf=5 */

/********************************************************/
/* Internal Public Variables, Constans, Macros          */
/********************************************************/
#define u1s_GEARRTO_ONE     (u1)(((3.5 + 5)  / (10 / 256)) + 0.5) /* rate1 lsb=10/256, osf=5 */
#define u1s_GEARRTO_TWO     (u1)(((2.1 + 5)  / (10 / 256)) + 0.5) /* rate2 lsb=10/256, osf=5 */
#define u1s_GEARRTO_THREE   (u1)(((1.4 + 5)  / (10 / 256)) + 0.5) /* rate3 lsb=10/256, osf=5 */
#define u1s_GEARRTO_FOUR    (u1)(((1.0 + 5)  / (10 / 256)) + 0.5) /* rate4 lsb=10/256, osf=5 */
#define u1s_GEARRTO_FIVE    (u1)(((0.8 + 5)  / (10 / 256)) + 0.5) /* rate5 lsb=10/256, osf=5 */
#define u1s_GEARRTO_NEUTRAL (u1)(((0 + 5)    / (10 / 256)) + 0.5) /* rateR lsb=10/256, osf=5 */
#define u1s_GEARRTO_REVERSE (u1)(((-3.2 + 5) / (10 / 256)) + 0.5) /* rateN lsb=10/256, osf=5 */

/* info of shift (1-5,N,R) to rate */
static const u1 u1s_GEARRTO_TBL[u1g_GEAR_NUM] =
{
    u1s_GEARRTO_ONE,
    u1s_GEARRTO_TWO,
    u1s_GEARRTO_THREE,
    u1s_GEARRTO_FOUR,
    u1s_GEARRTO_FIVE,
    u1s_GEARRTO_NEUTRAL,
    u1s_GEARRTO_REVERSE
};

/********************************************************/
/* External Public Function Definitions                 */
/********************************************************/
/********************************************************/
/* func    | vdg_gearrtoif_pwon()                       */
/* abst    | pwon                                       */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_gearrtoif_pwon( void )
{
    vdg_gearrto_renew();
}

/********************************************************/
/* func    | vdg_gearrtoif_50msm()                      */
/* abst    | 50msm                                      */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_gearrtoif_50msm( void )
{
    vdg_gearrto_renew();
}

/********************************************************/
/* Internal Public Function Definitions                 */
/********************************************************/
/********************************************************/
/* func    | vdg_gearrto_renew()                        */
/* abst    | renew gear rto                             */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_gearrto_renew( void )
{
    u1 u1t_gearcrt;
    u1 u1t_gearrto;

    u1t_gearcrt = u1g_gearcrtif_shft;

    u1t_gearrto = u1s_GEARRTO_TBL[u1g_GEAR_NEUTRAL];
    if ( u1t_gearcrt <= u1g_GEAR_MAX )
    {
        u1t_gearrto = u1s_GEARRTO_TBL[u1t_gearcrt];
    }

    u1g_gearrtoif_ratio = u1t_gearrto;
}

/********************************************************/
/* EOF                                                  */
/********************************************************/
