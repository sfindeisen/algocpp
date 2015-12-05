#ifndef __ALGO__AVL__
#define __ALGO__AVL__

#include <algorithm>
#include <iostream>

namespace algocpp {

template <class T> struct avl_node {
    avl_node(const T& val) : value(val), parent(0), child_left(0), child_right(0), bf(0) {
    }

    T            value;
    avl_node<T>* parent;
    avl_node<T>* child_left;
    avl_node<T>* child_right;
    signed short bf;    // Balance factor: height(right) - height(left)
};

template <class T> class avl {
    public:
        avl();
        avl(const avl<T>& another);
        avl<T>& operator=(const avl<T>& another);
        virtual ~avl();

        bool contains(const T& value) const;
        void   insert(const T& value);
        void   remove(const T& value);

        size_t    size() const;
        bool   isEmpty() const;
        void     clear();

    protected:
        void rotate_l_basic(avl_node<T>* pivot);
        void rotate_r_basic(avl_node<T>* pivot);

        void rotate_l (avl_node<T>* pivot);
        void rotate_lr(avl_node<T>* pivot);
        void rotate_r (avl_node<T>* pivot);
        void rotate_rl(avl_node<T>* pivot);

        avl_node<T>* find_max(avl_node<T>* tree) const;
        avl_node<T>* find_min(avl_node<T>* tree) const;
        void     fixup_insert(avl_node<T>* child, avl_node<T>* parent);
        void     fixup_remove(avl_node<T>* child, avl_node<T>* parent);

        avl_node<T>* copyTree(const avl_node<T>* node) const;
        void deleteTree(avl_node<T>* node);

    private:
        avl_node<T>* root;
        size_t       nodeCount;
};

template <class T> avl<T>::avl() : root(0), nodeCount(0) {    
}

template <class T> avl<T>::avl(const avl<T>& another) : root(0), nodeCount(another.nodeCount) {
    this->root = copyTree(another.root);
}

template <class T> avl<T>::~avl() {
    if (root)
        deleteTree(root);
}

template <class T> avl<T>& avl<T>::operator=(const avl<T>& another) {
    if (this != &another) {
        deleteTree(root);
        this->root      = copyTree(another.root);
        this->nodeCount = another.nodeCount;
    }

    return *this;
}

template <class T> size_t avl<T>::size() const {
    return nodeCount;
}

template <class T> bool avl<T>::isEmpty() const {
    return (0 == nodeCount);
}

template <class T> void avl<T>::clear() {
    deleteTree(root);
    root = 0;
    nodeCount = 0;
}

template <class T> avl_node<T>* avl<T>::copyTree(const avl_node<T>* node) const {
    avl_node<T>* newTree = 0;
    avl_node<T>* p       = 0;

    if (node) {
        newTree = new avl_node<T>(node->value);

        if ((p = copyTree(node->child_left))) {
            newTree->child_left = p;
            p->parent           = newTree;
        }
        if ((p = copyTree(node->child_right))) {
            newTree->child_right = p;
            p->parent            = newTree;
        }
    }

    return newTree;
}

template <class T> void avl<T>::deleteTree(avl_node<T>* node) {
    if (node) {
        deleteTree(node->child_left);
        deleteTree(node->child_right);
        delete node;
    }
}

template <class T> avl_node<T>* avl<T>::find_max(avl_node<T>* tree) const {
    if (tree->child_right)
        return find_max(tree->child_right);
    return tree;
}

template <class T> avl_node<T>* avl<T>::find_min(avl_node<T>* tree) const {
    if (tree->child_left)
        return find_min(tree->child_left);
    return tree;
}

/** Single left rotation (just move the nodes, no bfs are updated). */
template <class T> void avl<T>::rotate_l_basic(avl_node<T>* pivot) {
    avl_node<T>* const parent  =  pivot->parent;
    avl_node<T>* const parent2 = parent->parent;
    avl_node<T>* const  childl =  pivot->child_left;

    std::cerr << "rotate left basic: pivot: " << (pivot->value) << ", parent: " << (parent->value) << std::endl;

    if (parent2) {
        if (parent == (parent2->child_left))
            parent2->child_left = pivot;
        else
            parent2->child_right = pivot;
    } else
        root = pivot;

     pivot->parent = parent2;
    parent->parent = pivot;

    if (childl)
        childl->parent = parent;

    parent->child_right = childl;
     pivot->child_left  = parent;
}

/** Single right rotation (just move the nodes, no bfs are updated). */
template <class T> void avl<T>::rotate_r_basic(avl_node<T>* pivot) {
    avl_node<T>* const parent  =  pivot->parent;
    avl_node<T>* const parent2 = parent->parent;
    avl_node<T>* const  childr =  pivot->child_right;

    std::cerr << "rotate right basic: pivot: " << (pivot->value) << ", parent: " << (parent->value) << std::endl;

    if (parent2) {
        if (parent == (parent2->child_left))
            parent2->child_left = pivot;
        else
            parent2->child_right = pivot;
    } else
        root = pivot;

     pivot->parent = parent2;
    parent->parent = pivot;

    if (childr)
        childr->parent = parent;

    parent->child_left = childr;
    pivot->child_right = parent;
}

/**
 * Left rotation (right right case).
 * This includes node moves as well as bfs udpate in pivot and its parent.
 *
 * Here pivot is the lower node of the 2 (to-be root).
 */
template <class T> void avl<T>::rotate_l(avl_node<T>* pivot) {
    avl_node<T>*  const parent = pivot->parent;
    const signed int bf_parent = parent->bf;
    const signed int bf_pivot  =  pivot->bf;

    std::cerr << "rotate left: pivot: " << (pivot->value) << ", parent: " << (parent->value) << std::endl;
    rotate_l_basic(pivot);

    const signed int c1 = 1 - bf_parent + std::max(0, bf_pivot);
    parent->bf = 0 - c1;
     pivot->bf = bf_pivot - 1 - std::max(0, c1);
}

/**
 * Right rotation (left left case).
 * This includes node moves as well as bfs udpate in pivot and its parent.
 *
 * Here pivot is the lower node of the 2 (to-be root).
 */
template <class T> void avl<T>::rotate_r(avl_node<T>* pivot) {
    avl_node<T>*  const parent = pivot->parent;
    const signed int bf_parent = parent->bf;
    const signed int bf_pivot  =  pivot->bf;

    std::cerr << "rotate right: pivot: " << (pivot->value) << ", parent: " << (parent->value) << std::endl;
    rotate_r_basic(pivot);

    const signed int c1 = 1 + bf_parent + std::max(0, bf_pivot);
    parent->bf = c1 - bf_pivot;
     pivot->bf = 1 + std::max(bf_pivot, c1);
}

/**
 * Left rotation + right rotation (left right case).
 * This includes node moves as well as bfs udpate in pivot, its parent
 * and its grandparent.
 *
 * Here pivot is the lowest node of the 3 (to-be root).
 */
template <class T> void avl<T>::rotate_lr(avl_node<T>* pivot) {
    rotate_l(pivot);
    rotate_r(pivot);
}

/**
 * Right rotation + left rotation (right left case).
 * This includes node moves as well as bfs udpate in pivot, its parent
 * and its grandparent.
 *
 * Here pivot is the lowest node of the 3 (to-be root).
 */
template <class T> void avl<T>::rotate_rl(avl_node<T>* pivot) {
    rotate_r(pivot);
    rotate_l(pivot);
}

template <class T> void avl<T>::fixup_insert(avl_node<T>* child, avl_node<T>* parent) {
    while (parent) {
        std::cerr << "fixup_insert: child: " << (child->value) << ", parent: " << (parent->value) << std::endl;

        if (child == parent->child_left) {
            --(parent->bf);

            if (0 == (parent->bf))
                break;
            else if (-2 == (parent->bf)) {
                if (-1 == (child->bf)) {
                    rotate_r(child);
                    break;
                } else if (1 == (child->bf)) {
                    rotate_lr(child->child_right);
                    break;
                }
            }
        } else if (child == (parent->child_right)) {
            ++(parent->bf);

            if (0 == (parent->bf))
                break;
            else if (2 == (parent->bf)) {
                if (1 == (child->bf)) {
                    rotate_l(child);
                    break;
                } else if (-1 == (child->bf)) {
                    rotate_rl(child->child_left);
                    break;
                }
            }
        }

        child  = parent;
        parent = parent->parent;
    }
}

template <class T> void avl<T>::insert(const T& insItem) {
    std::cerr << "insert: " << insItem << std::endl;

    avl_node<T>* current = root;
    avl_node<T>* parent  = current;

    while (current) {
        if ((current->value) <= insItem) {
            parent  = current;
            current = current->child_right;
        } else {
            parent  = current;
            current = current->child_left;
        }
    }

    if (parent) {
        current = new avl_node<T>(insItem);
        current->parent = parent;

        if ((parent->value) < insItem)
            parent->child_right = current;
        else
            parent->child_left  = current;

        ++nodeCount;
        fixup_insert(current, parent);
    } else {
        // This is the first node in the tree (root)
        root = new avl_node<T>(insItem);
        nodeCount = 1;
    }
}

template <class T> void avl<T>::fixup_remove(avl_node<T>* child, avl_node<T>* parent) {
    avl_node<T>* pivot = 0;

    if ((! child) && (! (parent->child_left)) && (! (parent->child_right))) {
        // parent is a leaf; before remove() it had 1 child
        std::cerr << "fixup_remove: child: NULL, parent: " << (parent->value) << " (leaf)" << std::endl;
        parent->bf = 0;
         child = parent;
        parent = parent->parent;
    }

    while (parent) {
        pivot = 0;

        if (child) {
            std::cerr << "fixup_remove: child: " << (child->value) << ", parent: " << (parent->value) << std::endl;
        } else {
            std::cerr << "fixup_remove: child: NULL, parent: " << (parent->value) << std::endl;
        }

        if (child == parent->child_left) {
            ++(parent->bf);

            if (1 == (parent->bf))
                break;
            else if (2 == (parent->bf)) {
                // Now child becomes the other child
                child = parent->child_right;

                if (1 == (child->bf))
                    rotate_l(pivot = child);
                else if (-1 == (child->bf))
                    rotate_rl(pivot = (child->child_left));
                else if (0 == (child->bf))
                    rotate_l(pivot = child);
            }
        } else if (child == (parent->child_right)) {
            --(parent->bf);

            if (-1 == (parent->bf))
                break;
            else if (-2 == (parent->bf)) {
                // Now child becomes the other child
                child = parent->child_left;

                if (-1 == (child->bf))
                    rotate_r(pivot = child);
                else if (1 == (child->bf))
                    rotate_lr(pivot = (child->child_right));
                else if (0 == (child->bf))
                    rotate_r(pivot = child);
            }
        }

        if (pivot) {
            // A rotation was made, and pivot is the new local root.
            if (pivot->bf) {
                // This was a (+2, 0) or (-2, 0) case. So the subtree height didn't change.
                break;
            }
             child = pivot;
            parent = pivot->parent;
        } else {
            child  = parent;
            parent = parent->parent;
        }
    }
}

template <class T> void avl<T>::remove(const T& delItem) {
    std::cerr << "remove: " << delItem << std::endl;
    avl_node<T>* current = root;

    while (current) {
        if ((current->value) == delItem)
            break;
        else if (current->value < delItem)
            current = current->child_right;
        else
            current = current->child_left;
    }

    if (current) {
        if (current->child_left) {
            avl_node<T>* lmax = find_max(current->child_left);
            current->value = lmax->value;
            current = lmax;
            std::cerr << "lmax: " << (lmax->value) << std::endl;
            std::cerr << "current: " << (current->value) << std::endl;
        } else if (current->child_right) {
            avl_node<T>* rmin = find_min(current->child_right);
            current->value = rmin->value;
            current = rmin;
            std::cerr << "rmin: " << (rmin->value) << std::endl;
            std::cerr << "current: " << (current->value) << std::endl;
        } else {
            // current is a leaf!
            std::cerr << "current is a leaf!" << std::endl;
        }

        // Now delete current. It has at most 1 child.
        avl_node<T>* parent = current->parent;

        if (parent) {
            std::cerr << "parent: " << (parent->value) << std::endl;

            avl_node<T>* child = 0;
            if (current->child_left)
                child = current->child_left;
            else if (current->child_right)
                child = current->child_right;

            if (current == parent->child_left) {
                parent->child_left = child;
            } else if (current == parent->child_right) {
                parent->child_right = child;
            }
            if (child)
                child->parent = parent;

            std::cerr << "delete: " << (current->value) << std::endl;
            delete current;

            --nodeCount;
            fixup_remove(child, parent);
        } else {
            // This is the last node in the tree.
            std::cerr << "delete root: " << (root->value) << std::endl;
            delete root;
            nodeCount = 0;
        }
    } else {
        // value not found -- just ignore
    }
}

template <class T> bool avl<T>::contains(const T& searchItem) const {
    avl_node<T>* p = root;
    while (p) {
        if ((p->value) == searchItem)
            return true;
        else if ((p->value) < searchItem)
            p = p->child_right;
        else
            p = p->child_left;
    }
    return false;
}

// =========================================================
// Printing --- this is for debugging purposes only!
// =========================================================

/*
template <class T> int avl<T>::printTree(ostream& s, int level, const avl_node<T>* p) const {
    if (p) {
        int hl=0, hr=0;
        // const bool leaf = (! ((p->child_left) || (p->child_right)));

        TString indent;
        for (int k = 0; k < level; k++) {
            indent += "    ";
        }

//      if (! leaf)
//          printMsg(s, EBDS_STRING(indent << "   (" << (p->value) << ")"));

        if (p->child_left) {
            if (p != p->child_left->parent)
                printMsg(s, "LEFT CHILD ERROR");
            hl = printTree(s, level + 1, p->child_left);
        }

        if (p == root) {
            printMsg(s, EBDS_STRING(indent << " R (" << (p->value) << ") bf=" << (p->bf)));
        } else {
            printMsg(s, EBDS_STRING(indent << "   (" << (p->value) << ") bf=" << (p->bf)));
        }

        if (p->child_right) {
            if (p != p->child_right->parent)
                printMsg(s, "RIGHT CHILD ERROR");
            hr = printTree(s, level + 1, p->child_right);
        }

        if ((hr - hl) != (p->bf))
            printMsg(s, EBDS_STRING(indent << "   (" << (p->value) << ") BF ERROR!!"));
//      if (! leaf)
//          printMsg(s, EBDS_STRING(indent << "   (" << (p->value) << ")"));

        return 1 + max(hl, hr);
    } else
        return 0;
}

template <class T> void avl<T>::printTree(ostream& s) const {
    //printMsg(s, "=- avl -=- avl -=- avl -= /");
    printMsg(s, EBDS_STRING("AVL: " << nodeCount << " nodes"));
    if (root && (root->parent)) {
        printMsg(s, "ROOT PARENT ERROR");
    }
    printTree(s, 1, root);
    //printMsg(s, "/ =- avl -=- avl -=- avl -=");
}
*/

};

#endif
