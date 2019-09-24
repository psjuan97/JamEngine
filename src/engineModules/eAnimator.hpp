// from meat starto
#ifndef ANIMATION_H
#define ANIMATION_H

#include <eTime.hpp>
#include <eClock.hpp>


#include <list>
#include <vector>
#include <string>


class Animator {
public:
    struct Animation
    {
        std::string _name;
        SDL_Texture* _texture;
        std::vector<SDL_Rect> _frames;
        eTime _duration;
        bool _loop;

        Animation(std::string const& name, std::string const& textureName,
            eTime const& duration, bool looping)
            : _name(name), m_TextureName(textureName), _duration(duration), _loop (looping)
        {



        }
        //Adds frames horizontaly
        void AddFrames( int alto,  int ancho, unsigned int nframes){
            SDL_Rect rect; 
            rect.x = 0;
            rect.y = 0;
            rect.w = ancho;
            rect.h = alto;

            for (unsigned int i = 0; i < nframes; i++)
            {
                _frames.push_back(rect);
                rect.x += ancho;
            }

        }

        bool isLooping(){
            return _loop;
        }

    };
    
    Animator(renderEngine::rSprite& sprite);
    Animator::Animation& CreateAnimation(std::string const& name, std::string const& textureName, renderEngine::rTime const& duration, bool loop = false);

    void Update(renderEngine::rTime const& dt);
    //Devuelve si el switch fue bien
    bool SwitchAnimation(std::string const& name);
    std::string GetCurrentAnimationName() const;

private:
        //Returns the animation with the passed name
        //Return nullptr si no encuentra la animacion

        Animator::Animation* FindAnimation(std::string const& name);
        void SwitchAnimation(Animator::Animation* animation);
        
        //Reference to the sprite que se ha de crear fuera de la clase 
        Sprite* _sprite;
        eTime m_CurrentTime;
        std::list <Animator::Animation> _animations;
        Animator::Animation* _currentAnimation;
        

};

#endif /* ANIMATOR_H */