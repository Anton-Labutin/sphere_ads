#pragma once

struct tree {
    tree *left = nullptr;
    tree *right = nullptr;

    int sym = -1;
    int count;
};
