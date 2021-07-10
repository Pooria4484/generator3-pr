/*
 * macro.h
 *
 *  Created on: May 20, 2021
 *      Author: Pooria
 */

#ifndef INC_MACRO_H_
#define INC_MACRO_H_
#define oil_on LL_GPIO_SetOutputPin(oil_l_GPIO_Port, oil_l_Pin)
#define oil_off LL_GPIO_ResetOutputPin(oil_l_GPIO_Port, oil_l_Pin)
#define water_on LL_GPIO_SetOutputPin(water_l_GPIO_Port, water_l_Pin)
#define water_off LL_GPIO_ResetOutputPin(water_l_GPIO_Port, water_l_Pin)
#define feul_on LL_GPIO_SetOutputPin(feul_l_GPIO_Port, feul_l_Pin)
#define feul_off LL_GPIO_ResetOutputPin(feul_l_GPIO_Port, feul_l_Pin)
#define emr_on LL_GPIO_SetOutputPin(emr_l_GPIO_Port, emr_l_Pin)
#define emr_off LL_GPIO_ResetOutputPin(emr_l_GPIO_Port, emr_l_Pin)
#define bat_on LL_GPIO_SetOutputPin(ol_l_GPIO_Port, ol_l_Pin)
#define bat_off LL_GPIO_ResetOutputPin(ol_l_GPIO_Port, ol_l_Pin)
#define ol_on LL_GPIO_SetOutputPin(bat_l_GPIO_Port, bat_l_Pin)
#define ol_off LL_GPIO_ResetOutputPin(bat_l_GPIO_Port, bat_l_Pin)
#define pwr_toggle LL_GPIO_TogglePin(pwr_GPIO_Port, pwr_Pin)
#define pwr_on LL_GPIO_SetOutputPin(pwr_GPIO_Port, pwr_Pin)
#define pwr_off LL_GPIO_ResetOutputPin(pwr_GPIO_Port, pwr_Pin)
#define er_toggle LL_GPIO_TogglePin(er_GPIO_Port, er_Pin)
#define er_on LL_GPIO_SetOutputPin(er_GPIO_Port, er_Pin)
#define er_off LL_GPIO_ResetOutputPin(er_GPIO_Port, er_Pin)
#define fr_on LL_GPIO_SetOutputPin(freq_l_GPIO_Port, freq_l_Pin)
#define fr_off LL_GPIO_ResetOutputPin(freq_l_GPIO_Port, freq_l_Pin)
#define vac_on LL_GPIO_SetOutputPin(vac_l_GPIO_Port,vac_l_Pin)
#define vac_off LL_GPIO_ResetOutputPin(vac_l_GPIO_Port,vac_l_Pin)
#define vac_toggle LL_GPIO_TogglePin(vac_l_GPIO_Port,vac_l_Pin)

#define start_on LL_GPIO_SetOutputPin(start_GPIO_Port, start_Pin)
#define start_off LL_GPIO_ResetOutputPin(start_GPIO_Port, start_Pin)

#define gov_on LL_GPIO_SetOutputPin(gov_GPIO_Port,gov_Pin)
#define gov_off LL_GPIO_ResetOutputPin(gov_GPIO_Port,gov_Pin)

#define siren_on LL_GPIO_SetOutputPin(sir_GPIO_Port,sir_Pin)
#define siren_off LL_GPIO_ResetOutputPin(sir_GPIO_Port,sir_Pin)

#define isStartPressed !((LL_GPIO_ReadInputPort(mute_GPIO_Port)) & (1<<15))
#define isMutePressed !((LL_GPIO_ReadInputPort(btn_start_GPIO_Port)) & (1<<3))

#define ms_delay(d) LL_mDelay((d))

#define oil_err !((LL_GPIO_ReadInputPort(water_GPIO_Port)) & (1<<7))
#define water_err !((LL_GPIO_ReadInputPort(oil_GPIO_Port)) & (1<<0))
#define feul_err !((LL_GPIO_ReadInputPort(feul_GPIO_Port)) & (1<<15))
#define emr_err !((LL_GPIO_ReadInputPort(emr_GPIO_Port)) & (1<<8))
#define dyn_err !((LL_GPIO_ReadInputPort(gen_GPIO_Port)) & (1<<14))
#define ol_err !((LL_GPIO_ReadInputPort(ol_GPIO_Port)) & (1<<1))


#define vbat_min 1.0
#define vdyn_min 1.26//26 volt
#define vac_min 0.35
#define vac_max 1.27

#endif /* INC_MACRO_H_ */
