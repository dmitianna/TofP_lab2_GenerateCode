#ifndef CLASSMODIFIER_H
#define CLASSMODIFIER_H

namespace ClassModifier {

enum ClassModifier : unsigned int {
    NO_CLASS_MODIFIER = 0,

    ABSTRACT_CLASS = 1 << 0,
    SEALED_CLASS   = 1 << 1,
    FINAL_CLASS    = 1 << 2
};

}

#endif // CLASSMODIFIER_H
