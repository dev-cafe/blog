#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

struct VectorWtf
{
  VectorWtf(const std::vector<size_t> & s, size_t w) :
    nValues_(std::accumulate(s.begin(),
                                 s.end(),
                                 1,
                                 std::multiplies<size_t>())),
    buffer_(nValues_ * w, char(0)) {
      std::cout << "nValues_ " << nValues_ << std::endl;
      std::cout << "w " << w << std::endl;
      std::cout << "nValues_ * w " << nValues_ * w << std::endl;
      assert(buffer_.size() == nValues_ * w);
      for (size_t i = 0; i < nValues_ * w; ++i) {
        std::cout << buffer_[i] << std::endl;
      }
      std::cout << "buffer_.size() " << buffer_.size() << std::endl;
  }

  std::vector<char> buffer_;
  size_t nValues_;
};

int main()
{
  std::vector<size_t> shape({10, 11});
  size_t w = 16;

  VectorWtf(shape, w);

  return 0;
}
