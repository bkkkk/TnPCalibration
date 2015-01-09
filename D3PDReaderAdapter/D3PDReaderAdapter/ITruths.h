#ifndef D3PDREADERADAPTER_ITRUTHS
#define D3PDREADERADAPTER_ITRUTHS 1

#include <vector>

class ITruth {
public:
  virtual ~ITruth() { }

  virtual const std::vector<std::size_t> child_index() const = 0;
  virtual std::vector<std::size_t> child_index() = 0;

  virtual const std::vector<std::size_t> parent_index() const = 0;
  virtual std::vector<std::size_t> parent_index() = 0;

  virtual const int pdgId() const = 0;
  virtual int pdgId() = 0;

  virtual const int eta() const = 0;
  virtual int eta() = 0;

  virtual const int phi() const = 0;
  virtual int phi() = 0;

  virtual const int pt() const = 0;
  virtual int pt() = 0;

  virtual const std::vector<int> children() const = 0;
  virtual std::vector<int> children() = 0;

  virtual const std::vector<int> parents() const = 0;
  virtual std::vector<int> parents() = 0;

  virtual const int GetIndex() const = 0;
  virtual int GetIndex() = 0;

  virtual const int status() const = 0;
  virtual int status() = 0;
};

class ITruths {
public:
  virtual ~ITruths() { }

  virtual const ITruth& operator[](std::size_t idx) const = 0;
  virtual ITruth& operator[](std::size_t idx) = 0;

  virtual const std::size_t n() const = 0;
  virtual std::size_t n() = 0;
};

#endif
