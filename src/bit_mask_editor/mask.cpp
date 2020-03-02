#include "mask.h"
#include <sstream>
#include <iomanip>

Mask::Mask(uint16_t w, uint16_t h)
    :width_(w), height_(h)
{
    data_.resize(Mask::getVectorSize(w, h), 0);
}

Mask::Mask(uint16_t w, uint16_t h, std::vector<uint32_t> v)
    :width_(w), height_(h), data_(v)
{
    data_.resize(Mask::getVectorSize(w, h), 0);
}


void
Mask::resize(uint16_t w, uint16_t h) {
    std::vector<uint32_t> new_data(Mask::getVectorSize(w, h));
    uint16_t min_width = std::min(width_, w);
    uint16_t min_height = std::min(height_, h);
    for (uint16_t i = 0; i < min_width; ++i) {
        for(uint16_t j = 0; j < min_height; ++j) {
            if (getAt(i, j)) {
                uint16_t offset = (j * w + i) / 32;
                uint8_t shift = 31 - ((j * w + i) % 32);
                new_data[offset] |= 1 << shift;
            }
        }
    }
    data_ = std::move(new_data);
    width_ = w;
    height_ = h;
}

bool
Mask::getAt(uint16_t x, uint16_t y) const {
    auto position = calculateOffset(x, y);
    return (data_[position.offset] & (1 << position.shift)) > 0;
}

void
Mask::setAt(uint16_t x, uint16_t y, bool val) {
    auto position = calculateOffset(x, y);
    if (val) {
        data_[position.offset] |= 1 << position.shift;
    } else {
        data_[position.offset] &= ~(1 << position.shift);
    }

}

Mask::position
Mask::calculateOffset(uint16_t x, uint16_t y) const {
    uint16_t offset = (y * width_ + x) / 32;
    uint8_t shift = 31 - ((y * width_ + x) % 32);
    return {offset, shift};
}

uint16_t
Mask::getVectorSize(uint16_t w, uint16_t h) {
    uint16_t addition = (w * h % 32) > 0;
    return w * h / 32 + addition;
}

std::string
Mask::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::ostream& operator << (std::ostream &out, const Mask& mask) {
    out << '{' << std::dec << mask.width_ << ',' << mask.height_ << ','
        << '{';
    bool first = true;
    out << std::hex;
    for (const auto& num: mask.data_) {
        if (!first) out << ',';
        first = false;
        out << "0x" << num;
    }
    out << "}}";
    return out;
}
