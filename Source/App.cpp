//#include <windows.h>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "App.h"
#include "Relations.h"
#include "BitmapPrinter.h"
#include "CTransform.h"


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
double App::getParameterValue(const ParamId& id) const {
  Identi objectId(id.getObjectID());

  if (const Point<double>* point = findObjectById(objectId, pointStorage_)) {
    if (id.getComponent() == 0) return point->x();
    if (id.getComponent() == 1) return point->y();
  }

  if (const Segment<double>* segment = findObjectById(objectId, segmentStorage_)) {
    switch (id.getComponent()) {
    case 0: return segment->p1().x();
    case 1: return segment->p1().y();
    case 2: return segment->p2().x();
    case 3: return segment->p2().y();
    default: break;
    }
  }

  if (const Circle<double>* circle = findObjectById(objectId, circleStorage_)) {
    switch (id.getComponent()) {
    case 0: return circle->center().x();
    case 1: return circle->center().y();
    case 2: return circle->radius();
    default: break;
    }
  }

  return 0.0;
}

bool App::setParameterValue(const ParamId& id, double value) {
  Identi objectId(id.getObjectID());

  if (Point<double>* point = findObjectById(objectId, pointStorage_)) {
    if (id.getComponent() == 0) {
      point->set_x(value);
      return true;
    }
    if (id.getComponent() == 1) {
      point->set_y(value);
      return true;
    }
  }

  if (Segment<double>* segment = findObjectById(objectId, segmentStorage_)) {
    Point<double> p1 = segment->p1();
    Point<double> p2 = segment->p2();
    switch (id.getComponent()) {
    case 0: p1.set_x(value); break;
    case 1: p1.set_y(value); break;
    case 2: p2.set_x(value); break;
    case 3: p2.set_y(value); break;
    default: return false;
    }
    segment->set_p1(p1);
    segment->set_p2(p2);
    return true;
  }

  if (Circle<double>* circle = findObjectById(objectId, circleStorage_)) {
    Point<double> center = circle->center();
    switch (id.getComponent()) {
    case 0: center.set_x(value); circle->set_center(center); return true;
    case 1: center.set_y(value); circle->set_center(center); return true;
    case 2: circle->set_radius(value); return true;
    default: return false;
    }
  }

  return false;
}

static bool containsParamId(const Storage<ParamId>& ids, const ParamId& id) {
  for (size_t i = 0; i < ids.getSize(); ++i) {
    if (ids.getItem(i) == id) {
      return true;
    }
  }
  return false;
}

bool App::solve() {
  const double errorThreshold = 1e-3;
  const size_t maxIterations = 10000;
  double learningRate = 0.1;

  if (relationStorage_.getSize() == 0) {
    return true;
  }

  for (size_t iteration = 0; iteration < maxIterations; ++iteration) {
    double currentError = sumErrors();
    if (currentError <= errorThreshold) {
      return true;
    }

    Storage<ParamId> ids;
    Dict<ParamId, double> currentValues;
    Dict<ParamId, double> gradients;
    bool hasGradient = false;

    for (size_t i = 0; i < relationStorage_.getSize(); ++i) {
      Relation* relation = relationStorage_.getItem(i);
      if (relation == nullptr) {
        continue;
      }

      Storage<ParamId> relationIds = relation->getParameterIds();
      Dict<ParamId, double> relationParameters = relation->getIdParameters();
      Dict<ParamId, double> relationGradients = relation->getIdPartitions();

      for (size_t j = 0; j < relationIds.getSize(); ++j) {
        ParamId id = relationIds.getItem(j);
        if (!containsParamId(ids, id)) {
          ids.addItem(id);
        }
        if (!currentValues.contains(id) && relationParameters.contains(id)) {
          currentValues.insert(id, relationParameters[id]);
        }

        double gradient = gradients.contains(id) ? gradients[id] : 0.0;
        if (relationGradients.contains(id)) {
          double relationGradient = relationGradients[id];
          gradient += relationGradient;
          hasGradient = hasGradient || std::abs(relationGradient) > 1e-12;
        }
        gradients.insert(id, gradient);
      }
    }

    if (ids.getSize() == 0 || !hasGradient) {
      return false;
    }

    Dict<ParamId, double> oldValues;
    for (size_t i = 0; i < ids.getSize(); ++i) {
      ParamId id = ids.getItem(i);
      double value = currentValues.contains(id) ? currentValues[id] : getParameterValue(id);
      oldValues.insert(id, value);
    }

    bool accepted = false;
    double step = learningRate;

    for (size_t attempt = 0; attempt < 20; ++attempt) {
      for (size_t i = 0; i < ids.getSize(); ++i) {
        ParamId id = ids.getItem(i);
        double gradient = gradients.contains(id) ? gradients[id] : 0.0;
        setParameterValue(id, oldValues[id] - step * gradient);
      }

      double newError = sumErrors();
      if (std::isfinite(newError) && newError < currentError) {
        accepted = true;
        learningRate = std::min(step * 1.2, 1.0);
        break;
      }

      for (size_t i = 0; i < ids.getSize(); ++i) {
        ParamId id = ids.getItem(i);
        setParameterValue(id, oldValues[id]);
      }
      step *= 0.5;
    }

    if (!accepted) {
      return false;
    }
  }

  return sumErrors() <= errorThreshold;
}

