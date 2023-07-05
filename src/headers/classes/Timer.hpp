class Timer {
    public:
        Timer() {
            startTicks = 0;
            pauseTicks = 0;

            paused = false;
            started = false;
        }

        void start() {
            started = true;
            paused = false;

            startTicks = SDL_GetTicks();
            pauseTicks = 0;
        }

        void stop() {
            started = false;
            paused = true;

            startTicks = 0;
            pauseTicks = 0;
        }

        void pause() {
            if (started && !paused) {
                paused = true;

                pauseTicks = SDL_GetTicks() - startTicks;
                startTicks = 0;
            }
        }

        void unpause() {
            if (started && paused) {
                paused = false;

                startTicks = SDL_GetTicks() - pauseTicks;
                pauseTicks = 0;
            }
        }

        Uint32 getTicks() {
            Uint32 time = 0;

            if (started) {
                if (paused) {
                    time = pauseTicks;
                } else {
                    time = SDL_GetTicks() - startTicks;
                }
            }
            return time;
        }

        bool isStarted() {
            return started;
        }

        bool isPaused() {
            return paused && started;
        }

    private:
        Uint32 startTicks;
        Uint32 pauseTicks;

        bool paused;
        bool started;
};