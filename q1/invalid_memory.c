int main() {
    int *pointer = (int *) 0xdeadbeef;
    *pointer = 2;
    return 0;
}
