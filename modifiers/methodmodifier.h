#ifndef METHODMODIFIER_H
#define METHODMODIFIER_H

namespace MethodModifier {

enum MethodModifier : unsigned int {
    NO_MODIFIER = 0,

    STATIC   = 1 << 0,
    CONST    = 1 << 1,
    VIRTUAL  = 1 << 2,

    ABSTRACT = 1 << 3,
    FINAL    = 1 << 4,

    SEALED   = 1 << 5,
    EXTERN   = 1 << 6
};

}

#endif // METHODMODIFIER_H
