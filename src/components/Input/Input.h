/**
 * @file
 * @brief Header of input for the user action
 */

#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus

#include <Qt>

extern "C" {
#endif

#include "../../brick_game/bg_enums.h"
#include "../../components/GameInfo/GameInfo.h"

#ifdef __cplusplus
}
#endif

/**
 * @brief Input processing for the user action
 * @param action User action
 * @param hold Hold action
 * @param last_key Last key
 * @param new_key New key
 * @return New key
 */
int getInput(UserAction_t *action, bool *hold, int last_key, int new_key);

#endif