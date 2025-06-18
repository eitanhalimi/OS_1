// stack_overflow.c
void crash() {
    crash();
}

int main() {
    crash();
    return 0;
}
