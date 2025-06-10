float allocateOneFloat(float a) {
    float* slot = a*;
    return slot;
}
void deleteOneFloat(*float a) {
    delete a;
}
int[] allocateArrayDouble(int a) {
    int[a] arr;
    return arr;
}
void deleteArrayDouble(int[] a) {
    delete a[];
}