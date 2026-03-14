/**
 * ============================================================
 * FICHIER : Block.cpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Block — obstacle descendant vers le joueur.
 *
 * Les blocs descendent à 0.1f px/frame (plus lentement que les ennemis à 0.2f).
 * Ils peuvent être détruits par les tirs du joueur (+10 pts au score).
 * Si un bloc non détruit touche le vaisseau, c'est game over.
 *
 * Cycle de vie d'un bloc :
 *   1. Spawné par spawnInitialBlocks() (en ligne) ou spawnDescendingBlocks() (aléatoire)
 *   2. Descend à chaque frame via update()
 *   3. Détruit par collision balle → destroy() (destroyed = true)
 *   4. Supprimé du vecteur par removeOffscreenBlocks() si y > 600
 *
 * Note : La texture utilisée est assets/images/enemy.png (réutilisée pour les blocs).
 *
 * Dépendances :
 *   - Block.hpp, SFML/Graphics.hpp
 * ============================================================
 */

#include "../include/Block.hpp"

/**
 * @brief Constructeur : charge la texture et positionne le bloc.
 *
 * @param x Position horizontale initiale (px)
 * @param y Position verticale initiale (px), négatif pour les blocs hors écran initiaux
 *
 * Initialise destroyed = false. Utilise la texture enemy.png (réutilisée pour les blocs).
 */
Block::Block(float x, float y) : destroyed(false) {
    texture.loadFromFile("assets/images/enemy.png");  // Texture réutilisée de l'ennemi
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

/**
 * @brief Descend le sprite de 0.1f px vers le bas à chaque frame.
 *
 * Le mouvement n'est effectué que si le bloc n'est pas détruit.
 * Vitesse plus lente que les ennemis (0.1f vs 0.2f) pour augmenter la difficulté progressivement.
 */
void Block::update() {
    if (!destroyed) {
        sprite.move(0, 0.1f);  // Descente lente : 0.1 px/frame
    }
}

/**
 * @brief Dessine le sprite dans la fenêtre si le bloc n'est pas détruit.
 *
 * @param window Référence constante à la fenêtre de rendu
 *
 * Les blocs détruits sont invisibles mais restent dans le vecteur
 * jusqu'à la purge par removeOffscreenBlocks().
 */
void Block::draw(sf::RenderWindow &window) const {
    if (!destroyed) {
        window.draw(sprite);
    }
}

/**
 * @brief Marque le bloc comme détruit (destroyed = true).
 *
 * Une fois détruit, le bloc cesse d'être dessiné et de participer aux collisions.
 * Il reste dans le vecteur jusqu'à la prochaine purge.
 */
void Block::destroy() {
    destroyed = true;
}

/**
 * @brief Indique si le bloc est détruit.
 * @return true si destroyed == true, false sinon
 */
bool Block::isDestroyed() const {
    return destroyed;
}

/**
 * @brief Retourne la hitbox globale du sprite pour les collisions.
 * @return sf::FloatRect rectangle englobant le sprite dans l'espace monde
 */
sf::FloatRect Block::getBounds() const {
    return sprite.getGlobalBounds();
}

/**
 * @brief Retourne la position verticale du sprite.
 *
 * Utilisée par removeOffscreenBlocks() pour supprimer les blocs sortis
 * en bas de l'écran (y > 600).
 *
 * @return float position Y en pixels
 */
float Block::getY() const {
    return sprite.getPosition().y;
}
