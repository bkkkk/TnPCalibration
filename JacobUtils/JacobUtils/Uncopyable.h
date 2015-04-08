#ifndef UNCOPYABLE_H_
#define UNCOPYABLE_H_ 1

namespace Uncopyable_ {
class Uncopyable {
 protected:
  Uncopyable() {}
  virtual ~Uncopyable() {}

 private:
  Uncopyable(const Uncopyable&);
  const Uncopyable& operator=(const Uncopyable&);
};
};

using uncopyable = Uncopyable_::Uncopyable;

#endif
