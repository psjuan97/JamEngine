#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable{
    public:
        virtual void Draw() = 0;

    bool Visibility = true;
};

#endif