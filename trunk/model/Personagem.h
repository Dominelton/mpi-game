/* 
 * File:   Personagem.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:06 PM
 */

#ifndef PERSONAGEM_H
#define	PERSONAGEM_H
#include "Posicao.h"

class Personagem {
public:
    Personagem();
    Personagem(const Personagem& orig);
    virtual ~Personagem();
    void mover();
    void parar();
    
    Posicao getPosicao(){
        return posicao;
    }
    void setPosicao(Posicao posicao){
        this->posicao = posicao;
    }
    int getVelocidade(){
        return velocidade;
    }
    void setVelocidade(int velocidade){
        this->velocidade = velocidade;
    }
    
private:
    Posicao posicao;
    int velocidade;
};

#endif	/* PERSONAGEM_H */

