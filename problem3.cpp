long long fib (int n) {
    if (n<2) return n;
    return fib(n-2) + fib(n-3);
}

int main() {
    fib(40);
}