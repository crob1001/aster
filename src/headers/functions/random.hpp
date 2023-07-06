float randF(float min, float max) {
	return ((float(std::rand()) / float(RAND_MAX)) * (max - min)) + min;
}