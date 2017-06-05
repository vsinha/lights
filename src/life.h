#define GOL_ROWS 200
#define GOL_COLS 200

namespace GOL {

void clear(bool**);
void randomize(bool**);
void initialize();
bool checkNeighborhood(bool**, int, int);
bool (*update(void))[GOL_ROWS][GOL_COLS];

bool (*currBoard)[GOL_ROWS][GOL_COLS];
bool (*prevBoard)[GOL_ROWS][GOL_COLS];

}
