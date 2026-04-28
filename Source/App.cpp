#include <windows.h>
#include "App.h"
#include "Relations.h"
#include <cmath>
#include <iostream>


int App::count = 0;

App::App()
    : pointStorage_(), segmentStorage_(), circleStorage_(), relationStorage_() {
}

App::~App() {
  for (size_t i = 0; i < relationStorage_.getSize(); ++i) {
    delete relationStorage_.getItem(i);
  }
}

Identi App::addObject(PrimitiveType type) {
  Identi newId(++count);

  switch (type) {
  case PrimitiveType::POINT: {
    Point<double> point;
    point.setId(newId);
    pointStorage_.addItem(point);
    break;
  }
  case PrimitiveType::SEGMENT: {
    Segment<double> segment;
    segment.setId(newId);
    segmentStorage_.addItem(segment);
    break;
  }
  case PrimitiveType::CIRCLE: {
    Circle<double> circle;
    circle.setId(newId);
    circleStorage_.addItem(circle);
    break;
  }
  }

  return newId;
}

Identi App::addPoint(double x, double y) {
  Identi id(++count);
  Point<double> point;
  point.setId(id);
  point.set_x(x);
  point.set_y(y);
  pointStorage_.addItem(point);
  return id;
}

Identi App::addSegment(double x1, double y1, double x2, double y2) {
  Identi id(++count);
  Segment<double> seg;
  seg.setId(id);
  seg.set_p1(Point<double>(x1, y1));
  seg.set_p2(Point<double>(x2, y2));
  segmentStorage_.addItem(seg);
  return id;
}

Identi App::addCircle(double cx, double cy, double radius) {
  Identi id(++count);
  Circle<double> circ;
  circ.setId(id);
  circ.set_center(Point<double>(cx, cy));
  circ.set_radius(radius);
  circleStorage_.addItem(circ);
  return id;
}

Identi App::addArrange(MutualArrangeType type, const Storage<Identi> &ii) {
  return addArrange(type, ii, 0.0);
}

Identi App::addArrange(MutualArrangeType type, const Storage<Identi> &ii,
                       double value) {
  Identi relationId(++count);
  Relation *relation = nullptr;

  switch (type) {
  case MutualArrangeType::POINTCOINCIDENT:
    relation = new PointCoincidentRelation(relationId, ii, value);
    break;
  case MutualArrangeType::POINTDISTANCE:
    relation = new PointDistanceRelation(relationId, ii, value);
    break;
  case MutualArrangeType::POINTBELONGSTOSEGMENT:
    relation = new PointBelongsToSegmentRelation(relationId, ii, value);
    break;
  case MutualArrangeType::POINTSSYMMETRYSEGMENT:
    relation = new PointsSymmetrySegmentRelation(relationId, ii, value);
    break;
  case MutualArrangeType::SEGMENTLENGTH:
    relation = new SegmentLengthRelation(relationId, ii, value);
    break;
  case MutualArrangeType::SEGMENTVERTICAL:
    relation = new SegmentVerticalRelation(relationId, ii, value);
    break;
  case MutualArrangeType::SEGMENTSNORMAL:
    relation = new SegmentsNormalRelation(relationId, ii, value);
    break;
  }

  if (relation != nullptr) {
    relation->setApp(this);
    relationStorage_.addItem(relation);
  }

  std::cout << "Created relation of type " << static_cast<int>(type) + 1
            << " with ID: " << relationId.getID() << " for " << ii.getSize()
            << " objects" << " with parameter: " << value << "\n";

  return relationId;
}

Rect<double> App::unionRect() const {
  Storage<Rect<double>> rects;

  for (size_t i = 0; i < pointStorage_.getSize(); ++i)
    rects.addItem(pointStorage_.getItem(i).getBoundingRect());
  for (size_t i = 0; i < segmentStorage_.getSize(); ++i)
    rects.addItem(segmentStorage_.getItem(i).getBoundingRect());
  for (size_t i = 0; i < circleStorage_.getSize(); ++i)
    rects.addItem(circleStorage_.getItem(i).getBoundingRect());

  if (rects.getSize() == 0)
    return Rect<double>();

  Rect<double> result = rects.getItem(0);
  for (size_t i = 1; i < rects.getSize(); ++i)
    result = result.unite(rects.getItem(i));

  return result;
}

