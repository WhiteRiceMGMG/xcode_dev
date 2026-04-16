/* crthcrt.c                                            */
/********************************************************/
/* object    | clthcrt                                  */
/* edit his  | 2026.03.05 make new ver1.0               */
/*           |                                          */
/********************************************************/
/********************************************************/
/* Header Includes                                      */
/********************************************************/
#include "../../inc/common.h"     /* common library     */
#include "../../swift/swiftif.h"  /* u1g_swiftif_clth   */
#include "../clthcrtif.h"         /* self header        */

/********************************************************/
/* External Public Variables, Consants, Macros          */
/********************************************************/
u1 u1g_clthcrtif_trqrate;        /* trq com   lsb=1/256 */
u1 u1g_clthcrtif_crtflg;         /* correcion onoff     */

/********************************************************/
/* Internal Public Variables, Constans, Macros          */
/********************************************************/

/********************************************************/
/* External Public Function Definitions                 */
/********************************************************/
/********************************************************/
/* func    | vdg_clthcrtif_pwon()                       */
/* abst    | Clutch Correction pwon                     */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_clthcrtif_pwon( void )
{
    /* when pwon set trq-com 0&, and cor off */
    u1g_clthcrtif_trqrate = (u1)0;
    u1g_clthcrtif_crtflg = (u1)OFF;
}

/********************************************************/
/* func    | vdg_clthcrtif_50msm()                      */
/* abst    | Clutch Correction 50msm                    */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_clthcrtif_50msm( void )
{
    u1 u1t_clthpct; /* input clutch percent */
    u1 u1t_clthrto; /* trq com              */
    u1 u1t_clthflg; /* trq cor onoff        */

    u1t_clthpct = u1g_swiftif_clth;

    u1t_clthrto = (u1)0;
    u1t_clthflg = (u1)OFF;
    if (u1t_clthpct <= 40)
    {
        u1t_clthflg = (u1)ON;
        u1t_clthrto = (u1)((clthpct * 50) / 40)
    }
    else if (u1t_clthpct <= 70)
    {
        u1t_clthflg = (u1)ON;
        u1t_clthrto =  (u1)(50 + ((clthpct - 40) * 5))
    }
    else
    {
        u1t_clthclg = (u1)ON;
        u1t_clthrto = (u1)(200 + ((clthpct - 70) * 2))
    }

    u1g_clthcrtif_trqrate = u1t_clthrto;

    u1g_clthcrtif_crtflg = u1t_clthflg;

}

/********************************************************/
/* Internal Public Function Definitions                 */
/********************************************************/

/********************************************************/
/* func    | u1 u1g_sample_function( void )             */
/* abst    | drive mode getter function                 */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/

/********************************************************/
/* EOF                                                  */
/********************************************************/

