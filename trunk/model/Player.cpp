/* 
 * File:   Player.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:07 PM
 */

#include "Player.h"

Player::Player() {
}

Player::Player(int id, Movement movement):Character(id, movement) {
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

