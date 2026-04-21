#include "App.h"
#include <iostream>

void printMenu() {
    std::cout << "\n--- Menu ---\n";
    std::cout << "1. Create point\n";
    std::cout << "2. Create segment\n";
    std::cout << "3. Create circle\n";
    std::cout << "4. Set relation\n";
    std::cout << "5. Show all objects\n";
    std::cout << "6. Show sum of errors\n";
    std::cout << "0. Quit\n";
    std::cout << "> ";
}

void printMutualArrangeTypes() {
    std::cout << "\n--- Relation types ---\n";
    std::cout << "1. Point coincidence\n";
    std::cout << "2. Distance between points\n";
    std::cout << "3. Point symmetry relative to segment\n";
    std::cout << "4. Point belongs to segment\n";
    std::cout << "5. Segment orthogonality\n";
    std::cout << "6. Segment verticality\n";
    std::cout << "7. Segment length\n";
    std::cout << "> ";
}

int main() {
    App app;
    int choice = 1;
    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        switch(choice) {
            case 1: {
                double x, y;
                std::cout << "Enter point coordinates (x y): ";
                std::cin >> x >> y;

                Identi id = app.addObject(PrimitiveType::POINT);
                Point<double>* pt = app.findObjectById(id, app.getPoints());
                if (pt) {
                    pt->set_x(x);
                    pt->set_y(y);
                }
                std::cout << "Point created with ID: " << id.getID()
                          << " at (" << x << ", " << y << ")\n";
                break;
            }

            case 2: {
                double x1, y1, x2, y2;
                std::cout << "Enter first point coordinates (x1 y1): ";
                std::cin >> x1 >> y1;
                std::cout << "Enter second point coordinates (x2 y2): ";
                std::cin >> x2 >> y2;

                Identi id = app.addObject(PrimitiveType::SEGMENT);
                Segment<double>* seg = app.findObjectById(id, app.getSegments());
                if (seg) {
                    seg->set_p1(Point<double>(x1, y1));
                    seg->set_p2(Point<double>(x2, y2));
                }
                std::cout << "Segment created with ID: " << id.getID()
                          << " from (" << x1 << ", " << y1
                          << ") to (" << x2 << ", " << y2 << ")\n";
                break;
            }

            case 3: {
                double x, y, radius;
                std::cout << "Enter center coordinates (x y): ";
                std::cin >> x >> y;
                std::cout << "Enter radius: ";
                std::cin >> radius;

                Identi id = app.addObject(PrimitiveType::CIRCLE);
                Circle<double>* circ = app.findObjectById(id, app.getCircles());
                if (circ) {
                    circ->set_center(Point<double>(x, y));
                    circ->set_radius(radius);
                }
                std::cout << "Circle created with ID: " << id.getID()
                          << " center (" << x << ", " << y
                          << "), radius " << radius << "\n";
                break;
            }

            case 4: {
                int arrangeType;
                printMutualArrangeTypes();
                std::cin >> arrangeType;

                std::cout << "Enter number of objects: ";
                int numObjects;
                std::cin >> numObjects;

                Storage<Identi> idStorage;
                std::cout << "Enter object IDs (one per line):\n";
                for (int i = 0; i < numObjects; ++i) {
                    int idValue;
                    std::cin >> idValue;
                    idStorage.addItem(Identi(idValue));
                }

                double value = 0.0;
                if (arrangeType == 2 || arrangeType == 7) {
                    std::cout << "Enter target value: ";
                    std::cin >> value;
                }

                MutualArrangeType type = static_cast<MutualArrangeType>(arrangeType - 1);
                Identi relationId = app.addArrange(type, idStorage, value);

                std::cout << "Relation created with ID: " << relationId.getID() << "\n";
                break;
            }

            case 5: {
                std::cout << "\n=== Current objects ===\n";
                std::cout << "Points:\n";
                app.getPoints().print();
                std::cout << "\nSegments:\n";
                app.getSegments().print();
                std::cout << "\nCircles:\n";
                app.getCircles().print();
                std::cout << "\n";
                break;
            }

            case 6: {
                std::cout << "Sum of errors: " << app.sumErrors() << "\n";
                break;
            }
        }
    }

    return 0;
}
