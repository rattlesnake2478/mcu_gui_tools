#ifndef MASK_H
#define MASK_H

#include <cstdint>
#include <vector>
#include <string>

#include <QMetaType>

class Mask
{
public:
    static const int DEFAULT_SIZE = 10;

    Mask() : Mask (DEFAULT_SIZE, DEFAULT_SIZE) {};
    Mask(uint16_t, uint16_t);
    Mask(uint16_t, uint16_t, std::vector<uint32_t>);
    void resize(uint16_t, uint16_t);
    uint16_t getWidth() const { return width_; }
    uint16_t getHeight() const { return height_; }
    const uint32_t* getRawData() const { return data_.data(); }
    bool getAt(uint16_t, uint16_t) const;
    void setAt(uint16_t, uint16_t, bool);
    std::string toString() const;
    friend std::ostream& operator << (std::ostream &out, const Mask& mask);

private:
    typedef struct {
        uint16_t offset;
        uint8_t shift;
    } position;

    uint16_t width_;
    uint16_t height_;
    std::vector<uint32_t> data_;

    position calculateOffset(uint16_t, uint16_t) const;
    static uint16_t getVectorSize(uint16_t, uint16_t);

};

Q_DECLARE_METATYPE(Mask);


#endif // MASK_H
