float rotatex(float angle, float x, float y, float cx, float cy) {
    return cos(angle * dtr) * (x - cx) - sin(angle * dtr) * (y - cy) + cx;
}

float rotatey(float angle, float x, float y, float cx, float cy) {
    return sin(angle * dtr) * (x - cx) + cos(angle * dtr) * (y - cy) + cy;
}