double distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

bool SACollision(Ship* a, Aster* b) {
	//Calculate total radius squared
	int totalRadiusSquared = a->getSize() + b->getSize();
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    //If the distance between the centers of the circles is less than the sum of their radii
    if(distanceSquared(a->getX(), a->getY(), b->getX(), b->getY()) < (totalRadiusSquared))
    {
        //The circles have collided
        return true;
    }

    //If not
    return false;
}

bool ABCollision(Aster* a, Bullet* b) {
    //Closest point on collision box
    int cX, cY;

    //Find closest x offset
    if(a->getX() < b->getX()) {
        cX = b->getX() ;
    } else if(a->getX() > b->getX() + b->getSize()) {
        cX = b->getX() + b->getSize();
    } else {
        cX = a->getX();
    }

    //Find closest y offset
    if(a->getY() < b->getY()) {
        cY = b->getY();
    } else if(a->getY() > b->getY() + b->getSize()) {
        cY = b->getY() + b->getSize();
    } else {
        cY = a->getY();
    }

    //If the closest point is inside the circle
    if(distanceSquared(a->getX(), a->getY(), cX, cY) < a->getSize() * a->getSize()) {
        //This box and the circle have collided
        return true;
    }

    //If the shapes have not collided
    return false;
}

// bool checkCollision( SDL_Rect a, SDL_Rect b )
// {
//     //The sides of the rectangles
//     int leftA, leftB;
//     int rightA, rightB;
//     int topA, topB;
//     int bottomA, bottomB;

//     //Calculate the sides of rect A
//     leftA = a.x;
//     rightA = a.x + a.w;
//     topA = a.y;
//     bottomA = a.y + a.h;

//     //Calculate the sides of rect B
//     leftB = b.x;
//     rightB = b.x + b.w;
//     topB = b.y;
//     bottomB = b.y + b.h;

//     //If any of the sides from A are outside of B
//     if( bottomA <= topB )
//     {
//         return false;
//     }

//     if( topA >= bottomB )
//     {
//         return false;
//     }

//     if( rightA <= leftB )
//     {
//         return false;
//     }

//     if( leftA >= rightB )
//     {
//         return false;
//     }

//     //If none of the sides from A are outside B
//     return true;
// }