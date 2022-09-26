#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_
#include <string>

#include "../model/m_caretaker.h"
#include "../model/m_memento.h"
#include "../model/model.h"

namespace view3d {
class Controller {
 public:
  using matrix_4x4 = std::vector<std::vector<double>>;
  using vertices = std::vector<float>;

  Controller() {}

  explicit Controller(const view3d::Model* m)
      : model_(*m), caretaker_(new Caretaker()) {}

  Controller(const Controller& other) {
    // *caretaker_ = new Caretaker(other.caretaker_);
    *this = other;
  }

  Controller& operator=(const Controller& other) {
    model_ = other.model_;
    backup_model_ = other.backup_model_;
    caretaker_ = other.caretaker_;
    backup_caretaker_ = other.backup_caretaker_;
    return *this;
  }

  ~Controller() { delete caretaker_; }

  matrix_4x4& GetMVPMatrix() { return model_.GetMVPMatrix().GetMVPMatrix(); }
  matrix_4x4& GetTranslationMatrix() {
    return model_.GetMVPMatrix().GetTranslationMatrix();
  }
  matrix_4x4 GetCentralProjection() {
    return model_.GetMVPMatrix().GetProjectionCentral();
  }
  vertices& GetVertices() { return model_.GetPolygon().GetVertices(); }
  size_t GetCountOfFacets() { return model_.GetCountOfFacets(); }
  size_t GetCountOfVertices() { return model_.GetCountOfVertices(); }

  void RotationX(double angle_x);
  void RotationY(double angle_y);
  void RotationZ(double angle_z);
  void TranslationX(double step_x);
  void TranslationY(double step_y);
  void TranslationZ(double step_z);
  void Scale(double scale);
  bool MakeObject(const std::string& path) { return model_.MakeObject(path); }
  void SaveState() { caretaker_->SetMemento(model_.SaveMemento()); }
  void RestoreState() { model_.RestoreMemento(caretaker_->GetMemento()); }
  void NormalizeModel() { model_.GetMVPMatrix().NormalizeModel(); }
  void ResetModel() { model_.ResetModel(); }

  void BackupModel() { backup_model_ = model_; }
  void BackupState() { backup_caretaker_ = *caretaker_; }
  void SaveBackupState() {
    backup_caretaker_.SetMemento(backup_model_.SaveMemento());
  }
  void RestoreBackupModele() { model_ = backup_model_; }
  void RestoreBackupState() {
    model_.RestoreMemento(backup_caretaker_.GetMemento());
  }

 private:
  Model model_;
  Model backup_model_;
  Caretaker* caretaker_;
  Caretaker backup_caretaker_;
};
}  // namespace view3d

#endif  // SRC_CONTROLLER_CONTROLLER_H_
