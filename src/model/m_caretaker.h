#ifndef SRC_MODEL_M_CARETAKER_H_
#define SRC_MODEL_M_CARETAKER_H_

#include "m_memento.h"
#include "model.h"

namespace view3d {
class Caretaker {
 public:
  Memento GetMemento() { return memento_; }
  void SetMemento(const Memento &memento) { memento_ = memento; }

 private:
  Memento memento_;
};
}  // namespace view3d

#endif  // SRC_MODEL_M_CARETAKER_H_
