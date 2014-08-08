#ifndef RENDERABLE_H
#define RENDERABLE_H


class Renderable
{
    public:
        Renderable(float, float);
        virtual ~Renderable();
        void setTex(int);
        int getTex();
        float getX();
        void setX(float);
        float getY();
        void setY(float);
        float getR();
        void setR(float);
    protected:
    private:
        float x;
        float y;
        float r;
        int tex;
};

#endif // RENDERABLE_H
