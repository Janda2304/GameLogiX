

#ifndef COLOR_H
#define COLOR_H



struct color
{
    float r, g, b, a;
    
    color(const float r, const float g, const float b, const float a) : r(r), g(g), b(b), a(a) {}

    static color red()
    {
        return {1.0f, 0.0f, 0.0f, 1.0f};
    }

    static color red(float a)
    {
        return {1.0f, 0.0f, 0.0f, a};
    }

    static color black()
    {
        return color(0.0f, 0.0f, 0.0f, 1.0f);
    }

    static color black(float a)
    {
        return color(0.0f, 0.0f, 0.0f, a);
    }

    static color white()
    {
        return color(1.0f, 1.0f, 1.0f, 1.0f);
    }

    static color white(float a)
    {
        return {1.0f, 1.0f, 1.0f, a};
    }

    
    /**
     * 
     * @return r: 0.0f, g: 0.5f, b: 0.0f, a: 1.0f
     */
    static color green()
    {
        return {0.0f, 0.5f, 0.0f, 1.0f};
    }

    /**
     * @return r: 0.0f, g: 0.5f, b: 0.0f, a: <b>a</b>
     */
    static color green(float a)
    {
        return {0.0f, 0.5f, 0.0f, a};
    }

    static color persian_red()
    {
        return {0.8f, 0.2f, 0.2f, 1.0f};
    }

    static color persian_red(float a)
    {
        return {0.8f, 0.2f, 0.2f, a};
    }

    static color transparent()
    {
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }
    
    
    operator ImVec4() const
    {
        return {r, g, b, a};
    }
    
};



#endif //COLOR_H
