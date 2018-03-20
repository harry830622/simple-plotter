#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <iostream>
#include <string>
#include <vector>

namespace simple_plotter {

class Plotter {
 public:
  Plotter(const std::string& title) : title_(title) {
  }

  void Plot(std::ostream& os) const {
    os << "set title '" << title_ << "'" << std::endl;
    os << std::endl;

    int current_style_id = 1;
    for (const Style& style : styles_) {
      os << "set style " << style.type_ << " " << current_style_id << " "
         << style.value_ << std::endl;
      ++current_style_id;
    }
    os << std::endl;

    os << "set size ratio -1" << std::endl;
    os << "set clip two" << std::endl;
    os << "unset key" << std::endl;

    os << std::endl;
    os << "plot ";
    for (const Segment& segment : segments_) {
      os << "'-' w l ls " << segment.style_id_ << ", ";
    }
    for (const Arrow& arrow : arrows_) {
      os << "'-' w vectors arrowstyle " << arrow.style_id_ << ", ";
    }
    os << std::endl;

    for (const Segment& segment : segments_) {
      os << std::endl;
      os << segment.from_point_x_ << " " << segment.from_point_y_ << std::endl;
      os << segment.to_point_x_ << " " << segment.to_point_y_ << std::endl;
      os << "e" << std::endl;
    }

    for (const Arrow& arrow : arrows_) {
      os << std::endl;
      os << arrow.from_point_x_ << " " << arrow.from_point_y_ << " "
         << arrow.to_point_x_ - arrow.from_point_x_ << " "
         << arrow.to_point_y_ - arrow.from_point_y_ << std::endl;
      os << "e" << std::endl;
    }

    os << std::endl;
    os << "pause -1 'Press enter to exit.'" << std::endl;
  }

  // Setters

  int AddStyle(const std::string& type, const std::string& value) {
    styles_.push_back(Style(type, value));
    const int style_id = styles_.size();
    return style_id;
  }

  void AddSegment(double from_point_x, double from_point_y, double to_point_x,
                  double to_point_y, int style_id) {
    segments_.push_back(
        Segment(from_point_x, from_point_y, to_point_x, to_point_y, style_id));
  }

  void AddArrow(double from_point_x, double from_point_y, double to_point_x,
                double to_point_y, int style_id) {
    arrows_.push_back(
        Arrow(from_point_x, from_point_y, to_point_x, to_point_y, style_id));
  }

  void AddRect(double lower_left_point_x, double lower_left_point_y,
               double upper_right_point_x, double upper_right_point_y,
               int style_id) {
    segments_.push_back(Segment(lower_left_point_x, lower_left_point_y,
                                lower_left_point_x, upper_right_point_y,
                                style_id));
    segments_.push_back(Segment(lower_left_point_x, upper_right_point_y,
                                upper_right_point_x, upper_right_point_y,
                                style_id));
    segments_.push_back(Segment(upper_right_point_x, upper_right_point_y,
                                upper_right_point_x, lower_left_point_y,
                                style_id));
    segments_.push_back(Segment(upper_right_point_x, lower_left_point_y,
                                lower_left_point_x, lower_left_point_y,
                                style_id));
  }

 private:
  class Style {
   public:
    Style(const std::string& type, const std::string& value)
        : type_(type), value_(value) {
    }

    std::string type_;
    std::string value_;
  };

  class Segment {
   public:
    Segment(double from_point_x, double from_point_y, double to_point_x,
            double to_point_y, int style_id)
        : from_point_x_(from_point_x),
          from_point_y_(from_point_y),
          to_point_x_(to_point_x),
          to_point_y_(to_point_y),
          style_id_(style_id) {
    }

    double from_point_x_;
    double from_point_y_;
    double to_point_x_;
    double to_point_y_;
    int style_id_;
  };

  class Arrow {
   public:
    Arrow(double from_point_x, double from_point_y, double to_point_x,
          double to_point_y, int style_id)
        : from_point_x_(from_point_x),
          from_point_y_(from_point_y),
          to_point_x_(to_point_x),
          to_point_y_(to_point_y),
          style_id_(style_id) {
    }

    double from_point_x_;
    double from_point_y_;
    double to_point_x_;
    double to_point_y_;
    int style_id_;
  };

  std::string title_;
  std::vector<Style> styles_;
  std::vector<Segment> segments_;
  std::vector<Arrow> arrows_;
};
}

#endif
