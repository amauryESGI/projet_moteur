#pragma once

enum ThreadState : int {
    JOIN = -1,
    DEFAULT = 0,
    START = 1,
    STOP = 2,
    BLOCK = 3
};