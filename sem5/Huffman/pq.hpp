#include <utility>
#include <optional>

template<typename T, typename TCMP>
class priority_queue
{
public:
  priority_queue(size_t MAX)
  {
    body = new T[maxsize = MAX + 1];
    numnodes = 0;
  }

  ~priority_queue() { delete[] body; }

  int insert(T const& node)
  {
    if (numnodes > maxsize) {
      return -1; // или расширяем.
    }
    body[++numnodes] = { node };
    for (size_t i = numnodes; i > 1 && TCMP()(body[i], body[i / 2]); i /= 2) {
      swap(i, i / 2);
    }
    return 0;
  }

  optional<T> fetchMin()
  {
    if (numnodes <= 0)
      return nullopt;
    return { body[1] };
  }
  
  size_t size() const 
  {
    return numnodes;
  }

  int removeMin()
  {
    if (numnodes == 0)
      return -1;
    body[1] = body[numnodes--];
    heapify(1);
    return 0;
  }

private:
  void heapify(size_t index)
  {
    for (;;) {
      auto left = index + index, right = left + 1;
      // Кто больше, [index], [left], [right]?
      auto largest = index;
      if (left <= numnodes && TCMP()(body[left], body[index]))
        largest = left;
      if (right <= numnodes && TCMP()(body[right], body[largest]))
        largest = right;
      if (largest == index)
        break;
      swap(index, largest);
      index = largest;
    }
  }

  void swap(int n1, int n2) { std::swap(body[n1], body[n2]); }
  T* body;
  size_t numnodes;
  size_t maxsize;
};
