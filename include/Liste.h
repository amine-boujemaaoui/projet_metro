#ifndef __LISTE_H__
#define __LISTE_H__

#include "Struct.h"

/**
 * @brief Fonction pour ajouter le maillon m en tête de la liste l
 *
 * @param l La liste à laquelle on ajoute un maillon
 * @param m Le maillon que l'on ajoute en tête de la liste
 */
void add_tete(Liste *l, Maillon *m);

/**
 * @brief Fonction pour ajouter le maillon m en queue de la liste l
 *
 * @param l La liste à laquelle on ajoute un maillon
 * @param m Le maillon que l'on ajoute en queue de la liste
 */
void add_queue(Liste *l,
               Maillon *m);

/**
 * @brief Fonction pour ajouter le maillon m à la position pos de la liste l
 *
 * @param l La liste à laquelle on ajoute un maillon
 * @param m Le maillon que l'on ajoute en position pos de la liste
 * @param pos La position à laquelle on ajoute le maillon
 */
void add_position(Liste *l,
                  Maillon *m,
                  uint32_t pos);

/**
 * @brief Fonction pour ajouter le maillon m à la liste l en gradant la liste triée dans l'ordre croissant de poids
 *
 * @param l La liste à laquelle on ajoute un maillon
 * @param m Le maillon que l'on ajoute en position pos de la liste
 */
void add_poidMin(Liste *l,
                 Maillon *m);

/**
 * @brief Fonction pour retirer le maillon en tête de la liste l
 *
 * @param l La liste à laquelle on retire le maillon en tête
 * @return Maillon*
 */
Maillon *rem_tete(Liste *l);

/**
 * @brief Fonction pour retirer le maillon en queue de la liste l
 *
 * @param l La liste à laquelle on retire le maillon en queue
 * @return Maillon*
 */
Maillon *rem_queue(Liste *l);

/**
 * @brief Fonction pour retirer le maillon a la position pos de la liste l
 *
 * @param l La liste à laquelle on retire le maillon
 * @param pos La position à laquelle on retire le maillon
 * @return Maillon*
 */
Maillon *rem_position(Liste *l,
                      uint32_t pos);

/**
 * @brief Renvoie true si le maillon est dans la liste
 *
 * @param l La liste a vérifié
 * @param id L'id a vérifier
 * @return true
 * @return false
 */
bool isin(Liste *l, uint32_t id);

#endif