double App::sumErrors() {
  double total = 0.0;
  for (size_t i = 0; i < relationStorage_.getSize(); ++i) {
    Relation *relation = relationStorage_.getItem(i);
    if (relation != nullptr) {
      total += relation->error();
    }
  }
  return total;
}
bool App::solve() {
  // Пока работаем только с одним требованием
  if (relationStorage_.getSize() == 1) {

    // Посчитаем текущее значение ошибки
    double current_error = relationStorage_.getItem(0)->error();

    const double errorThrreshold = 1e-3;

    while (current_error > errorThrreshold) {
      // Получим массив значений параметров
      Storage<double> parameters = relationStorage_.getItem(0)->getParameters();

      // Вычислим вектор частных производных для требования
      Storage<double> grad = relationStorage_.getItem(0)->partitions();

      // Сформируем новый вектор параметров
      static const double learning_rate = 0.1;
      Storage<double> newParameters;
      for (size_t i = 0; i < grad.getSize(); ++i) {
        newParameters.addItem(parameters.getItem(i) -
                              learning_rate * grad.getItem(i));
      }

      // Обновим параметры
      relationStorage_.getItem(0)->setParameters(newParameters);

      // Посчитаем новое значение ошибки
      current_error = relationStorage_.getItem(0)->error();
      std::cout << "Error " << current_error << std::endl;
    }
  }

  return true;
}

void App::scaleToFit(size_t& outW, size_t& outH) {
  Rect<double> bounds = unionRect();

  double x0 = bounds.topLeft().x();
  double y0 = bounds.bottomRight().y();
  double w  = bounds.width();
  double h  = bounds.height();

  const double minSize = 256.0;
  const double screenW = static_cast<double>(GetSystemMetrics(SM_CXSCREEN));
  const double screenH = static_cast<double>(GetSystemMetrics(SM_CYSCREEN));

  double alpha = 1.0;
  if (w > 0.0 && h > 0.0)
    alpha = std::min(screenW / w, screenH / h);
  else if (w > 0.0)
    alpha = screenW / w;
  else if (h > 0.0)
    alpha = screenH / h;

  if (w > 0.0 || h > 0.0) {
    double alphaMin = 1.0;
    if (w > 0.0 && h > 0.0)
      alphaMin = std::max(minSize / w, minSize / h);
    else if (w > 0.0)
      alphaMin = minSize / w;
    else
      alphaMin = minSize / h;

    double alphaMax = 1.0;
    if (w > 0.0 && h > 0.0)
      alphaMax = std::min(screenW / w, screenH / h);
    else if (w > 0.0)
      alphaMax = screenW / w;
    else
      alphaMax = screenH / h;

    alpha = std::max(alphaMin, std::min(alpha, alphaMax));
  }

  for (size_t i = 0; i < pointStorage_.getSize(); ++i) {
    Point<double>& p = pointStorage_.getItem(i);
    p.set_x(alpha * (p.x() - x0));
    p.set_y(alpha * (p.y() - y0));
  }
  for (size_t i = 0; i < segmentStorage_.getSize(); ++i) {
    Segment<double>& s = segmentStorage_.getItem(i);
    s.set_p1(Point<double>(alpha * (s.p1().x() - x0), alpha * (s.p1().y() - y0)));
    s.set_p2(Point<double>(alpha * (s.p2().x() - x0), alpha * (s.p2().y() - y0)));
  }
  for (size_t i = 0; i < circleStorage_.getSize(); ++i) {
    Circle<double>& c = circleStorage_.getItem(i);
    c.set_center(Point<double>(alpha * (c.center().x() - x0),
                               alpha * (c.center().y() - y0)));
    c.set_radius(alpha * c.radius());
  }

  if (w > 0.0)
    outW = static_cast<size_t>(alpha * w);
  else
    outW = static_cast<size_t>(minSize);

  if (h > 0.0)
    outH = static_cast<size_t>(alpha * h);
  else
    outH = static_cast<size_t>(minSize);
}
