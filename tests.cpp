#include "Algorithms/Algorithms.h"
#include "Graphics/View/View.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/rational.hpp>

typedef double T;

struct Comp
{
    bool are_equal(T a, T b) const
    {
        return a == b;
    }

    bool greater_than(T a, T b) const
    {
        return a >= b;
    }
};

int main()
{
    typedef alg::AVL_tree<T, Comp> Tree;
    typedef Tree::Node Node;

    Node* N1 = new Node(1);
    Node* N2 = new Node(2);
    Node* N3 = new Node(3);
    Node* N4 = new Node(4);
    Node* N5 = new Node(5);
    Node* N6 = new Node(6);

    N5->left = N3;
    N5->right = N6;
    N3->left = N2;
    N3->right = N4;
    N2->left = N1;

    Tree T;
//    T.root = N5;
    T.get_order() = Comp();

    unsigned n = 10;

    for(double x = 0; x < n; x += 1)
    {
//        std::cout << T.depth() << ' ' << T.size() << std::endl;
        T.insert(x);
    }

    std::cout << std::endl;

    for(double x = 0; x < n; x += 1)
    {
        bool found;
        T.remove(x, found);
    }


    return 0;
}