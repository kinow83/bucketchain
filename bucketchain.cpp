#include "bucketchain.hpp"


uint32_t int_hash(int &v) {
    return v;
}

int main() {

    chkchk::bucket_chain<int, int, int_hash> bc;

    bc.push(1, 10);
    bc.push(2, 20);
    bc.make_block();

    bc.push(1, 10);
    bc.push(4, 40);
    bc.make_block();

    bc.push(33, 3330);
    bc.make_block();

    bc.to_print();
    return 0;
}