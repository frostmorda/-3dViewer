#ifndef SRC_MISC_H_
#define SRC_MISC_H_
namespace view3d {
struct Extremums {
  double min_x{0};
  double max_x{0};
  double min_y{0};
  double max_y{0};
  double min_z{0};
  double max_z{0};
};
struct LastStand {
  double x_angle{0};
  double y_angle{0};
  double z_angle{0};
  double x_step{0};
  double y_step{0};
  double z_step{0};
  double scale{100};
};
}  // namespace view3d

#endif  // SRC_MISC_H_
