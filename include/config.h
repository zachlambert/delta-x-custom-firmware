#ifndef CONFIG_H
#define CONFIG_H

#include "pin.h"

// 54, 55, 38, 3
static Pin theta_1_pulse = {PORT_F, 0};
static Pin theta_1_dir = {PORT_F, 1};
static Pin theta_1_en = {PORT_D, 7};
static Pin theta_1_endstop = {PORT_E, 5};

// 60, 61, 56, 14
static Pin theta_2_pulse = {PORT_F, 6};
static Pin theta_2_dir = {PORT_F, 7};
static Pin theta_2_en = {PORT_F, 2};
static Pin theta_2_endstop = {PORT_J, 1};

// 46, 48, 62, 18
static Pin theta_3_pulse = {PORT_L, 3};
static Pin theta_3_dir = {PORT_L, 1};
static Pin theta_3_en = {PORT_K, 0};
static Pin theta_3_endstop = {PORT_D, 3};

#endif
