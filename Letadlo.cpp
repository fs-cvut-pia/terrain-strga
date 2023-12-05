#include "Letadlo.h"

Letadlo::Letadlo(TerrainMap& m, std::string name_in, Point start_in, Point finish_in)
        : Path(m, name_in, start_in, finish_in) {
}

Letadlo::~Letadlo() {
}

bool Letadlo::find() {
    std::priority_queue<Point, std::vector<Point>, std::greater<Point>> explorationQueue;
    explorationQueue.push(start);

    Matrix<int> isVisited(map.nx, map.ny);
    Matrix<Point> pathTrace(map.nx, map.ny);
    isVisited.zero();

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
                // Modify the condition to match Letadlo's specific requirements
                if (!map.validCoords(nextPosition)) continue;
                if (isVisited(nextPosition.x, nextPosition.y) == 0) {
                    isVisited(nextPosition.x, nextPosition.y) = 1;
                    nextPosition.r = calculateCost(currentPosition, nextPosition);
                    pathTrace(nextPosition.x, nextPosition.y) = currentPosition;
                    explorationQueue.push(nextPosition);
                }
            }
        }
    }
    return false; // Path not found
}

double Letadlo::calculateCost(const Point& from, const Point& to) {
    return from.r + (to - finish).length() - (from - finish).length();
}