
struct vec2 {int x,y;};

class Object
{
public:
    Object() = default;
    ~Object() = default;
    vec2 getSize() noexcept {return size_;}
    vec2 getPos() noexcept {return pos_;}
    virtual int draw() = 0;
    void setSize(const vec2& size);
    void setPos(const vec2& pos);
private:
    vec2 size_;
    vec2 pos_;
};

void Object::setSize(const vec2& size)
{
    size_ = size;
}
void Object::setPos(const vec2& pos)
{
    pos_ = pos;
}