#include "init.h"
QVector <mdbtest::PatternSystem> mdbtest::PMSystem()
{
    QVector <PatternSystem> vector;
    PatternSystem pattern;
    pattern.name = "p-0"; pattern.description = "Bunka";
    vector.push_back(pattern);
    pattern.name = "p-1"; pattern.description = "Barnfield and Richard";
    vector.push_back(pattern);
    pattern.name = "p-2"; pattern.description = "Friendship/Women";
    vector.push_back(pattern);
    pattern.name = "p-3"; pattern.description = "Morris, K.";
    vector.push_back(pattern);
    pattern.name = "p-4"; pattern.description = "Castro";
    vector.push_back(pattern);
    return vector;
}

QVector <mdbtest::GroupName> mdbtest::GroupNames()
{
    QVector <GroupName> vector;
    GroupName group;
    group.name = "A. Direct Height"; group.pattern = PMSystem().at(0).description;
    vector.push_back(group);
    group.name = "B. Direct Width"; group.pattern = PMSystem().at(1).description;
    vector.push_back(group);
    group.name = "C. Indentation"; group.pattern = PMSystem().at(2).description;
    vector.push_back(group);
    group.name = "D. Hand"; group.pattern = PMSystem().at(3).description;
    vector.push_back(group);
    group.name = "E. Foot"; group.pattern = PMSystem().at(4).description;
    vector.push_back(group);
    return vector;
}