void App::scaleToFit(size_t& outW, size_t& outH) {
  Rect<double> bounds = unionRect();

  double x0 = bounds.topLeft().x();
  double y0 = bounds.bottomRight().y();
  double w  = bounds.width();
  double h  = bounds.height();

  const double minSize = 256.0;
  const double screenW = 1920.0;
  //static_cast<double>(GetSystemMetrics(SM_CXSCREEN));
  const double screenH = 1280.0;
	  //static_cast<double>(GetSystemMetrics(SM_CYSCREEN));

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

Rect<double> getDestRect(const Rect<double>& bounds) {
	double x0 = bounds.topLeft().x();
	double y0 = bounds.bottomRight().y();
	double w = bounds.width();
	double h = bounds.height();

	const double minSize = 256.0;
	const double screenW = 1920.0;//static_cast<double>(GetSystemMetrics(SM_CXSCREEN));
	const double screenH = 1060.0;// static_cast<double>(GetSystemMetrics(SM_CYSCREEN));
	const double maxSize = std::min(screenW, screenH);

	double outW = 0.0;
	double outH = 0.0;


	if (w > 0.0 && h > 0.0 && (w < minSize || h < minSize)) {
		double ratio = w / h;

		if (w <= h) {
			outW = static_cast<size_t>(minSize);
			outH = static_cast<size_t>(minSize / ratio);
		}
		else {
			outH = static_cast<size_t>(minSize);
			outW = static_cast<size_t>(minSize * ratio);
		}
	}
	else if (w > 0.0 && h > 0.0 && (w > maxSize || h > maxSize)) {
		double ratio = w / h;

		if (w >= h) {
			outW = static_cast<size_t>(maxSize);
			outH = static_cast<size_t>(maxSize / ratio);
		}
		else {
			outH = static_cast<size_t>(maxSize);
			outW = static_cast<size_t>(maxSize * ratio);
		}
	}
	else {
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

		if (w > 0.0)
			outW = static_cast<size_t>(alpha * w);
		else
			outW = static_cast<size_t>(minSize);

		if (h > 0.0)
			outH = static_cast<size_t>(alpha * h);
		else
			outH = static_cast<size_t>(minSize);
	}

	return Rect<double>({ 0,outH }, { outW,0 });
}


void App::print(const char* filename) {
	Rect<double> originalRect = unionRect();	
	
	Rect<double> destRect = getDestRect(originalRect);

	CTransform transform(originalRect, destRect);

	
	BitmapPrinter printer(
		static_cast<size_t>(destRect.width()) + 1,
		static_cast<size_t>(destRect.height()) + 1 );


	for (size_t i = 0; i < pointStorage_.getSize(); ++i) {
		printer.drawPoint( transform(pointStorage_.getItem(i)) );
	}

	for (size_t i = 0; i < segmentStorage_.getSize(); ++i) {
		Segment<double> origSegment = segmentStorage_.getItem(i);
		printer.drawSegment(transform(origSegment));
	}
	for (size_t i = 0; i < circleStorage_.getSize(); ++i) {
		printer.drawCircle(transform(circleStorage_.getItem(i)));
	}

	printer.save2File(filename);

}
