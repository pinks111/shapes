#include "App.h"
#include "Relations.h"
#include <iostream>

int App::count = 0;

App::App() : pointStorage_(), segmentStorage_(), circleStorage_(), relationStorage_() {}

App::~App() {
    for (size_t i = 0; i < relationStorage_.getSize(); ++i) {
        delete relationStorage_.getItem(i);
    }
}

Identi App::addObject(PrimitiveType type) {
    Identi newId(++count);
    
    switch(type) {
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

Identi App::addArrange(MutualArrangeType type, const Storage<Identi>& ii) {
    return addArrange(type, ii, 0.0);
}

Identi App::addArrange(MutualArrangeType type, const Storage<Identi>& ii, double value) {
    Identi relationId(++count);
    Relation* relation = nullptr;

    switch(type) {
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

    std::cout << "Created relation of type " << static_cast<int>(type) +1<< " with ID: " << relationId.getID() 
              << " for " << ii.getSize() << " objects" << " with parameter: " << value << "\n";
    
    return relationId;
}

double App::sumErrors() {
    double total = 0.0;
    for (size_t i = 0; i < relationStorage_.getSize(); ++i) {
        Relation* relation = relationStorage_.getItem(i);
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
				newParameters.addItem(parameters.getItem(i) - learning_rate * grad.getItem(i));
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