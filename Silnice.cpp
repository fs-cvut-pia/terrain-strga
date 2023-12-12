#include "Silnice.h"

Silnice::Silnice(TerrainMap& m, std::string name_in, Point start_in, Point finish_in)
        : Path(m, name_in, start_in, finish_in) {
}

Silnice::~Silnice() {
}

bool Silnice::find() {
    std::priority_queue<Point, std::vector<Point>, std::greater<Point>> explorationQueue;
    explorationQueue.push(start);

    Matrix<int> hasBeenVisited(map.nx, map.ny);
    Matrix<Point> pathTrace(map.nx, map.ny);
    hasBeenVisited.zero();

    while (!explorationQueue.empty()) {
        Point currentPosition = explorationQueue.top();
        if (currentPosition == finish) {
            pathTrace(start.x, start.y) = Point(0, 0);
            while (!(pathTrace(currentPosition.x, currentPosition.y) == Point(0, 0))) {
                path.push_back(currentPosition);
                currentPosition = pathTrace(currentPosition.x, currentPosition.y);
            }
            std::reverse(path.begin(), path.end());
            return true;
        }
        explorationQueue.pop();

        for (int deltaX = -1; deltaX <= 1; deltaX++) {
            for (int deltaY = -1; deltaY <= 1; deltaY++) {
                if (deltaX == 0 && deltaY == 0) continue;
                Point nextPosition = currentPosition + Point(deltaX, deltaY);
                if (map.validCoords(nextPosition) && isMovementAllowed(currentPosition, nextPosition)) {
                    if (hasBeenVisited(nextPosition.x, nextPosition.y) == 0) {
                        hasBeenVisited(nextPosition.x, nextPosition.y) = 1;
                        nextPosition.r = calculateCost(currentPosition, nextPosition);
                        pathTrace(nextPosition.x, nextPosition.y) = currentPosition;
                        explorationQueue.push(nextPosition);
                    }
                }
            }
        }
    }
    return false;
}

double Silnice::calculateCost(const Point& from, const Point& to) {
    return from.r + (to - finish).length() - (from - finish).length();
}

bool Silnice::isMovementAllowed(const Point& from, const Point& to) {
    double distance = (to - from).length();
    return map.alt(to) >= 0 && std::abs(map.alt(to) - map.alt(from)) / distance / 1000 <= 0.06;
}