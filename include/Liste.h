#ifndef __LISTE_H__
#define __LISTE_H__

#include "Struct.h"

/**
 * @brief Fonction pour ajouter le maillon m en tete de la liste l
 *
 * @param l la liste à laquel on ajoute un maillon
 * @param m le maillon que l'on ajoute en tete de la liste
 */
void add_tete(Liste *l,
              Maillon *m);

/**
 * @brief Fonction pour ajouter le maillon m en queue de la liste l
 *
 * @param l la liste à laquel on ajoute un maillon
 * @param m le maillon que l'on ajoute en queue de la liste
 */
void add_queue(Liste *l,
               Maillon *m);

/**
 * @brief Fonction pour ajouter le maillon m à la position pos de la liste l
 *
 * @param l la liste à laquel on ajoute un maillon
 * @param m le maillon que l'on ajoute en posotion pos de la liste
 * @param pos la position a laquel on ajoute le maillon
 */
void add_position(Liste *l,
                  Maillon *m,
                  uint32_t pos);

/**
 * @brief Fonction pour ajouter le maillon m à la liste l en gradant la liste trier dans l'ordre croissant de poid
 *
 * @param l la liste à laquel on ajoute un maillon
 * @param m le maillon que l'on ajoute en posotion pos de la liste
 */
void add_poidMin(Liste *l,
                 Maillon *m);

/**
 * @brief Fonction pour retirer le maillon en tete de la liste l
 *
 * @param l la liste à laquel on retire le maillon en tete
 * @return Maillon*
 */
Maillon *rem_tete(Liste *l);

/**
 * @brief Fonction pour retirer le maillon en queue de la liste l
 *
 * @param l la liste à laquel on retire le maillon en queue
 * @return Maillon*
 */
Maillon *rem_queue(Liste *l);

/**
 * @brief Fonction pour retirer le maillon a la position pos de la liste l
 *
 * @param l la liste à laquel on retire le maillon
 * @param pos la position a laquel on retire le maillon
 * @return Maillon*
 */
Maillon *rem_position(Liste *l,
                      uint32_t pos);

/**
 * @brief renvoie true si le maillon est dans la liste
 * 
 * @param l la liste a verifier
 * @param id l'id a verifier
 * @return true 
 * @return false 
 */
bool isin(Liste *l, uint32_t id);

#endif