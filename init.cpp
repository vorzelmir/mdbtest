#include "init.h"

//----------------------------------------------------------------------------------------
/**
 * @brief insert default data to the pattern_system table
 * @return QVector<PatternSystem>
 */
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

//---------------------------------------------------------------------------------------
/**
 * @brief insert default data to the measurement_group table
 * @return QVector<GroupName>
 */
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

//---------------------------------------------------------------------------------------
/**
 * @brief insert default data to the measurement table
 * @return QVector<mdbtest::Measurement>
 */
QVector<mdbtest::Measurement> mdbtest::Measurements()
{
    QVector <Measurement> vector;
    Measurement meas;
    meas.pattern = PMSystem().at(0).description;
    meas.name = "height";
    meas.fullName = "Height: Total";
    meas.description = "Vertical distance from crown of head to floor.";
    meas.image = ":/diagrams/diagrams/Ap1.svg";
    meas.group = "A. Direct Height";
    vector.push_back(meas);

    meas.pattern = PMSystem().at(1).description;
    meas.name = "height_neck_back";
    meas.fullName = "Height: Neck Back";
    meas.description = "Vertical distance from the Neck Back (cervicale vertebra) to the floor.";
    meas.image = ":/diagrams/diagrams/Ap2.svg";
    meas.group = "A. Direct Height";
    vector.push_back(meas);

    meas.pattern = PMSystem().at(2).description;
    meas.name = "width_shoulder";
    meas.fullName = "Width: Shoulder";
    meas.description = "Horizontal distance from Shoulder Tip to Shoulder Tip.";
    meas.image = ":/diagrams/diagrams/Bp1.svg";
    meas.group = "B. Direct Width";
    vector.push_back(meas);

    meas.pattern = PMSystem().at(3).description;
    meas.name = "width_bust";
    meas.fullName = "Width: Bust";
    meas.description = "Horizontal distance from Bust Side to Bust Side.";
    meas.image = ":/diagrams/diagrams/Bp2.svg";
    meas.group = "B. Direct Width";
    vector.push_back(meas);

    meas.pattern = PMSystem().at(4).description;
    meas.name = "indent_neck_back";
    meas.fullName = "Indent: Neck Back";
    meas.description = "Horizontal distance from Scapula (Blade point) to the Neck Back.";
    meas.image = ":/diagrams/diagrams/Cp1.svg";
    meas.group = "C. Indentation";
    vector.push_back(meas);

    return vector;
}
