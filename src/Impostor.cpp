#include "Impostor.hpp"

Impostor::Impostor(Entity mIdentity) : Entity(mIdentity) {
//    body.load("assets/SusRed.png");
    InitFrames(impostorFrames, impostorSpriteClips);
    currentBodyFrame = 0;
    canUseDoor = false;
    doorTarget.setPosition(324, 360);
    home.setPosition(SCREEN_WIDTH / 2 - BLOCK_SIZE_24 / 2, 415);
}

Impostor::~Impostor() {
    body.free();
}

void Impostor::calcDirection(uint8_t ActualMap[]) {
    std::vector<int> distances;
    std::vector<uint8_t> possibleDirections;

    // Checking for each of the 4 directions
    for (uint8_t i = 0; i < 4; i++) {
        short x = this->getX();
        short y = this->getY();
        // Get the next possible block (there are 4 of them)
        this->getNextPosition(x, y, i);
        if (!this->wallCollision(x, y, ActualMap, canUseDoor)) { // Process the direction if it isn't a wall
            // Calculating distance from each potential block to Pac
            auto distX = abs(x - this->target.getX());
            if (distX > SCREEN_WIDTH / 2)
                distX = SCREEN_WIDTH - distX;
            auto distY = abs(y - target.getY());
            auto dist = (distX * distX + distY * distY);

            distances.push_back(dist);
            possibleDirections.push_back(i);
        }
    }

    // Sort the possible directions
//    this->directionsBubbleSort(distances, possibleDirections);
    this->directionsMergeSort(distances, possibleDirections);

    // To make sure that ghosts won't reverse direction abruptly
    for (uint8_t i = 0; i < possibleDirections.size(); i++) {
        if (possibleDirections.at(i) != (this->getDirection() + 2) % 4) {
            this->setDirection(possibleDirections.at(i));
            return;
        }
    }
}

void Impostor::draw(Pac &pac) {
    std::string SusPath = "assets/Sus" + SusColor + ".png";
    std::string SusPathNervous = "assets/Sus" + SusColor + "Nervous.png";
    std::string SusPathDead = "assets/Sus" + SusColor + "Dead.png";

    if (this->getLiving()) {
        if (!pac.getPoweredUp()) {
            body.load(SusPath);
            this->setSpeed(2);
        } else {
            body.load(SusPathNervous);
            this->setSpeed(1); // Impostor is scared and slows down
        }
    } else {
        body.load(SusPathDead);
        this->setSpeed(5); // Impostor quickly returns home
    }

    if (this->isHome()) {
        this->setLiving(true);
    }

    currentClip = &impostorSpriteClips[currentBodyFrame / impostorFrames];
    static int flip;
    if (this->getFacing() == right) flip = right;
    else if (this->getFacing() == left) flip = left;
    body.render(this->getX() - 4, this->getY() - 4, 0, currentClip, flip);

    currentBodyFrame++;
    if (currentBodyFrame / impostorFrames >= impostorFrames) {
        currentBodyFrame = 0;
    }
}

void Impostor::merge(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections, std::vector<int> &tempDistances, std::vector<uint8_t> &tempDirections, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (distances[i] <= distances[j]) {
            tempDistances[k] = distances[i];
            tempDirections[k] = possibleDirections[i];
            i++;
        } else {
            tempDistances[k] = distances[j];
            tempDirections[k] = possibleDirections[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        tempDistances[k] = distances[i];
        tempDirections[k] = possibleDirections[i];
        i++;
        k++;
    }

    while (j <= right) {
        tempDistances[k] = distances[j];
        tempDirections[k] = possibleDirections[j];
        j++;
        k++;
    }

    for (int x = left; x <= right; x++) {
        distances[x] = tempDistances[x];
        possibleDirections[x] = tempDirections[x];
    }
}

void Impostor::mergeSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections, std::vector<int> &tempDistances, std::vector<uint8_t> &tempDirections, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(distances, possibleDirections, tempDistances, tempDirections, left, mid);
        mergeSort(distances, possibleDirections, tempDistances, tempDirections, mid + 1, right);
        merge(distances, possibleDirections, tempDistances, tempDirections, left, mid, right);
    }
}

void Impostor::directionsMergeSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections) {
    std::vector<int> tempDistances(distances.size());
    std::vector<uint8_t> tempDirections(possibleDirections.size());
    mergeSort(distances, possibleDirections, tempDistances, tempDirections, 0, distances.size() - 1);
}


bool Impostor::isHome() {
    if (this->getX() > 11 * BLOCK_SIZE_24 && this->getX() < 17 * BLOCK_SIZE_24) {
        if (this->getY() > 15 * BLOCK_SIZE_24 && this->getY() < 18 * BLOCK_SIZE_24)
            return true;
    }
    return false;
}

bool Impostor::isTargetToCalc(Pac &mPac) {
    if (!this->getLiving()) {
        canUseDoor = true;

        // Fixing ghosts not going home
        if (!(target.getPosition() == home)) target.setPosition(doorTarget);
        if (this->getX() > 216 && this->getX() < 432 && this->getY() == 336 && target.getPosition() == doorTarget) {
            target.setPosition(home);
        }

        if (this->getPosition() == home.getPosition())
            this->setLiving(true);
        return false;
    }

    if (this->isHome() && mPac.getPoweredUp()) {
        if (this->getPosition() == home.getPosition())
            target.setY(this->home.getY());
        else if (this->getX() == home.getX() && this->getY() == home.getY())
            target.setY(this->home.getY());
        return false;
    }

    if (this->isHome() && this->getLiving()) {
        canUseDoor = true;
        target.setPosition(this->doorTarget);
        return false;
    }

    canUseDoor = false;
    if (isChasing) return true;
    target.setPosition(restPos);
    return false;
}

void Impostor::setTarget(Pac &mPac, Position susRed) {
    this->target.setPosition(mPac.getPosition());
}

void Impostor::updatePos(uint8_t *actualBoard, Pac &mPac, Position susRed, bool inMenu, bool TimedStatus) {
    this->setChasingOrNot(TimedStatus, mPac);
    for (uint8_t i = 0; i < this->getSpeed(); i++) {
        if (this->isTargetToCalc(mPac)) {
            this->setTarget(mPac, susRed);
        }

        this->setFacing(this->getDirection());

        if (!inMenu) {
            this->calcDirection(actualBoard);
            this->move(this->getDirection());
            this->checkIfGoesOutOfScreen(false);
        } else {
            this->move(this->getDirection());
            this->checkIfGoesOutOfScreen(false);
        }
    }
}

void Impostor::setChasingOrNot(bool TimedStatus, Pac &mPac) {
    if (mPac.getPoweredUp()) {
        isChasing = false;
        return;
    } else {
        isChasing = TimedStatus;
    }
}

