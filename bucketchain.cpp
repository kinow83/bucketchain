#include "bucketchain.hpp"


int main() {

    chkchk::bucket_chain<int, int> bc;

    bc.push(1, 10);
    bc.push(2, 20);
    bc.make_block();

    bc.push(1, 10);
    bc.push(4, 40);
    bc.make_block();

    bc.push(33, 3330);
    bc.make_block();

    bc.view();
    return 0;
}