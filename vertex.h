struct Vertex {
    int index;
    bool has_flea_a = false;
    bool has_flea_b = false;
    int state = 1;

    Vertex(int number, bool flea_a, bool flea_b) 
    : index(number), has_flea_a(flea_a), has_flea_b(flea_b) { }

    Vertex()
    : index(-1) {}
};

struct Flea {
    char name;
    int direction = 1;

    Flea()
    : name('z') {}

    Flea(char name_in)
        : name(name_in) {}
};
