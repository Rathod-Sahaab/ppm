#ifndef PPM_HPP
#define PPM_HPP

#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

struct Header {
  std::string format;
  unsigned width, height;
  unsigned max_pixel_value;

  friend std::ostream& operator<<(std::ostream&, const Header&);
};

// Base class PixMap
template <class T>
class PixMap {
  Header head;
  std::deque<std::vector<T>> data;

 public:
  PixMap();
  PixMap(std::string, size_t width, size_t height, unsigned max_value);

  template <class U>
  friend std::ostream& operator<<(std::ostream&, const PixMap<U>&);

  inline unsigned get_height() const;
  inline unsigned get_width() const;

  void fill(T val);

  PixMap<T>& set_pixel(size_t x, size_t y, T val);
};
std::ostream& operator<<(std::ostream& out, const Header& h) {
  out << h.format << '\n'
      << h.width << ' ' << h.height << '\n'
      << h.max_pixel_value << '\n';
  return out;
}

template <class T>
inline unsigned PixMap<T>::get_height() const {
  return head.height;
}

template <class T>
inline unsigned PixMap<T>::get_width() const {
  return head.width;
}

template <class U>
std::ostream& operator<<(std::ostream& out, const PixMap<U>& pix_map) {
  out << pix_map.head;
  for (const auto& dat : pix_map.data) {
    for (const auto& d : dat) {
      out << d << '\n';
    }
  }
  return out;
}

template <class T>
PixMap<T>::PixMap(std::string format, size_t width, size_t height,
                  unsigned max_pixel_value) {
  head.format = format;
  head.width = width;
  head.height = height;
  head.max_pixel_value = max_pixel_value;

  data.resize(height);
  for (auto& d : data) {
    d.resize(width);
  }
}

template <class T>
PixMap<T>& PixMap<T>::set_pixel(size_t x, size_t y, T val) {
  if (x >= 0 and x < head.width and y >= 0 and y < head.height) {
    data.at(y).at(x) = val;
  }
  return *this;
}

template <class T>
void PixMap<T>::fill(T val) {
  for (auto& row : data) {
    for (auto& elm : row) {
      elm = val;
    }
  }
}
// Base class PixMap

class PixBitMap : public PixMap<unsigned> {
 public:
  PixBitMap();
  PixBitMap(size_t width, size_t height);
};

PixBitMap::PixBitMap(size_t width, size_t height)
    : PixMap<unsigned>("P1", width, height, 1) {}

class PixGreyMap : public PixMap<unsigned> {
 public:
  PixGreyMap();
  PixGreyMap(size_t width, size_t height, unsigned max_pixel_value);
};

PixGreyMap::PixGreyMap(size_t width, size_t height, unsigned max_pixel_value)
    : PixMap<unsigned>("P2", width, height, max_pixel_value) {}

struct RGB {
  unsigned r, g, b;
  friend std::ostream& operator<<(std::ostream&, const RGB&);
  RGB();
  RGB(unsigned, unsigned, unsigned);
};

RGB::RGB() {
  r = 0;
  g = 0;
  b = 0;
}

RGB::RGB(unsigned red, unsigned green, unsigned blue) {
  r = red;
  g = green;
  b = blue;
}

std::ostream& operator<<(std::ostream& out, const RGB& rgb) {
  out << rgb.r << ' ' << rgb.g << ' ' << rgb.b;
  return out;
}

class PixPixMap : public PixMap<RGB> {
 public:
  PixPixMap();
  PixPixMap(size_t width, size_t height, unsigned max_pixel_value);
};

PixPixMap::PixPixMap(size_t width, size_t height, unsigned max_pixel_value)
    : PixMap<RGB>("P3", width, height, max_pixel_value) {}

#endif  // PPM_HPP
