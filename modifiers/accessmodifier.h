#ifndef ACCESSMODIFIER_H
#define ACCESSMODIFIER_H

namespace AccessModifier {

enum AccessModifier : unsigned int {
    PUBLIC,
    PROTECTED,
    PRIVATE,

    PRIVATE_PROTECTED,
    FILE_ACCESS,
    INTERNAL,
    PROTECTED_INTERNAL
};

}

#endif // ACCESSMODIFIER_H
