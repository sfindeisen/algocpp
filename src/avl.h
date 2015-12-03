#include <iostream>
#include "memory.h"

template <class T> struct avl_node {
    avl_node(T it) : item(it), parent(NULL), child_left(NULL), child_right(NULL), bf(0) {}

    T            item;
    avl_node<T>* parent;
    avl_node<T>* child_left;
    avl_node<T>* child_right;
    signed short bf;    // Balance factor: height(right) - height(left)
};

/** AVL tree. No duplicates. */
template <class T> class avl : public container<T> {
    public:
        avl();
        avl(const avl<T>& another);

        virtual avl<T>& operator=(const avl<T>& another);
        virtual         ~avl();

        virtual bool contains(T item) const;
        virtual void   insert(T item);
        virtual void   remove(T item);

        /** Number of elements in this container. */
        virtual t_index    size() const;
        virtual    bool isEmpty() const;
        virtual    void   clear();

        virtual TString asString() const;
        virtual void    printTree(ostream& s) const;

    protected:
        virtual void printMsg (ostream& s, const TString& msg)              const;
        virtual int  printTree(ostream& s, int level, const avl_node<T>* p) const;

        virtual void rotate_l_basic(avl_node<T>* pivot);
        virtual void rotate_r_basic(avl_node<T>* pivot);

        virtual void rotate_l (avl_node<T>* pivot);
        virtual void rotate_lr(avl_node<T>* pivot);
        virtual void rotate_r (avl_node<T>* pivot);
        virtual void rotate_rl(avl_node<T>* pivot);

        virtual avl_node<T>* find_max(avl_node<T>* tree) const;
        virtual avl_node<T>* find_min(avl_node<T>* tree) const;
        virtual void     fixup_insert(avl_node<T>* child, avl_node<T>* parent);
        virtual void     fixup_remove(avl_node<T>* child, avl_node<T>* parent);

        virtual avl_node<T>*   copyTree(const avl_node<T>* node) const;
        virtual void         deleteTree(const avl_node<T>* node) const;

    private:
        avl_node<T>* root;
        t_index      nodeCount;
};

// ========================================
// Template implementation
// ========================================

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

// ================================
// AVL operations
// ================================

