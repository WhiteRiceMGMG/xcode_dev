/* trqcalif.h                                           */
/********************************************************/
/* object    | trqcal                                   */
/* edit his  | 2026/03/10 make new ver1.0               */
/*           |                                          */
/********************************************************/
#ifndef TRQCALIF_H
#define TRQCALIF_H

/********************************************************/
/* Header Includes                                      */
/********************************************************/

/********************************************************/
/* External Public Variables, Constants, Macros         */
/********************************************************/
extern u1 u1g_trqcalif_efctrq;      /* effective torque */

/********************************************************/
/* External Function Prototypes                         */
/********************************************************/
void vdg_trqcalif_pwon( void );     /* ctltim  : pwon   */
                                    /* args    : none   */
                                    /* rtn val : none   */

void vdg_trqcalif_50msm( void );    /* ctltim  : 50msm  */
                                    /* args    : none   */
                                    /* rtn val : none   */

#undef TRQCALIF_H
/********************************************************/
/* EOF                                                  */
/********************************************************/
