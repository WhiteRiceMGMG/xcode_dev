/* acelcrtif.h                                          */
/********************************************************/
/* object    | crt acel                                 */
/* edit his  | 2023/03/28 make Ver1.0                   */
/*           |                                          */
/********************************************************/
#ifndef ACELCRTIF_H
#define ACELCRTIF_H

/********************************************************/
/* Header Includes                                      */
/********************************************************/

/********************************************************/
/* External Public Variables, Constants, Macros         */
/********************************************************/
extern u1 u1g_acelcrtif_thlopn; /* crted acel thl opn(%) */
extern u1 u1g_acelcrtif_crtflg; /* acel crt flg */

/********************************************************/
/* External Function Prototypes                         */
/********************************************************/
/********************************************************/

void vdg_acelcrtif_pwon( void );    /* ctltim  : pwon   */
                                    /* args    : none   */
                                    /* rtn val : none   */


void vdg_acelcrtif_50msm( void );   /* ctltim  : 50msm  */
                                    /* args    : none   */
                                    /* rtn val : none   */

#undef HEADER_H
/********************************************************/
/* EOF                                                  */
/********************************************************/