/** Single left rotation (just node moves, no bfs are updated). */
template <class T> void avl<T>::rotate_l_basic(avl_node<T>* pivot) {
    avl_node<T>* const parent  =  pivot->parent;
    avl_node<T>* const parent2 = parent->parent;
    avl_node<T>* const  childl =  pivot->child_left;

    EBDS_TRACE_MSG("rotate left basic: pivot: " << (pivot->item) << ", parent: " << (parent->item));

    if (parent2) {
        if (parent == parent2->child_left)
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

/** Single right rotation (just node moves, no bfs are updated). */
template <class T> void avl<T>::rotate_r_basic(avl_node<T>* pivot) {
    avl_node<T>* const parent  =  pivot->parent;
    avl_node<T>* const parent2 = parent->parent;
    avl_node<T>* const  childr =  pivot->child_right;

    EBDS_TRACE_MSG("rotate right basic: pivot: " << (pivot->item) << ", parent: " << (parent->item));

    if (parent2) {
        if (parent == parent2->child_left)
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

/** Left rotation (right right case).
 *  This includes node moves as well as bfs udpate in pivot and its parent.
 *
 *  Here pivot is the lower node of the 2 (to-be root).
 */
template <class T> void avl<T>::rotate_l(avl_node<T>* pivot) {
    avl_node<T>*  const parent = pivot->parent;
    const signed int bf_parent = parent->bf;
    const signed int bf_pivot  =  pivot->bf;

    EBDS_TRACE_MSG("rotate left: pivot: " << (pivot->item) << ", parent: " << (parent->item));

    rotate_l_basic(pivot);

    const signed int c1 = 1 - bf_parent + max(0, bf_pivot);
    parent->bf = 0 - c1;
     pivot->bf = bf_pivot - 1 - max(0, c1);
}

/** Right rotation (left left case).
 *  This includes node moves as well as bfs udpate in pivot and its parent.
 *
 *  Here pivot is the lower node of the 2 (to-be root).
 */
template <class T> void avl<T>::rotate_r(avl_node<T>* pivot) {
    avl_node<T>*  const parent = pivot->parent;
    const signed int bf_parent = parent->bf;
    const signed int bf_pivot  =  pivot->bf;

    EBDS_TRACE_MSG("rotate right: pivot: " << (pivot->item) << ", parent: " << (parent->item));

    rotate_r_basic(pivot);

    const signed int c1 = 1 + bf_parent + max(0, bf_pivot);
    parent->bf = c1 - bf_pivot;
     pivot->bf = 1 + max(bf_pivot, c1);
}

/** Left rotation + right rotation (left right case).
 *  This includes node moves as well as bfs udpate in pivot, its parent
 *  and its grandparent.
 *
 *  Here pivot is the lowest node of the 3 (to-be root).
 */
template <class T> void avl<T>::rotate_lr(avl_node<T>* pivot) {
    // TODO niepotrzebne zmienne
    avl_node<T>* const parent1 = pivot->parent;
    avl_node<T>* const parent2 = parent1->parent;
    // const signed short oldbf   = pivot->bf;

    EBDS_TRACE_MSG("rotate left-right: pivot: " << (pivot->item) << ", parent1: " << (parent1->item) << ", parent2: " << (parent2->item));

    rotate_l(pivot);
    rotate_r(pivot);

/*
    rotate_l_basic(p);
    rotate_r_basic(p);

      pivot->bf = 0;
    parent1->bf = 0;
    parent2->bf = 0;

    switch (pbf) {
        // 0 is also possible, since pivot can be a leaf
        case -1:
            parent2->bf = 1;
            break;
        case  1:
            pivot->bf = -1;
            break;
    }
*/
}

/** Right rotation + left rotation (right left case).
 *  This includes node moves as well as bfs udpate in pivot, its parent
 *  and its grandparent.
 *
 *  Here pivot is the lowest node of the 3 (to-be root).
 */
template <class T> void avl<T>::rotate_rl(avl_node<T>* pivot) {
    // TODO niepotrzebne zmienne
    avl_node<T>* const parent1 = pivot->parent;
    avl_node<T>* const parent2 = parent1->parent;
    // const signed short oldbf   = pivot->bf;

    EBDS_TRACE_MSG("rotate right-left: pivot: " << (pivot->item) << ", parent1: " << (parent1->item) << ", parent2: " << (parent2->item));

    rotate_r(pivot);
    rotate_l(pivot);

/*
    rotate_r_basic(pivot);
    rotate_l_basic(pivot);

      pivot->bf = 0;
    parent1->bf = 0;
    parent2->bf = 0;

    switch (bf) {
        // 0 is also possible, since pivot can be a leaf
        case -1:
            pivot->bf = 1;
            break;
        case  1:
            parent2->bf = -1;
            break;
    }
*/
}

template <class T> void avl<T>::fixup_insert(avl_node<T>* child, avl_node<T>* parent) {
    while (parent) {
        EBDS_TRACE_MSG("fixup_insert: child: " << (child->item) << ", parent: " << (parent->item));

        if (child == parent->child_left) {
            parent->bf--;

            if (0 == parent->bf)
                break;
            else if (-2 == parent->bf) {
                if (-1 == child->bf) {
                    rotate_r(child);
                    break;
                } else if (1 == child->bf) {
                    rotate_lr(child->child_right);
                    break;
                }
            }
        } else if (child == parent->child_right) {
            parent->bf++;

            if (0 == parent->bf)
                break;
            else if (2 == parent->bf) {
                if (1 == child->bf) {
                    rotate_l(child);
                    break;
                } else if (-1 == child->bf) {
                    rotate_rl(child->child_left);
                    break;
                }
            }
        }

        child  = parent;
        parent = parent->parent;
    }
}

template <class T> void avl<T>::insert(T insItem) {
    EBDS_TRACE_MSG("insert: " << insItem);

    avl_node<T>* current = root;
    avl_node<T>* parent  = current;

    while (current) {
        if (current->item == insItem) {
            EBDS_THROW(duplicate_value_exception());
        } else if (current->item < insItem) {
            parent  = current;
            current = current->child_right;
        } else {
            parent  = current;
            current = current->child_left;
        }
    }

    if (parent) {
        EBDS_NEW(current, avl_node<T>(insItem));
        current->parent = parent;

        if (parent->item < insItem)
            parent->child_right = current;
        else
            parent->child_left  = current;

        nodeCount++;
        fixup_insert(current, parent);
    } else {
        // This is the first node in the tree (root)
        EBDS_NEW(root, avl_node<T>(insItem));
        nodeCount = 1;
    }
}

template <class T> void avl<T>::fixup_remove(avl_node<T>* child, avl_node<T>* parent) {
    avl_node<T>* pivot = NULL;

    if ((! child) && (! (parent->child_left)) && (! (parent->child_right))) {
        // parent is a leaf; before remove() it had 1 child
        EBDS_TRACE_MSG("fixup_remove: child: NULL, parent: " << (parent->item) << " (leaf)");
        parent->bf = 0;
         child = parent;
        parent = parent->parent;
    }

    while (parent) {
        pivot = NULL;

        if (child) {
            EBDS_TRACE_MSG("fixup_remove: child: " << (child->item) << ", parent: " << (parent->item));
        } else {
            EBDS_TRACE_MSG("fixup_remove: child: NULL, parent: " << (parent->item));
        }

        if (child == parent->child_left) {
            parent->bf++;

            if (1 == parent->bf)
                break;
            else if (2 == parent->bf) {
                // Now child becomes the other child
                child = parent->child_right;

                if (1 == child->bf)
                    rotate_l(pivot = child);
                else if (-1 == child->bf)
                    rotate_rl(pivot = child->child_left);
                else if (0 == child->bf)
                    rotate_l(pivot = child);
            }
        } else if (child == parent->child_right) {
            parent->bf--;

            if (-1 == parent->bf)
                break;
            else if (-2 == parent->bf) {
                // Now child becomes the other child
                child = parent->child_left;

                if (-1 == child->bf)
                    rotate_r(pivot = child);
                else if (1 == child->bf)
                    rotate_lr(pivot = child->child_right);
                else if (0 == child->bf)
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

template <class T> void avl<T>::remove(T delItem) {
    EBDS_TRACE_MSG("remove: " << delItem);

    avl_node<T>* current = root;

    while (current) {
        if (current->item == delItem)
            break;
        else if (current->item < delItem)
            current = current->child_right;
        else
            current = current->child_left;
    }

    if (current) {
        if (current->child_left) {
            avl_node<T>* lmax = find_max(current->child_left);
            current->item = lmax->item;
            current = lmax;
            EBDS_TRACE_MSG("lmax: " << (lmax->item));
            EBDS_TRACE_MSG("current: " << (current->item));
        } else if (current->child_right) {
            avl_node<T>* rmin = find_min(current->child_right);
            current->item = rmin->item;
            current = rmin;
            EBDS_TRACE_MSG("rmin: " << (rmin->item));
            EBDS_TRACE_MSG("current: " << (current->item));
        } else {
            // current is a leaf!
            EBDS_TRACE_MSG("current is a leaf!");
        }

        // Now delete current. It has at most 1 child.
        avl_node<T>* parent = current->parent;

        if (parent) {
            EBDS_TRACE_MSG("parent: " << (parent->item));

            avl_node<T>* child = NULL;
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

            EBDS_TRACE_MSG("delete: " << (current->item));
            EBDS_DELETE(current);

            nodeCount--;
            fixup_remove(child, parent);
        } else {
            // This is the last node in the tree.
            EBDS_TRACE_MSG("delete root: " << (root->item));
            EBDS_DELETE(root);
            nodeCount = 0;
        }
    } else {
        EBDS_THROW(no_such_value_exception());
    }
}

template <class T> bool avl<T>::contains(T searchItem) const {
    avl_node<T>* p = root;
    while (p) {
        if (p->item == searchItem)
            return true;
        else if (p->item < searchItem)
            p = p->child_right;
        else
            p = p->child_left;
    }
    return false;
}

// =========================================================
// Printing --- this is for debugging purposes only!
// =========================================================

template <class T> TString avl<T>::asString() const {
    TStringStream ss;
    printTree(ss);
    return ss.str();
}

template <class T> void avl<T>::printMsg(ostream& s, const TString& m) const {
    s << m << std::endl;
}

template <class T> int avl<T>::printTree(ostream& s, int level, const avl_node<T>* p) const {
    if (p) {
        int hl=0, hr=0;
        // const bool leaf = (! ((p->child_left) || (p->child_right)));

        TString indent;
        for (int k = 0; k < level; k++) {
            indent += "    ";
        }

//      if (! leaf)
//          printMsg(s, EBDS_STRING(indent << "   (" << (p->item) << ")"));

        if (p->child_left) {
            if (p != p->child_left->parent)
                printMsg(s, "LEFT CHILD ERROR");
            hl = printTree(s, level + 1, p->child_left);
        }

        if (p == root) {
            printMsg(s, EBDS_STRING(indent << " R (" << (p->item) << ") bf=" << (p->bf)));
        } else {
            printMsg(s, EBDS_STRING(indent << "   (" << (p->item) << ") bf=" << (p->bf)));
        }

        if (p->child_right) {
            if (p != p->child_right->parent)
                printMsg(s, "RIGHT CHILD ERROR");
            hr = printTree(s, level + 1, p->child_right);
        }

        if ((hr - hl) != (p->bf))
            printMsg(s, EBDS_STRING(indent << "   (" << (p->item) << ") BF ERROR!!"));
//      if (! leaf)
//          printMsg(s, EBDS_STRING(indent << "   (" << (p->item) << ")"));

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
